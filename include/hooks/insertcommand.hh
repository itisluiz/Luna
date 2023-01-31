#ifndef LUNA_HOOK_CLIENTCMD_HH
#define LUNA_HOOK_CLIENTCMD_HH
#include <sdk/source.hh>
#include <MinHook.h>

#ifdef _WIN64
#define EDX_PARAM ,
#define EDX_ARG ,
#else
#define EDX_PARAM ,void* edx,
#define EDX_ARG ,edx,
#endif

namespace hooks::insertcommand
{
	bool __cdecl hook(const char* szCmdString);
	extern decltype(&hook) original;

	MH_STATUS apply();
}

#endif
