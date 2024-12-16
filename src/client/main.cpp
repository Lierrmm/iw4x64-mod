#include <std_include.hpp>
#include "loader/loader.hpp"
#include "loader/component_loader.hpp"
#include "game/game.hpp"

#include <utils/string.hpp>
#include <utils/io.hpp>
#include <utils/properties.hpp>
#include <utils/flags.hpp>

DECLSPEC_NORETURN void WINAPI exit_hook(const int code)
{
	component_loader::pre_destroy();
	exit(code);
}

void apply_aslr_patch(std::string* data)
{
	// mp binary, sp binary
	if (data->size() != 0x4BFA00 && data->size() != 0x4A6C00)
	{
		printf("%llu", data->size());
		throw std::runtime_error("File size mismatch, bad game files");
	}

	auto* dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(&data->at(0));
	auto* nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(&data->at(dos_header->e_lfanew));
	auto* optional_header = &nt_headers->OptionalHeader;

	if (optional_header->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE)
	{
		optional_header->DllCharacteristics &= ~(IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE);
	}
}

void get_aslr_patched_binary(std::string* binary, std::string* data)
{
	const auto patched_binary = (utils::properties::get_appdata_path() / "bin" / *binary).generic_string();

	try
	{
		apply_aslr_patch(data);
		if (!utils::io::file_exists(patched_binary) && !utils::io::write_file(patched_binary, *data, false))
		{
			throw std::runtime_error("Could not write file");
		}
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(
			utils::string::va("Could not create aslr patched binary for %s! %s",
				binary->data(), e.what())
		);
	}

	*binary = patched_binary;
}

FARPROC load_binary(uint64_t* base_address)
{
	loader loader;
	utils::nt::library self;

	loader.set_import_resolver([self](const std::string& library, const std::string& function) -> void*
	{
		if (function == "ExitProcess")
		{
			return exit_hook;
		}

		return component_loader::load_import(library, function);
	});

	game::environment::mode mode{ game::environment::mode::sp };
	if (utils::flags::has_flag("dedicated") || utils::flags::has_flag("dedi"))
	{
		mode = game::environment::mode::dedi;
	}
	else if (utils::flags::has_flag("multiplayer") || utils::flags::has_flag("mp"))
	{
		mode = game::environment::mode::mp;
	}
	else if (utils::flags::has_flag("singleplayer") || utils::flags::has_flag("sp"))
	{
		mode = game::environment::mode::sp;
	}
	else
	{
		const int result = MessageBoxA(NULL, "Launch multiplayer?", "INFO", MB_YESNOCANCEL);
		switch (result)
		{
		case IDYES:
			mode = game::environment::mode::mp;
			break;
		case IDNO:
			break;
		case IDCANCEL:
			quick_exit(0);
			break;
		}
	}
	game::environment::set_mode(mode);

	std::string binary = mode == game::environment::mode::sp ? "iw4sp.exe" : "iw4mp.exe";

	std::string data;
	if (!utils::io::read_file(binary, &data))
	{
		if (errno == EACCES) {
			throw std::runtime_error(utils::string::va(
				"Failed to access game binary (%s)!\nMake sure to dump the executables before running iw4x64-mod. You can use UWPDumper for this.",
				binary.data()));
		}
		throw std::runtime_error(utils::string::va(
			"Failed to read game binary (%s)!\nPlease copy the iw4x64-mod.exe into your Call of Duty: Modern Warfare 2 UWP installation folder and run it from there.",
			binary.data()));
	}

	get_aslr_patched_binary(&binary, &data);

#ifdef INJECT_HOST_AS_LIB
	return loader.load_library(binary, base_address);
#else
	*base_address = 0x140000000;
	return loader.load(self, data); // not working
#endif
}

int main()
{
	if (!game::environment::is_dedi())
		ShowWindow(GetConsoleWindow(), SW_HIDE);

	FARPROC entry_point;

	srand(uint32_t(time(nullptr)));

	{
		component_loader::sort();

		auto premature_shutdown = true;
		const auto _ = gsl::finally([&premature_shutdown]()
		{
			if (premature_shutdown)
			{
				component_loader::pre_destroy();
			}
		});

		try
		{
			if (!component_loader::post_start()) return EXIT_FAILURE;

			uint64_t base_address{};
			entry_point = load_binary(&base_address);
			if (!entry_point)
			{
				throw std::runtime_error("Unable to load binary into memory");
			}

			if (base_address != 0x140000000)
			{
				throw std::runtime_error(utils::string::va(
					"Base address was (%p) and not (%p)\nThis should not be possible!",
					base_address, 0x140000000));
			}

			if (!component_loader::post_load()) return EXIT_FAILURE;

			premature_shutdown = false;
		}
		catch (std::exception& e)
		{
			MessageBoxA(nullptr, e.what(), "ERROR", MB_ICONERROR);
			return EXIT_FAILURE;
		}
	}

	return static_cast<int>(entry_point());
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ int)
{
	return main();
}
