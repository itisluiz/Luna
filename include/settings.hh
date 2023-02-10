#ifndef LUNA_SETTINGS_HH
#define LUNA_SETTINGS_HH
#include <queue>
#include <string>
#include <sdk/luaifaces.hh>

namespace settings
{
	extern bool luaDump;
	extern bool luaOverride;
	extern bool luaUnrestrictCmd;
	extern std::string luaHkPaint;
	extern std::string luaHkCreateMove;

	namespace internals
	{
		extern std::queue<std::string> stateQueue[sdk::State::STATE_MAX];
	}
}

#endif