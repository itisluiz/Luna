#include <hooks/luaeditcvar.hh>
#include <hooking.hh>
#include <memory/pe.hh>
#include <memory/pattern.hh>
#include <settings.hh>

#ifdef _WIN64
#define CALLBACKFN_OFFSET 3
#else
#define CALLBACKFN_OFFSET 4
#endif

namespace hooks::luaeditcvar
{
	decltype(&hook) original;

	sdk::ConVar* __cdecl hook(sdk::ConVar* cvar)
	{
		if (!settings::luaUnrestrictCmd)
			return original(cvar);

		if (!std::strcmp(cvar->m_pszName, "name"))
			reinterpret_cast<uintptr_t*>(&cvar->m_fnChangeCallback)[CALLBACKFN_OFFSET] = 0;

		return cvar;
	}

	MH_STATUS apply()
	{
		PESection section(".text", "client.dll");
#ifdef _WIN64
		Pattern pattern("48 8B 01 BA ?? ?? ?? ?? 48 8B D9 FF 50", -6);
#else
		Pattern pattern("8B CE 68 ?? ?? ?? ?? 8B 06 8B 40", -7);
#endif

		return MH_CreateHook(pattern.locate(section.start(), section.end()), hook, reinterpret_cast<void**>(&original));
	}
}

