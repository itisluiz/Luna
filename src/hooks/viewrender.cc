#include <hooks/viewrender.hh>
#include <hooking.hh>
#include <imports.hh>
#include <settings.hh>
#include <features/luamanager.hh>


#define VTABLE_INDEX 26

namespace hooks::viewrender
{
	decltype(&hook) original;

	bool __fastcall hook(sdk::IBaseClientDLL* baseClient EDX_PARAM sdk::vrect_t* rect)
	{
		bool result{ original(baseClient EDX_ARG rect) };

		if (settings::luaSafePaint.empty() || imports::iEngineClient->IsTakingScreenshot() || imports::iEngineClient->IsRecordingMovie())
			return result;

		imports::iSurface->StartDrawing();
		features::luamanager::runHook(sdk::State::CLIENT, settings::luaSafePaint);
		imports::iSurface->FinishDrawing();

		return result;
	}

	MH_STATUS apply()
	{
		return MH_CreateHook(vFuncAddress(imports::iBaseClient, VTABLE_INDEX), hook, reinterpret_cast<void**>(&original));
	}
}