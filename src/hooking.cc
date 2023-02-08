#include <hooking.hh>
#include <MinHook.h>
#include <windows/msgbox.hh>

#include <hooks/luacycle.hh>
#include <hooks/luashutdown.hh>
#include <hooks/luarunstring.hh>
#include <hooks/luarunstringex.hh>
#include <hooks/insertcommand.hh>
#include <hooks/viewrender.hh>

using applyFn = MH_STATUS();

void* vFuncAddress(void* object, size_t index)
{
	void** vTable{ *reinterpret_cast<void***>(object) };
	return vTable[index];
}

bool applyHook(const char* hookName, applyFn* apply)
{
	MH_STATUS mhResult = apply();
	if (mhResult != MH_OK)
	{
		msgbox::message << "Failed to apply '" << hookName << "' hook" << msgbox::ShowOptions(MB_ICONERROR);
		return false;
	}

	return true;
}

bool loadHooks()
{
	MH_STATUS mhResult;
	mhResult = MH_Initialize();
	if (mhResult != MH_OK)
	{
		msgbox::message << "Failed to initialize MinHook (" << MH_StatusToString(mhResult) << ')' << msgbox::ShowOptions(MB_ICONERROR);
		return false;
	}

	if (!applyHook("luacycle", hooks::luacycle::apply))
		return false;

	if (!applyHook("luashutdown", hooks::luashutdown::apply))
		return false;

	if (!applyHook("luarunstring", hooks::luarunstring::apply))
		return false;

	if (!applyHook("luarunstringex", hooks::luarunstringex::apply))
		return false;

	if (!applyHook("insertcommand", hooks::insertcommand::apply))
		return false;

	if (!applyHook("viewrender", hooks::viewrender::apply))
		return false;

	mhResult = MH_EnableHook(MH_ALL_HOOKS);
	if (mhResult != MH_OK)
	{
		msgbox::message << "Failed to enable hooks (" << MH_StatusToString(mhResult) << ')' << msgbox::ShowOptions(MB_ICONERROR);
		return false;
	}

	return true;
}

void unloadHooks()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}