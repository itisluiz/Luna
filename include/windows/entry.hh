#ifndef LUNA_WINDOWS_ENTRY_HH
#define LUNA_WINDOWS_ENTRY_HH
#include <Windows.h>

extern HMODULE hLibrary;
void unloadLibrary(DWORD exitCode);

#endif