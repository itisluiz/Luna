#include <hooks/luashutdown.hh>
#include <features/dumper.hh>
#include <features/overrider.hh>
#include <features/luamanager.hh>
#include <hooking.hh>
#include <imports.hh>

#define VTABLE_INDEX 56

namespace hooks::luashutdown
{
	decltype(&hook) original;

	bool __fastcall hook(sdk::ILuaInterface* luaInterface)
	{
		if (luaInterface->IsClient())
		{
			features::dumper::reset();
			features::overrider::reset();
		}

		features::luamanager::clearQueue(luaInterface);

		return original(luaInterface);
	}

	MH_STATUS apply()
	{
		return MH_CreateHook(vFuncAddress(imports::iLuaShared->GetLuaInterface(sdk::State::MENU), VTABLE_INDEX), hook, reinterpret_cast<void**>(&original));
	}
}