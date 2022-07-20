#if _WIN64
# error "Only x86 supported"
#endif
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
#include "detours/ReadFile.hpp"

DWORD WINAPI ConsoleThread(LPVOID lpParam)
{
	LONG Error;

    new_console();
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID &)MS_OpenFile, SH_OpenFile);
	DetourAttach(&(PVOID &)MS_ReadFile, SH_ReadFile);
    Error = DetourTransactionCommit();
	if (Error == NO_ERROR)
		printf("Hooked Success\n");
	else
	    printf("Hook Error\n");
	return 0;
}

DWORD id;
HANDLE hndl;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)  
{
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
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