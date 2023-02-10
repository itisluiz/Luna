#ifndef LUNA_HOOK_LUAEDITCVAR_HH
#define LUNA_HOOK_LUAEDITCVAR_HH
#include <sdk/luaifaces.hh>
#include <MinHook.h>

#ifdef _WIN64
#define EDX_PARAM ,
#define EDX_ARG ,
#else
#define EDX_PARAM ,void* edx,
#define EDX_ARG ,edx,
#endif

namespace hooks::luaeditcvar
{
	sdk::ConVar* __cdecl hook(sdk::ConVar* cvar);
	extern decltype(&hook) original;

	MH_STATUS apply();
}

#endif
