#include <windows/thread.hh>
#include <windows/entry.hh>
#include <initdeinit.hh>

DWORD WINAPI mainThread(LPVOID)
{
	if (!init())
	{
		deinit();
		FreeLibraryAndExitThread(hLibrary, -1);
	}

	return 0;
}

DWORD WINAPI unloadThread(LPVOID pExitCode)
{
	deinit();
	Sleep(5);

	FreeLibraryAndExitThread(hLibrary, *reinterpret_cast<DWORD*>(pExitCode));
}