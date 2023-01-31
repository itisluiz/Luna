#ifndef LUNA_HOOK_LUARUNSTRINGEX_HH
#define LUNA_HOOK_LUARUNSTRINGEX_HH
#include <sdk/luaifaces.hh>
#include <MinHook.h>

#ifdef _WIN64
#define EDX_PARAM ,
#define EDX_ARG ,
#else
#define EDX_PARAM ,void* edx,
#define EDX_ARG ,edx,
#endif

namespace hooks::luarunstringex
{
	bool __fastcall hook(sdk::ILuaInterface* luaInterface EDX_PARAM const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns);
	extern decltype(&hook) original;

	MH_STATUS apply();
}

#endif
