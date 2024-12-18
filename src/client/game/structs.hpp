#pragma once

namespace game
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];
	
	enum errorParm
	{
		ERR_FATAL = 0x0,
		ERR_DROP = 0x1,
		ERR_SERVERDISCONNECT = 0x2,
		ERR_DISCONNECT = 0x3,
		ERR_SCRIPT = 0x4,
		ERR_SCRIPT_DROP = 0x5,
		ERR_LOCALIZATION = 0x6,
		ERR_MAPLOADERRORSUMMARY = 0x7,
	};

	enum DvarSetSource : std::uint32_t
	{
		DVAR_SOURCE_INTERNAL = 0x0,
		DVAR_SOURCE_EXTERNAL = 0x1,
		DVAR_SOURCE_SCRIPT = 0x2,
		DVAR_SOURCE_UISCRIPT = 0x3,
		DVAR_SOURCE_SERVERCMD = 0x4,
		DVAR_SOURCE_NUM = 0x5,
	};

	enum DvarFlags : std::uint32_t
	{
		DVAR_FLAG_NONE = 0,
		DVAR_FLAG_SAVED = 0x1,
		DVAR_FLAG_LATCHED = 0x2,
		DVAR_FLAG_CHEAT = 0x4,
		DVAR_FLAG_REPLICATED = 0x8,
		DVAR_FLAG_WRITE = 0x800,
		DVAR_FLAG_READ = 0x2000,
	};

	enum dvar_type : std::int8_t
	{
		boolean = 0,
		value = 1,
		vec2 = 2,
		vec3 = 3,
		vec4 = 4,
		integer = 5,
		enumeration = 6,
		string = 7,
		color = 8,
		rgb = 9 // Color without alpha
	};

	union dvar_value
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		char color[4];
	};

	struct $A37BA207B3DDD6345C554D4661813EDD
	{
		int stringCount;
		const char* const* strings;
	};

	struct $9CA192F9DB66A3CB7E01DE78A0DEA53D
	{
		int min;
		int max;
	};

	struct $251C2428A496074035CACA7AAF3D55BD
	{
		float min;
		float max;
	};

	union dvar_limits
	{
		$A37BA207B3DDD6345C554D4661813EDD enumeration;
		$9CA192F9DB66A3CB7E01DE78A0DEA53D integer;
		$251C2428A496074035CACA7AAF3D55BD value;
		$251C2428A496074035CACA7AAF3D55BD vector;
	};

	struct dvar_t
	{
		const char* name; //00
		unsigned int flags; //08
		dvar_type type; //0C
		bool modified; //0D
		dvar_value current; //10
		dvar_value latched;
		dvar_value reset;
		dvar_limits domain;
	};

	struct Glyph
	{
		unsigned short letter;
		char x0;
		char y0;
		char dx;
		char pixelWidth;
		char pixelHeight;
		float s0;
		float t0;
		float s1;
		float t1;
	};
	
	struct Font_s
	{
		const char* fontName;
		int pixelHeight;
		int glyphCount;
		void* material;
		void* glowMaterial;
		Glyph* glyphs;
	};

	struct ScreenPlacement
	{
		vec2_t scaleVirtualToReal;
		vec2_t scaleVirtualToFull;
		vec2_t scaleRealToVirtual;
		vec2_t realViewportPosition;
		vec2_t realViewportSize;
		vec2_t virtualViewableMin;
		vec2_t virtualViewableMax;
		vec2_t realViewableMin;
		vec2_t realViewableMax;
		vec2_t virtualAdjustableMin;
		vec2_t virtualAdjustableMax;
		vec2_t realAdjustableMin;
		vec2_t realAdjustableMax;
		vec2_t subScreenLeft;
	};

	enum keyNum_t
	{
		K_NONE = 0x0,
		K_FIRSTGAMEPADBUTTON_RANGE_1 = 0x1,
		K_BUTTON_A = 0x1,
		K_BUTTON_B = 0x2,
		K_BUTTON_X = 0x3,
		K_BUTTON_Y = 0x4,
		K_BUTTON_LSHLDR = 0x5,
		K_BUTTON_RSHLDR = 0x6,
		K_LASTGAMEPADBUTTON_RANGE_1 = 0x6,
		K_BS = 0x8,
		K_TAB = 0x9,
		K_ENTER = 0xD,
		K_FIRSTGAMEPADBUTTON_RANGE_2 = 0xE,
		K_BUTTON_START = 0xE,
		K_BUTTON_BACK = 0xF,
		K_BUTTON_LSTICK = 0x10,
		K_BUTTON_RSTICK = 0x11,
		K_BUTTON_LTRIG = 0x12,
		K_BUTTON_RTRIG = 0x13,
		K_DPAD_UP = 0x14,
		K_FIRSTDPAD = 0x14,
		K_DPAD_DOWN = 0x15,
		K_DPAD_LEFT = 0x16,
		K_DPAD_RIGHT = 0x17,
		K_BUTTON_LSTICK_ALTIMAGE2 = 0x10,
		K_BUTTON_RSTICK_ALTIMAGE2 = 0x11,
		K_BUTTON_LSTICK_ALTIMAGE = 0xBC,
		K_BUTTON_RSTICK_ALTIMAGE = 0xBD,
		K_LASTDPAD = 0x17,
		K_LASTGAMEPADBUTTON_RANGE_2 = 0x17,
		K_ESCAPE = 0x1B,
		K_FIRSTGAMEPADBUTTON_RANGE_3 = 0x1C,
		K_APAD_UP = 0x1C,
		K_FIRSTAPAD = 0x1C,
		K_APAD_DOWN = 0x1D,
		K_APAD_LEFT = 0x1E,
		K_APAD_RIGHT = 0x1F,
		K_LASTAPAD = 0x1F,
		K_LASTGAMEPADBUTTON_RANGE_3 = 0x1F,
		K_SPACE = 0x20,
		K_GRAVE = 0x60,
		K_TILDE = 0x7E,
		K_BACKSPACE = 0x7F,
		K_ASCII_FIRST = 0x80,
		K_ASCII_181 = 0x80,
		K_ASCII_191 = 0x81,
		K_ASCII_223 = 0x82,
		K_ASCII_224 = 0x83,
		K_ASCII_225 = 0x84,
		K_ASCII_228 = 0x85,
		K_ASCII_229 = 0x86,
		K_ASCII_230 = 0x87,
		K_ASCII_231 = 0x88,
		K_ASCII_232 = 0x89,
		K_ASCII_233 = 0x8A,
		K_ASCII_236 = 0x8B,
		K_ASCII_241 = 0x8C,
		K_ASCII_242 = 0x8D,
		K_ASCII_243 = 0x8E,
		K_ASCII_246 = 0x8F,
		K_ASCII_248 = 0x90,
		K_ASCII_249 = 0x91,
		K_ASCII_250 = 0x92,
		K_ASCII_252 = 0x93,
		K_END_ASCII_CHARS = 0x94,
		K_COMMAND = 0x96,
		K_CAPSLOCK = 0x97,
		K_POWER = 0x98,
		K_PAUSE = 0x99,
		K_UPARROW = 0x9A,
		K_DOWNARROW = 0x9B,
		K_LEFTARROW = 0x9C,
		K_RIGHTARROW = 0x9D,
		K_ALT = 0x9E,
		K_CTRL = 0x9F,
		K_SHIFT = 0xA0,
		K_INS = 0xA1,
		K_DEL = 0xA2,
		K_PGDN = 0xA3,
		K_PGUP = 0xA4,
		K_HOME = 0xA5,
		K_END = 0xA6,
		K_F1 = 0xA7,
		K_F2 = 0xA8,
		K_F3 = 0xA9,
		K_F4 = 0xAA,
		K_F5 = 0xAB,
		K_F6 = 0xAC,
		K_F7 = 0xAD,
		K_F8 = 0xAE,
		K_F9 = 0xAF,
		K_F10 = 0xB0,
		K_F11 = 0xB1,
		K_F12 = 0xB2,
		K_F13 = 0xB3,
		K_F14 = 0xB4,
		K_F15 = 0xB5,
		K_KP_HOME = 0xB6,
		K_KP_UPARROW = 0xB7,
		K_KP_PGUP = 0xB8,
		K_KP_LEFTARROW = 0xB9,
		K_KP_5 = 0xBA,
		K_KP_RIGHTARROW = 0xBB,
		K_KP_END = 0xBC,
		K_KP_DOWNARROW = 0xBD,
		K_KP_PGDN = 0xBE,
		K_KP_ENTER = 0xBF,
		K_KP_INS = 0xC0,
		K_KP_DEL = 0xC1,
		K_KP_SLASH = 0xC2,
		K_KP_MINUS = 0xC3,
		K_KP_PLUS = 0xC4,
		K_KP_NUMLOCK = 0xC5,
		K_KP_STAR = 0xC6,
		K_KP_EQUALS = 0xC7,
		K_MOUSE1 = 0xC8,
		K_MOUSE2 = 0xC9,
		K_MOUSE3 = 0xCA,
		K_MOUSE4 = 0xCB,
		K_MOUSE5 = 0xCC,
		K_MWHEELDOWN = 0xCD,
		K_MWHEELUP = 0xCE,
		K_AUX1 = 0xCF,
		K_AUX2 = 0xD0,
		K_AUX3 = 0xD1,
		K_AUX4 = 0xD2,
		K_AUX5 = 0xD3,
		K_AUX6 = 0xD4,
		K_AUX7 = 0xD5,
		K_AUX8 = 0xD6,
		K_AUX9 = 0xD7,
		K_AUX10 = 0xD8,
		K_AUX11 = 0xD9,
		K_AUX12 = 0xDA,
		K_AUX13 = 0xDB,
		K_AUX14 = 0xDC,
		K_AUX15 = 0xDD,
		K_AUX16 = 0xDE,
		K_LAST_KEY = 0xDF
	};

	struct KeyState
	{
		int down;
		int repeats;
		int binding;
	};
	
	struct PlayerKeyState
	{
		int overstrikeMode;
		int anyKeyDown;
		KeyState keys[256];
	};

	struct cmd_function_s
	{
		cmd_function_s* next;
		const char* name;
		void (__cdecl* function)();
	};

	struct CmdArgs
	{
		int nesting;
		int localClientNum[8];
		int controllerIndex[8];
		int argc[8];
		const char** argv[8];
	};

	enum XAssetType
	{
		ASSET_TYPE_PHYSPRESET = 0x0,
		ASSET_TYPE_PHYSCOLLMAP = 0x1,
		ASSET_TYPE_XANIMPARTS = 0x2,
		ASSET_TYPE_XMODEL_SURFS = 0x3,
		ASSET_TYPE_XMODEL = 0x4,
		ASSET_TYPE_MATERIAL = 0x5,
		ASSET_TYPE_PIXELSHADER = 0x6,
		ASSET_TYPE_VERTEXSHADER = 0x7,
		ASSET_TYPE_VERTEXDECL = 0x8,
		ASSET_TYPE_TECHNIQUE_SET = 0x9,
		ASSET_TYPE_IMAGE = 0xA,
		ASSET_TYPE_SOUND = 0xB,
		ASSET_TYPE_SOUND_CURVE = 0xC,
		ASSET_TYPE_LOADED_SOUND = 0xD,
		ASSET_TYPE_CLIPMAP_SP = 0xE,
		ASSET_TYPE_CLIPMAP_MP = 0xF,
		ASSET_TYPE_COMWORLD = 0x10,
		ASSET_TYPE_GAMEWORLD_SP = 0x11,
		ASSET_TYPE_GAMEWORLD_MP = 0x12,
		ASSET_TYPE_MAP_ENTS = 0x13,
		ASSET_TYPE_FXWORLD = 0x14,
		ASSET_TYPE_GFXWORLD = 0x15,
		ASSET_TYPE_LIGHT_DEF = 0x16,
		ASSET_TYPE_UI_MAP = 0x17,
		ASSET_TYPE_FONT = 0x18,
		ASSET_TYPE_MENULIST = 0x19,
		ASSET_TYPE_MENU = 0x1A,
		ASSET_TYPE_LOCALIZE_ENTRY = 0x1B,
		ASSET_TYPE_WEAPON = 0x1C,
		ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1D,
		ASSET_TYPE_FX = 0x1E,
		ASSET_TYPE_IMPACT_FX = 0x1F,
		ASSET_TYPE_AITYPE = 0x20,
		ASSET_TYPE_MPTYPE = 0x21,
		ASSET_TYPE_CHARACTER = 0x22,
		ASSET_TYPE_XMODELALIAS = 0x23,
		ASSET_TYPE_RAWFILE = 0x24,
		ASSET_TYPE_STRINGTABLE = 0x25,
		ASSET_TYPE_LEADERBOARD = 0x26,
		ASSET_TYPE_STRUCTURED_DATA_DEF = 0x27,
		ASSET_TYPE_TRACER = 0x28,
		ASSET_TYPE_VEHICLE = 0x29,
		ASSET_TYPE_ADDON_MAP_ENTS = 0x2A,
		ASSET_TYPE_COUNT = 0x2B,
		ASSET_TYPE_STRING = 0x2B,
		ASSET_TYPE_ASSETLIST = 0x2C,
		ASSET_TYPE_INVALID = -1,
	};
	
	struct expression_s;
	struct Statement_s;
	struct menuDef_t;

	struct Material 
	{
		const char *name;
	};

	struct keyname_t
	{
		const char *name;
		int keynum;
	};
	
	struct rectDef_s
	{
		float x;
		float y;
		float w;
		float h;
		char horzAlign;
		char vertAlign;
	};

	static_assert(sizeof(rectDef_s) == 0x14);

	struct windowDef_t
	{
		const char* name;
		rectDef_s rect;
		rectDef_s rectClient;
		const char* group;
		int style;
		int border;
		int ownerDraw;
		int ownerDrawFlags;
		float borderSize;
		int staticFlags;
		int dynamicFlags[1];
		int nextTime;
		float foreColor[4];
		float backColor[4];
		float borderColor[4];
		float outlineColor[4];
		float disableColor[4];
		Material* background;
	};

	enum expDataType
	{
		VAL_INT = 0x0,
		VAL_FLOAT = 0x1,
		VAL_STRING = 0x2,
		NUM_INTERNAL_DATATYPES = 0x3,
		VAL_FUNCTION = 0x3,
		NUM_DATATYPES = 0x4,
	};

	struct ExpressionString
	{
		const char* string;
	};

	union operandInternalDataUnion
	{
		int intVal;
		float floatVal;
		ExpressionString stringVal;
		Statement_s* function;
	};

	struct Operand
	{
		expDataType dataType;
		operandInternalDataUnion internals;
	};

	enum operationEnum
	{
		OP_NOOP = 0x0,
		OP_RIGHTPAREN = 0x1,
		OP_MULTIPLY = 0x2,
		OP_DIVIDE = 0x3,
		OP_MODULUS = 0x4,
		OP_ADD = 0x5,
		OP_SUBTRACT = 0x6,
		OP_NOT = 0x7,
		OP_LESSTHAN = 0x8,
		OP_LESSTHANEQUALTO = 0x9,
		OP_GREATERTHAN = 0xA,
		OP_GREATERTHANEQUALTO = 0xB,
		OP_EQUALS = 0xC,
		OP_NOTEQUAL = 0xD,
		OP_AND = 0xE,
		OP_OR = 0xF,
		OP_LEFTPAREN = 0x10,
		OP_COMMA = 0x11,
		OP_BITWISEAND = 0x12,
		OP_BITWISEOR = 0x13,
		OP_BITWISENOT = 0x14,
		OP_BITSHIFTLEFT = 0x15,
		OP_BITSHIFTRIGHT = 0x16,
		OP_STATICDVARINT = 0x17,
		OP_FIRSTFUNCTIONCALL = 0x17,
		OP_STATICDVARBOOL = 0x18,
		OP_STATICDVARFLOAT = 0x19,
		OP_STATICDVARSTRING = 0x1A,
		OP_TOINT = 0x1B,
		OP_TOSTRING = 0x1C,
		OP_TOFLOAT = 0x1D,
		LAST_COMMONLY_CALLED_FUNCTION = 0x1D,
		OP_SIN = 0x1E,
		OP_COS = 0x1F,
		OP_MIN = 0x20,
		OP_MAX = 0x21,
		OP_MILLISECONDS = 0x22,
		OP_DVARINT = 0x23,
		OP_DVARBOOL = 0x24,
		OP_DVARFLOAT = 0x25,
		OP_DVARSTRING = 0x26,
		OP_STAT = 0x27,
		OP_UIACTIVE = 0x28,
		OP_FLASHBANGED = 0x29,
		OP_USINGVEHICLE = 0x2A,
		OP_MISSILECAM = 0x2B,
		OP_SCOPED = 0x2C,
		OP_SCOPEDTHERMAL = 0x2D,
		OP_SCOREBOARDVISIBLE = 0x2E,
		OP_INKILLCAM = 0x2F,
		OP_INKILLCAM_NPC = 0x30,
		OP_PLAYERFIELD = 0x31,
		OP_GET_PLAYER_PERK = 0x32,
		OP_SELECTINGLOCATION = 0x33,
		OP_SELECTINGDIRECTION = 0x34,
		OP_TEAMFIELD = 0x35,
		OP_OTHERTEAMFIELD = 0x36,
		OP_MARINESFIELD = 0x37,
		OP_OPFORFIELD = 0x38,
		OP_MENUISOPEN = 0x39,
		OP_WRITINGDATA = 0x3A,
		OP_INLOBBY = 0x3B,
		OP_INPRIVATEPARTY = 0x3C,
		OP_PRIVATEPARTYHOST = 0x3D,
		OP_PRIVATEPARTYHOSTINLOBBY = 0x3E,
		OP_ALONEINPARTY = 0x3F,
		OP_ADSJAVELIN = 0x40,
		OP_WEAPLOCKBLINK = 0x41,
		OP_WEAPATTACKTOP = 0x42,
		OP_WEAPATTACKDIRECT = 0x43,
		OP_WEAPLOCKING = 0x44,
		OP_WEAPLOCKED = 0x45,
		OP_WEAPLOCKTOOCLOSE = 0x46,
		OP_WEAPLOCKSCREENPOSX = 0x47,
		OP_WEAPLOCKSCREENPOSY = 0x48,
		OP_SECONDSASTIME = 0x49,
		OP_TABLELOOKUP = 0x4A,
		OP_TABLELOOKUPBYROW = 0x4B,
		OP_TABLEGETROWNUM = 0x4C,
		OP_LOCALIZESTRING = 0x4D,
		OP_LOCALVARINT = 0x4E,
		OP_LOCALVARBOOL = 0x4F,
		OP_LOCALVARFLOAT = 0x50,
		OP_LOCALVARSTRING = 0x51,
		OP_TIMELEFT = 0x52,
		OP_SECONDSASCOUNTDOWN = 0x53,
		OP_GAMEMSGWNDACTIVE = 0x54,
		OP_GAMETYPENAME = 0x55,
		OP_GAMETYPE = 0x56,
		OP_GAMETYPEDESCRIPTION = 0x57,
		OP_SCORE = 0x58,
		OP_FRIENDSONLINE = 0x59,
		OP_FOLLOWING = 0x5A,
		OP_SPECTATINGFREE = 0x5B,
		OP_STATRANGEBITSSET = 0x5C,
		OP_KEYBINDING = 0x5D,
		OP_ACTIONSLOTUSABLE = 0x5E,
		OP_HUDFADE = 0x5F,
		OP_MAXPLAYERS = 0x60,
		OP_ACCEPTINGINVITE = 0x61,
		OP_ISINTERMISSION = 0x62,
		OP_GAMEHOST = 0x63,
		OP_PARTYHASMISSINGMAPPACK = 0x64,
		OP_PARTYMISSINGMAPPACKERROR = 0x65,
		OP_ANYNEWMAPPACKS = 0x66,
		OP_AMISELECTED = 0x67,
		OP_PARTYSTATUSSTRING = 0x68,
		OP_ATTACHED_CONTROLLER_COUNT = 0x69,
		OP_IS_SPLIT_SCREEN_ONLINE_POSSIBLE = 0x6A,
		OP_SPLITSCREENPLAYERCOUNT = 0x6B,
		OP_GETPLAYERDATA = 0x6C,
		OP_GETPLAYERDATASPLITSCREEN = 0x6D,
		OP_EXPERIENCE_FOR_LEVEL = 0x6E,
		OP_LEVEL_FOR_EXPERIENCE = 0x6F,
		OP_IS_ITEM_UNLOCKED = 0x70,
		OP_IS_ITEM_UNLOCKEDSPLITSCREEN = 0x71,
		OP_DEBUG_PRINT = 0x72,
		OP_GETPLAYERDATA_ANYBOOLTRUE = 0x73,
		OP_WEAPON_CLASS_NEW = 0x74,
		OP_WEAPONNAME = 0x75,
		OP_ISRELOADING = 0x76,
		OP_SAVE_GAME_AVAILABLE = 0x77,
		OP_UNLOCKED_ITEM_COUNT = 0x78,
		OP_UNLOCKED_ITEM_COUNT_SPLITSCREEN = 0x79,
		OP_UNLOCKED_ITEM = 0x7A,
		OP_UNLOCKED_ITEM_SPLITSCREEN = 0x7B,
		OP_MAIL_SUBJECT = 0x7C,
		OP_MAIL_FROM = 0x7D,
		OP_MAIL_RECEIVED = 0x7E,
		OP_MAIL_BODY = 0x7F,
		OP_MAIL_LOOT_LOCALIZED = 0x80,
		OP_MAIL_GIVES_LOOT = 0x81,
		OP_ANY_NEW_MAIL = 0x82,
		OP_MAIL_TIME_TO_FOLLOWUP = 0x83,
		OP_MAIL_LOOT_TYPE = 0x84,
		OP_MAIL_RAN_LOTTERY = 0x85,
		OP_LOTTERY_LOOT_LOCALIZED = 0x86,
		OP_RADAR_IS_JAMMED = 0x87,
		OP_RADAR_JAM_INTENSITY = 0x88,
		OP_RADAR_IS_ENABLED = 0x89,
		OP_EMP_JAMMED = 0x8A,
		OP_PLAYERADS = 0x8B,
		OP_WEAPON_HEAT_ACTIVE = 0x8C,
		OP_WEAPON_HEAT_VALUE = 0x8D,
		OP_WEAPON_HEAT_OVERHEATED = 0x8E,
		OP_SPLASH_TEXT = 0x8F,
		OP_SPLASH_DESCRIPTION = 0x90,
		OP_SPLASH_MATERIAL = 0x91,
		OP_SPLASH_HAS_ICON = 0x92,
		OP_SPLASH_ROWNUM = 0x93,
		OP_GETFOCUSED_NAME = 0x94,
		OP_GETFOCUSED_X = 0x95,
		OP_GETFOCUSED_Y = 0x96,
		OP_GETFOCUSED_W = 0x97,
		OP_GETFOCUSED_H = 0x98,
		OP_GETITEMDEF_X = 0x99,
		OP_GETITEMDEF_Y = 0x9A,
		OP_GETITEMDEF_W = 0x9B,
		OP_GETITEMDEF_H = 0x9C,
		OP_PLAYLISTFIELD = 0x9D,
		OP_SCOREBOARD_EXTERNALMUTE_NOTICE = 0x9E,
		OP_CLIENT_MATCH_DATA = 0x9F,
		OP_CLIENT_MATCH_DATA_DEF = 0xA0,
		OP_GET_MAP_NAME = 0xA1,
		OP_GET_MAP_IMAGE = 0xA2,
		OP_GET_MAP_CUSTOM = 0xA3,
		OP_GET_MIGRATION_STATUS = 0xA4,
		OP_GET_PLAYERCARD_INFO = 0xA5,
		OP_IS_OFFLINE_PROFILE_SELECTED = 0xA6,
		OP_COOP_PLAYERFIELD = 0xA7,
		OP_IS_COOP = 0xA8,
		OP_GETPARTYSTATUS = 0xA9,
		OP_GETSEARCHPARAMS = 0xAA,
		OP_GETTIMEPLAYED = 0xAB,
		OP_IS_SELECTED_PLAYER_FRIEND = 0xAC,
		OP_GETCHARBYINDEX = 0xAD,
		OP_GETPLAYERPROFILEDATA = 0xAE,
		OP_IS_PROFILE_SIGNED_IN = 0xAF,
		OP_GET_WAIT_POPUP_STATUS = 0xB0,
		NUM_OPERATORS = 0xB1,
	};

	struct ItemFloatExpressionEntry
	{
		int target;
		const char *s1;
		const char *s2;
	};

	union entryInternalData
	{
		operationEnum op;
		Operand operand;
	};

	struct expressionEntry
	{
		int type;
		entryInternalData data;
	};

	struct UIFunctionList
	{
		int totalFunctions;
		Statement_s** functions;
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		unsigned char color[4];
	};

	static_assert(sizeof(DvarValue) == 0x10);

	struct enum_limit
	{
		int stringCount;
		const char** strings;
	};

	struct int_limit
	{
		int min;
		int max;
	};

	struct float_limit
	{
		float min;
		float max;
	};

	union DvarLimits
	{
		enum_limit enumeration;
		int_limit integer;
		float_limit value;
		float_limit vector;
	};

	static_assert(sizeof(DvarLimits) == 0x10);
	
	struct StaticDvar
	{
		dvar_t* dvar;
		char* dvarName;
	};

	struct StaticDvarList
	{
		int numStaticDvars;
		StaticDvar** staticDvars;
	};

	struct StringList
	{
		int totalStrings;
		const char** strings;
	};

	struct ExpressionSupportingData
	{
		UIFunctionList uifunctions;
		StaticDvarList staticDvarList;
		StringList uiStrings;
	};

	struct Statement_s
	{
		int numEntries;
		expressionEntry* entries;
		ExpressionSupportingData* supportingData;
		int lastExecuteTime;
		Operand lastResult;
	};

	enum EventType
	{
		EVENT_UNCONDITIONAL = 0x0,
		EVENT_IF = 0x1,
		EVENT_ELSE = 0x2,
		EVENT_SET_LOCAL_VAR_BOOL = 0x3,
		EVENT_SET_LOCAL_VAR_INT = 0x4,
		EVENT_SET_LOCAL_VAR_FLOAT = 0x5,
		EVENT_SET_LOCAL_VAR_STRING = 0x6,
		EVENT_COUNT = 0x7,
	};

	struct MenuEventHandlerSet;
	
	struct ConditionalScript
	{
		MenuEventHandlerSet* eventHandlerSet;
		Statement_s* eventExpression;
	};

	struct SetLocalVarData
	{
		const char* localVarName;
		Statement_s* expression;
	};

	union EventData
	{
		const char* unconditionalScript;
		ConditionalScript* conditionalScript;
		struct MenuEventHandlerSet* elseScript;
		SetLocalVarData* setLocalVarData;
	};

	struct __declspec(align(4)) MenuEventHandler
	{
		EventData eventData;
		EventType eventType;
	};

	struct MenuEventHandlerSet
	{
		int eventHandlerCount;
		MenuEventHandler** eventHandlers;
	};

	struct ItemKeyHandler
	{
		int key;
		MenuEventHandlerSet* action;
		ItemKeyHandler* next;
	};

	struct columnInfo_s
	{
		int pos;
		int width;
		int maxChars;
		int alignment;
	};

	struct listBoxDef_s
	{
		int mousePos;
		int startPos[1];
		int endPos[1];
		int drawPadding;
		float elementWidth;
		float elementHeight;
		int elementStyle;
		int numColumns;
		columnInfo_s columnInfo[16];
		MenuEventHandlerSet* onDoubleClick;
		int notselectable;
		int noScrollBars;
		int usePaging;
		float selectBorder[4];
		Material* selectIcon;
	};

	struct editFieldDef_s
	{
		float minVal;
		float maxVal;
		float defVal;
		float range;
		int maxChars;
		int maxCharsGotoNext;
		int maxPaintChars;
		int paintOffset;
	};

	struct multiDef_s
	{
		const char* dvarList[32];
		const char* dvarStr[32];
		float dvarValue[32];
		int count;
		int strDef;
	};

	struct newsTickerDef_s
	{
		int feedId;
		int speed;
		int spacing;
		int lastTime;
		int start;
		int end;
		float x;
	};

	struct textScrollDef_s
	{
		int startTime;
	};

	union itemDefData_t
	{
		listBoxDef_s* listBox;
		editFieldDef_s* editField;
		multiDef_s* multi;
		const char* enumDvarName;
		newsTickerDef_s* ticker;
		textScrollDef_s* scroll;
		void* data;
	};

	struct ItemFloatExpression
	{
		int target;
		Statement_s* expression;
	};

	union SoundAliasFlags
	{
#pragma warning(push)
#pragma warning(disable: 4201)
		struct
		{
			unsigned int looping : 1;		// & 1	/ 0x1			/ 0000 0000 0000 0001
			unsigned int isMaster : 1;		// & 2	/ 0x2			/ 0000 0000 0000 0010
			unsigned int isSlave : 1;		// & 4	/ 0x4			/ 0000 0000 0000 0100
			unsigned int fullDryLevel : 1;	//	& 8	/ 0x8			/ 0000 0000 0000 1000
			unsigned int noWetLevel : 1;	// & 16	/ 0x10			/ 0000 0000 0001 0000
			unsigned int unknown : 1;		// & 32	/ 0x20			/ 0000 0000 0010 0000
			unsigned int unk_is3D : 1;		// & 64	/ 0x40			/ 0000 0000 0100 0000		// CONFIRMED IW4 IW5
			unsigned int type : 2;			// & 384	/ 0x180		/ 0000 0001 1000 0000		// CONFIRMED IW4 IW5
			unsigned int channel : 6;		// & 32256	/ 0x7E00	/ 0111 1110 0000 0000		// CONFIRMED IW4 IW5
		};
#pragma warning(pop)
		unsigned int intValue;
	};
	
	struct snd_alias_t
	{
		const char* aliasName;
		const char* subtitle;
		const char* secondaryAliasName;
		const char* chainAliasName;
		const char* mixerGroup;
		void* soundFile;
		int sequence;
		float volMin;
		float volMax;
		float pitchMin;
		float pitchMax;
		float distMin;
		float distMax;
		float velocityMin;
		SoundAliasFlags flags;
		union
		{
			float slavePercentage;
			float masterPercentage;
		} ___u15;
		float probability;
		float lfePercentage;
		float centerPercentage;
		int startDelay;
		void* volumeFalloffCurve;
		float envelopMin;
		float envelopMax;
		float envelopPercentage;
		void* speakerMap;
	};
	
	struct snd_alias_list_t
	{
		const char* aliasName;
		snd_alias_t* head;
		unsigned int count;
	};

	struct itemDef_s
	{
		windowDef_t window;
		rectDef_s textRect[1];
		int type;
		int dataType;
		int alignment;
		int fontEnum;
		int textAlignMode;
		float textalignx;
		float textaligny;
		float textscale;
		int textStyle;
		int gameMsgWindowIndex;
		int gameMsgWindowMode;
		const char* text;
		int itemFlags;
		menuDef_t* parent;
		MenuEventHandlerSet* mouseEnterText;
		MenuEventHandlerSet* mouseExitText;
		MenuEventHandlerSet* mouseEnter;
		MenuEventHandlerSet* mouseExit;
		MenuEventHandlerSet* action;
		MenuEventHandlerSet* accept;
		MenuEventHandlerSet* onFocus;
		MenuEventHandlerSet* leaveFocus;
		const char* dvar;
		const char* dvarTest;
		ItemKeyHandler* onKey;
		const char* enableDvar;
		const char* localVar;
		int dvarFlags;
		snd_alias_list_t* focusSound;
		float special;
		int cursorPos[1];
		itemDefData_t typeData;
		int imageTrack;
		int floatExpressionCount;
		ItemFloatExpression* floatExpressions;
		Statement_s* visibleExp;
		Statement_s* disabledExp;
		Statement_s* textExp;
		Statement_s* materialExp;
		float glowColor[4];
		bool decayActive;
		int fxBirthTime;
		int fxLetterTime;
		int fxDecayStartTime;
		int fxDecayDuration;
		int lastSoundPlayedTime;
	};

	struct menuTransition
	{
		int transitionType;
		int targetField;
		int startTime;
		float startVal;
		float endVal;
		float time;
		int endTriggerType;
	};

	struct menuDef_t
	{
		windowDef_t window;
		const char* font;
		int fullScreen;
		int itemCount;
		int fontIndex;
		int cursorItem[1];
		int fadeCycle;
		float fadeClamp;
		float fadeAmount;
		float fadeInAmount;
		float blurRadius;
		MenuEventHandlerSet* onOpen;
		MenuEventHandlerSet* onCloseRequest;
		MenuEventHandlerSet* onClose;
		MenuEventHandlerSet* onESC;
		ItemKeyHandler* onKey;
		Statement_s* visibleExp;
		const char* allowedBinding;
		const char* soundName;
		int imageTrack;
		float focusColor[4];
		Statement_s* rectXExp;
		Statement_s* rectYExp;
		Statement_s* rectWExp;
		Statement_s* rectHExp;
		Statement_s* openSoundExp;
		Statement_s* closeSoundExp;
		itemDef_s** items;
		menuTransition scaleTransition[1];
		menuTransition alphaTransition[1];
		menuTransition xTransition[1];
		menuTransition yTransition[1];
		ExpressionSupportingData* expressionData;
	};

	struct MenuList
	{
		const char* name;
		int menuCount;
		menuDef_t** menus;
	};

	union XAssetHeader
	{
		void* data;
		Material* material;
		Font_s* font;
		MenuList* menuList;
		menuDef_t* menu;
	};
	
	struct XAsset
	{
		XAssetType type;
		XAssetHeader header;
	};

	struct XAssetEntry
	{
		XAsset asset;
		char zoneIndex;
		volatile char inuseMask;
		bool printedMissingAsset;
		unsigned short nextHash;
		unsigned short nextOverride;
	};
}
