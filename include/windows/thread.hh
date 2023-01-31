#ifndef LUNA_WINDOWS_THREAD_HH
#define LUNA_WINDOWS_THREAD_HH
#include <Windows.h>

DWORD WINAPI mainThread(LPVOID);
DWORD WINAPI unloadThread(LPVOID pExitCode);

#endif