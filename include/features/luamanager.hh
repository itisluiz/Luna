#ifndef LUNA_FEATURE_LUAMANAGER
#define LUNA_FEATURE_LUAMANAGER
#include <string>
#include <sdk/luaifaces.hh>

namespace features::luamanager
{
	void handleQueues(sdk::ILuaInterface* luaInterface);
	void clearQueue(sdk::ILuaInterface* luaInterface);
	bool enqueueScript(const std::string& script, sdk::State state, bool checkAvailability = true);

	sdk::State toState(const std::string& stateString);
	sdk::State toState(sdk::ILuaInterface* luaInterface);
}

#endif
