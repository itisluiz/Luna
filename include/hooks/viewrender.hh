#ifndef LUNA_HOOK_VIEWRENDER_HH
#define LUNA_HOOK_VIEWRENDER_HH
#include <sdk/source.hh>
#include <MinHook.h>

#ifdef _WIN64
#define EDX_PARAM ,
#define EDX_ARG ,
#else
#define EDX_PARAM ,void* edx,
#define EDX_ARG ,edx,
#endif

namespace hooks::viewrender
{
	bool __fastcall hook(sdk::IBaseClientDLL* baseClient EDX_PARAM sdk::vrect_t* rect);
	extern decltype(&hook) original;

	MH_STATUS apply();
}

#endif
