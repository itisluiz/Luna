#include <hooks/luarunstring.hh>
#include <features/dumper.hh>
#include <features/overrider.hh>
#include <hooking.hh>
#include <imports.hh>

#define VTABLE_INDEX 92

namespace hooks::luarunstring
{
	decltype(&hook) original;

	bool __fastcall hook(sdk::ILuaInterface* luaInterface EDX_PARAM const char* filename, const char* path, const char* stringToRun, bool run, bool showErrors)
	{
		if (luaInterface->IsClient())
		{
			features::dumper::dumpScript(filename, stringToRun);
			std::optional<std::string> overrideScript{ features::overrider::overrideScript(filename) };

			if (overrideScript.has_value())
				return original(luaInterface EDX_ARG filename, path, overrideScript.value().c_str(), run, showErrors);
		}

		return original(luaInterface EDX_ARG "", "", stringToRun, run, showErrors);
	}

	MH_STATUS apply()
	{
		return MH_CreateHook(vFuncAddress(imports::iLuaShared->GetLuaInterface(sdk::State::MENU), VTABLE_INDEX), hook, reinterpret_cast<void**>(&original));
	}
}

