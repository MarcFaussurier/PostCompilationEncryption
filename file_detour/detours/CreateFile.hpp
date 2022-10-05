#include <windows.h>
#include "handle_storage.hpp"

HANDLE ( WINAPI * MS_CreateFile)(
        LPCSTR                lpFileName,
        DWORD                 dwDesiredAccess,
        DWORD                 dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD                 dwCreationDisposition,
        DWORD                 dwFlagsAndAttributes,
        HANDLE                hTemplateFile
) = CreateFile;

HANDLE ( WINAPI * MS_CreateFileA)(
        LPCSTR                lpFileName,
        DWORD                 dwDesiredAccess,
        DWORD                 dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD                 dwCreationDisposition,
        DWORD                 dwFlagsAndAttributes,
        HANDLE                hTemplateFile
) = CreateFileA;



HANDLE  ( WINAPI SH_CreateFile)(
        LPCSTR                lpFileName,
        DWORD                 dwDesiredAccess,
        DWORD                 dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD                 dwCreationDisposition,
        DWORD                 dwFlagsAndAttributes,
        HANDLE                hTemplateFile
)
{
    HANDLE k = MS_CreateFile(lpFileName,dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    
    if (strstr(lpFileName, "data.sah"))
    {
        dataSahHandle = k;
        dataSahPath = (char*) lpFileName;
    }
        if (strstr(lpFileName, "update.sah"))
    {
        updateSahHandle = k;
        updateSahPath = (char*)lpFileName;
    }
    printf("[CreateFile hook] CreateFile %s [%x]\n", lpFileName, k);
    return k;
}

HANDLE  ( WINAPI SH_CreateFileA)(
        LPCSTR                lpFileName,
        DWORD                 dwDesiredAccess,
        DWORD                 dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD                 dwCreationDisposition,
        DWORD                 dwFlagsAndAttributes,
        HANDLE                hTemplateFile
)
{
    HANDLE k = MS_CreateFileA(lpFileName,dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    
    if (strstr(lpFileName, "data.sah"))
    {
        dataSahHandle = k;
        dataSahPath = (char*) lpFileName;
    }
        if (strstr(lpFileName, "update.sah"))
    {
        updateSahHandle = k;
        updateSahPath = (char*)lpFileName;
    }
    printf("[CreateFile hook] CreateFileA %s [%x]\n", lpFileName, k);
    return k;
}