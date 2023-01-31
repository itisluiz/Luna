#include <hooks/luacycle.hh>
#include <features/dumper.hh>
#include <features/overrider.hh>
#include <features/luamanager.hh>
#include <hooking.hh>
#include <imports.hh>

#define VTABLE_INDEX 57

namespace hooks::luacycle
{
	decltype(&hook) original;

	bool __fastcall hook(sdk::ILuaInterface* luaInterface)
	{
		bool curInGame{ imports::iEngineClient->IsInGame() };
		static bool lastInGame{ curInGame };

		if (lastInGame != curInGame)
		{
			if (curInGame)
			{
				features::dumper::stats();
				features::overrider::stats();
			}

			lastInGame = curInGame;
		}

		features::luamanager::handleQueues(luaInterface);

		return original(luaInterface);
	}

	MH_STATUS apply()
	{
		return MH_CreateHook(vFuncAddress(imports::iLuaShared->GetLuaInterface(sdk::State::MENU), VTABLE_INDEX), hook, reinterpret_cast<void**>(&original));
	}
}