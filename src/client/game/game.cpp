#include <std_include.hpp>
#include "game.hpp"

#include <utils/flags.hpp>
#include <utils/string.hpp>
#include <utils/io.hpp>

namespace game
{
	int Cmd_Argc()
	{
		return cmd_args->argc[cmd_args->nesting];
	}
	
	uint64_t base_address;

	namespace environment
	{
		mode mode_{none};

		bool is_sp()
		{
			return mode_ == sp;
		}

		bool is_mp()
		{
			return mode_ == mp;
		}

		bool is_dedi()
		{
			return mode_ == dedi;
		}

		void set_mode(mode mode)
		{
			mode_ = mode;
		}
	}
}

size_t reverse_b(const size_t ptr)
{
	return ptr - game::base_address;
}

size_t reverse_b(const void* ptr)
{
	return reverse_b(reinterpret_cast<size_t>(ptr));
}
