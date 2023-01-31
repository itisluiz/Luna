#include <windows/entry.hh>
#include <windows/thread.hh>

HMODULE hLibrary{ NULL };

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		hLibrary = hinstDLL;
		DisableThreadLibraryCalls(hinstDLL);
		HANDLE hMainThread{ CreateThread(NULL, 0, mainThread, NULL, 0, NULL) };

		if (!hMainThread)
			return FALSE;

		CloseHandle(hMainThread);
	}

	return TRUE;
}

void unloadLibrary(DWORD exitCode)
{
	HANDLE hUnloadThread{ CreateThread(NULL, 0, unloadThread, &exitCode, 0, NULL) };

	if (hUnloadThread)
		CloseHandle(hUnloadThread);
}