#ifndef LUNA_HOOK_LUASHUTDOWN_HH
#define LUNA_HOOK_LUASHUTDOWN_HH
#include <sdk/luaifaces.hh>
#include <MinHook.h>

#ifdef _WIN64
#define EDX_PARAM ,
#define EDX_ARG ,
#else
#define EDX_PARAM ,void* edx,
#define EDX_ARG ,edx,
#endif

namespace hooks::luashutdown
{
	bool __fastcall hook(sdk::ILuaInterface* luaInterface);
	extern decltype(&hook) original;

	MH_STATUS apply();
}

#endif
