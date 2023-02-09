#ifndef LUNA_HOOK_CREATEMOVE_HH
#define LUNA_HOOK_CREATEMOVE_HH
#include <sdk/luaifaces.hh>
#include <MinHook.h>

#ifdef _WIN64
#define EDX_PARAM ,
#define EDX_ARG ,
#else
#define EDX_PARAM ,void* edx,
#define EDX_ARG ,edx,
#endif

namespace hooks::createmove
{
	bool __fastcall hook(sdk::IClientMode* clientMode EDX_PARAM float flInputSampleTime, sdk::CUserCmd* cmd);
	extern decltype(&hook) original;

	MH_STATUS apply();
}

#endif
