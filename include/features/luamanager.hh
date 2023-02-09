#ifndef LUNA_FEATURE_LUAMANAGER
#define LUNA_FEATURE_LUAMANAGER
#include <string>
#include <sdk/luaifaces.hh>

namespace features::luamanager
{
	int runHook(sdk::ILuaInterface* luaInterface, const std::string& hookName, size_t args = 0, size_t rets = 0);
	int runHook(sdk::State state, const std::string& hookName, size_t args = 0, size_t rets = 0);
	bool runScriptOrFile(sdk::ILuaInterface* luaInterface, const std::string& script, bool silent = false);
	bool runScriptOrFile(sdk::State state, const std::string& script, bool silent = false);
	void handleQueue(sdk::ILuaInterface* luaInterface);
	void clearQueue(sdk::ILuaInterface* luaInterface);
	bool enqueueScript(const std::string& script, sdk::State state, bool checkAvailability = true);

	sdk::State toState(const std::string& stateString);
	sdk::State toState(sdk::ILuaInterface* luaInterface);
}

#endif
