#include <hooks/luaruncmd.hh>
#include <hooking.hh>
#include <memory/pe.hh>
#include <memory/pattern.hh>
#include <settings.hh>

namespace hooks::luaruncmd
{
	decltype(&hook) original;

	const char* __cdecl hook(const char* command)
	{
		if (settings::luaUnrestrictCmd)
			return nullptr;

		return original(command);
	}

	MH_STATUS apply()
	{
		PESection section(".text", "client.dll");
#ifdef _WIN64
		Pattern pattern("48 8B F9 80 B8 E0", -13);
#else
		Pattern pattern("57 8B 7D 08 80 B8 90", -8);
#endif

		return MH_CreateHook(pattern.locate(section.start(), section.end()), hook, reinterpret_cast<void**>(&original));
	}
}

