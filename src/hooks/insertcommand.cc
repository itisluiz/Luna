#include <hooks/insertcommand.hh>
#include <hooking.hh>
#include <imports.hh>
#include <command.hh>

#define VTABLE_INDEX 106

namespace hooks::insertcommand
{
	decltype(&hook) original;

	bool __cdecl hook(const char* szCmdString)
	{
		if (runCommand(szCmdString))
			return false;

		return original(szCmdString);
	}

	MH_STATUS apply()
	{
		uint8_t* clientcmd_unrestricted{ reinterpret_cast<uint8_t*>(vFuncAddress(imports::iEngineClient, VTABLE_INDEX)) };
		while (*clientcmd_unrestricted != 0xE8 && *clientcmd_unrestricted != 0xE9)
			++clientcmd_unrestricted;

		int32_t* jumpOffset{ reinterpret_cast<int32_t*>(++clientcmd_unrestricted) };
		return MH_CreateHook(clientcmd_unrestricted + *jumpOffset + sizeof(int32_t), hook, reinterpret_cast<void**>(&original));
	}
}
