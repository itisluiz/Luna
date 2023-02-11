#ifndef LUNA_HOOK_LUARUNCMD_HH
#define LUNA_HOOK_LUARUNCMD_HH
#include <sdk/luaifaces.hh>
#include <MinHook.h>

#ifdef _WIN64
#define EDX_PARAM ,
#define EDX_ARG ,
#else
#define EDX_PARAM ,void* edx,
#define EDX_ARG ,edx,
#endif

namespace hooks::luaruncmd
{
	const char* __cdecl hook(const char* command);
	extern decltype(&hook) original;

	MH_STATUS apply();
}

#endif
