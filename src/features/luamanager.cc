#include <features/luamanager.hh>
#include <features/printer.hh>
#include <windows/path.hh>
#include <settings.hh>
#include <imports.hh>
#include <Windows.h>

#define LUAMANAGER_FOLDERNAME "userscripts"

namespace features::luamanager
{
	static const char* const stateName[sdk::State::STATE_MAX]{ "client", "server", "menu" };

	static bool runScript(sdk::ILuaInterface* luaInterface, const std::string& script)
	{
		static std::optional<fs::path> path;

		if (!path.has_value())
		{
			path = getAppdata(fs::path(LUAMANAGER_FOLDERNAME));

			if (!path.has_value())
			{
				console << sdk::Color{ 255, 100, 100, 255 } << "Failed to acquire folder for the Lua user scripts" "\n";
				return false;
			}
		}

		std::optional<fs::path> scriptAsPath;
		if (script.size() < MAX_PATH)
		{
			scriptAsPath = script;

			if (scriptAsPath.value().is_relative())
				scriptAsPath = path.value() / scriptAsPath.value();

			if (!fs::exists(scriptAsPath.value()))
				scriptAsPath = std::nullopt;
		}

		console << "Running script as " << (scriptAsPath.has_value() ? "file" : "string") << " on " << toState(luaInterface) << '\n';

		if (scriptAsPath.has_value() && imports::lua_loadfile(luaInterface->state, scriptAsPath.value().string().c_str()) 
			|| !scriptAsPath.has_value() && imports::lua_loadstring(luaInterface->state, script.c_str()))
		{
			console << "Lua error: " << sdk::Color{255, 100, 100, 255} << luaInterface->GetString() << '\n';
			luaInterface->Pop();
			return false;
		}
	
		if (luaInterface->PCall(0, -1, 0))
		{
			console << "Lua run error: " << sdk::Color{ 255, 100, 100, 255 } << luaInterface->GetString() << '\n';
			luaInterface->Pop();
			return false;
		}

		return true;
	}

	void handleQueues(sdk::ILuaInterface* luaInterface)
	{
		sdk::State state{ toState(luaInterface) };

		if (state >= sdk::STATE_MAX)
			return;

		std::queue<std::string>& scriptQueue{ settings::internals::stateQueue[state] };
		while (!scriptQueue.empty())
		{
			std::string& script{ scriptQueue.front() };

			if (!script.empty())
				runScript(luaInterface, script);

			scriptQueue.pop();
		}
	}

	void clearQueue(sdk::ILuaInterface* luaInterface)
	{
		sdk::State state{ toState(luaInterface) };

		if (state >= sdk::STATE_MAX)
			return;

		std::queue<std::string>& scriptQueue{ settings::internals::stateQueue[state] };
		while (!scriptQueue.empty())
			scriptQueue.pop();
	}

	bool enqueueScript(const std::string& script, sdk::State state, bool checkAvailability)
	{
		if (state >= sdk::STATE_MAX)
			return false;

		if (checkAvailability && !imports::iLuaShared->GetLuaInterface(state))
			return false;

		settings::internals::stateQueue[state].push(script);
		return true;
	}

	sdk::State toState(const std::string& stateString)
	{
		std::string lowerString;

		for (const char c : stateString)
			lowerString.push_back(std::tolower(c));

		for (uint8_t state{ sdk::State::CLIENT }; state < sdk::State::STATE_MAX; ++state)
		{
			if (lowerString == stateName[state])
				return static_cast<sdk::State>(state);
		}

		return sdk::State::STATE_MAX;
	}

	sdk::State toState(sdk::ILuaInterface* luaInterface)
	{
		if (!luaInterface)
			return sdk::State::STATE_MAX;

		if (luaInterface->IsClient())
			return sdk::State::CLIENT;

		if (luaInterface->IsServer())
			return sdk::State::SERVER;

		if (luaInterface->IsMenu())
			return sdk::State::MENU;

		return sdk::State::STATE_MAX;
	}

}
