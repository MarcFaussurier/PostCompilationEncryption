#if _WIN64
# error "Only x86 supported"
#endif
#define DEBUG 0
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string.h>
#include <psapi.h>
#include <detours.h>
#include "printf.hpp"
#include "file.hpp"
#include "console.hpp"
#include "detours/OpenFile.hpp"
#include "detours/CreateFile.hpp"
#include "detours/ReadFile.hpp"
#include "detours/WriteFile.hpp"

__declspec(dllexport) void __cdecl Function1(void)
{
    printf("OK!");
}

DWORD WINAPI ConsoleThread(LPVOID lpParam)
{
	LONG Error;

#if DEBUG
    new_console();
#endif
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID &)MS_OpenFile, SH_OpenFile);
   // DetourAttach(&(PVOID &)MS_OpenFileA, SH_OpenFile);
    DetourAttach(&(PVOID &)MS_CreateFile, SH_CreateFile);
    DetourAttach(&(PVOID &)MS_CreateFileA, SH_CreateFileA);

	DetourAttach(&(PVOID &)MS_ReadFile, SH_ReadFile);
    DetourAttach(&(PVOID &)MS_WriteFile, SH_WriteFile);
    Error = DetourTransactionCommit();
    #if DEBUG
	if (Error == NO_ERROR)
		printf("Hooked Success\n");
	else
	    printf("Hook Error\n");
    #endif
    	return 0;

}

DWORD id;
HANDLE hndl;
#include "../crypto/updater_key.hpp"
#include <Windows.h>
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)  
{
    LPSTR lps;

    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
            lps = GetCommandLineA();
            if (!strstr(lps, UPDATER_KEY))
            {
                WinExec("\"Shaiya Updater.exe\"", SW_HIDE);
                exit(0);
            }

        	hndl = CreateThread(NULL, 0, ConsoleThread, 0, 0, &id);
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }
    return (TRUE);  
}