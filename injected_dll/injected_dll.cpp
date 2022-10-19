#if _WIN64
# error "Only x86 supported"
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string.h>
#include <psapi.h>
#include <detours.h>

/*


*/

#pragma comment (lib, "Ws2_32.lib")

#define DEBUG 0
#define ENCRYPT 0

#if DEBUG
#include "../utils/printf.hpp"
#include "../utils/console.hpp"
#endif
#if ENCRYPT
#include "../utils/file.hpp"
#include "detours/OpenFile.hpp"
#include "detours/CreateFile.hpp"
#include "detours/ReadFile.hpp"
#include "detours/WriteFile.hpp"
#include "../crypto/updater_key.hpp"
#endif

//	::ReadProcessMemory(GetCurrentProcess(), (void*)0x00747094, &ipGame, sizeof(ipGame), 0);
int (WINAPI* MS_ReadProcessMemory)(
    HANDLE  hProcess,
    LPCVOID lpBaseAddress,
    LPVOID  lpBuffer,
    SIZE_T  nSize,
    SIZE_T* lpNumberOfBytesRead    
) = ReadProcessMemory;

BOOL(WINAPI SH_ReadProcessMemory)(
    HANDLE  hProcess,
    LPCVOID lpBaseAddress,
    LPVOID  lpBuffer,
    SIZE_T  nSize,
    SIZE_T* lpNumberOfBytesRead
    )
{
    if (lpBaseAddress == (LPCVOID) 0x00747094)
    {
#if DEBUG
        printf("Detour Game Name OK\n");
#endif  
        strcpy((char*)lpBuffer, "Shaiya Elysium");
        return 1;
    }
    return MS_ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}



int (WSAAPI* MS_connect)(SOCKET, const sockaddr*, int) = connect;


int (WSAAPI SH_connect)(
    SOCKET         s,
    const sockaddr* name,
    int            namelen
) {
    ((struct sockaddr_in*)name)->sin_addr.S_un.S_addr = inet_addr("188.165.194.214");
    int port = htons(((struct sockaddr_in*)name)->sin_port);

    char host[NI_MAXHOST]; // to store resulting string for ip
    if (getnameinfo((sockaddr*)name, sizeof(*name),
        host, NI_MAXHOST, // to try to get domain name don't put NI_NUMERICHOST flag
        NULL, 0,          // use char serv[NI_MAXSERV] if you need port number
        NI_NUMERICHOST    // | NI_NUMERICSERV
    ) != 0) {
        //handle errors
    }
    else {
      //  if (!strcmp(host, "51.77.195.229"))
      //  {
       //ima }
#if DEBUG
        printf("Connecting to to: %s:%i\n", host);
#endif   
    }
    return MS_connect(s, name, sizeof(*name));

}




DWORD WINAPI ConsoleThread(LPVOID lpParam)
{
#if DEBUG
    new_console();
#endif

    LONG Error;
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)MS_connect, SH_connect);
    DetourAttach(&(PVOID&)MS_ReadProcessMemory, SH_ReadProcessMemory);

    Error = DetourTransactionCommit();
#if DEBUG
    if (Error == NO_ERROR)
        printf("Hooked Success\n");
    else
        printf("Hook Error\n");
#endif

#if ENCRYPT
    LONG Error;
  //  DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)MS_OpenFile, SH_OpenFile);
    //DetourAttach(&(PVOID&)MS_OpenFileA, SH_OpenFile);
    DetourAttach(&(PVOID&)MS_CreateFile, SH_CreateFile);
    DetourAttach(&(PVOID&)MS_CreateFileA, SH_CreateFileA);

    DetourAttach(&(PVOID&)MS_ReadFile, SH_ReadFile);
    DetourAttach(&(PVOID&)MS_ReadFileEx, SH_ReadFile);

    //DetourAttach(&(PVOID&)MS_WriteFile, SH_WriteFile);
    Error = DetourTransactionCommit();
#if DEBUG
    if (Error == NO_ERROR)
        printf("Hooked Success\n");
    else
        printf("Hook Error\n");
#endif
#endif
    return 0;
}

//#include "mods.cpp"

/*
extern  "C"  __declspec(dllexport) void __cdecl OpenSurveyW()
{
}

extern  "C"  __declspec(dllexport) void __cdecl OpenSurveyA()
{
}

extern  "C"  __declspec(dllexport) void __cdecl ExtendedMain()
{
}

extern  "C"  __declspec(dllexport) void __cdecl ShaiyaDestek()
{
}
*/


#include "stdlib.h"
#define UPDATER_KEY "dwa@981dwd"
HANDLE hndl;
DWORD id;
__declspec(dllexport) BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    LPSTR lps;

    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
            /*
            lps = GetCommandLineA();
            if (!strstr(lps, UPDATER_KEY))
            {
             //   WinExec(".\\..\\\"Shaiya Updater.exe\"", SW_HIDE);
              //  exit(0);
            }
            */
          

           hndl = CreateThread(NULL, 0, ConsoleThread, 0, 0, &id);
           // ExtendedThread();
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