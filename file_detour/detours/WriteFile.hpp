#include <windows.h>
#include ".\..\crypto\encr.hpp"
#include "handle_storage.hpp"

BOOL (WINAPI *MS_WriteFile)(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
) = WriteFile;

HANDLE writePrev = 0;

BOOL (WINAPI SH_WriteFile)(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
) {
    unsigned char   SHALL_ENCR = 0;
    if (!writePrev || hFile != writePrev)
    {
        #if DEBUG
        if (hFile == dataSahHandle)
        {
            printf("Writing DATA::%s\n", dataSahPath);
        }
        else if (hFile == updateSahHandle)
        {
            printf("Writing UPDATE::%s\n", updateSahPath); 

        }
        else 
        {
            char *fname = GetFileNameFromHandle(hFile);
            printf("Writing ??::%s [%x]\n", fname, hFile);
            free(fname);
        }
        #endif
        writePrev = hFile;
    }
    if ((dataSahHandle && (hFile == dataSahHandle))  || (updateSahHandle && (hFile == updateSahHandle)))
        SHALL_ENCR = 1;
    BOOL R = MS_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
    if (SHALL_ENCR)
    {
        unsigned long    pos = GetFilePointer(hFile) - *lpNumberOfBytesWritten;
        unsigned int     i = 0;
        unsigned char   *rr = (unsigned char *) lpBuffer;
        while (i < *lpNumberOfBytesWritten)
        {
             unsigned char *byte = rr + i;
             int offset = pos + i;
            *byte  = encr(*byte, offset);
            i += 1;
        }
    }
    return R;
}