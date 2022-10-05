#include <windows.h>
#include ".\..\crypto\decr.hpp"
#include "handle_storage.hpp"

BOOL (WINAPI * MS_ReadFile)(
              HANDLE       hFile,
                LPVOID       lpBuffer,
                  DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
  LPOVERLAPPED lpOverlapped
) = ReadFile;

HANDLE readPrev = 0;

BOOL (WINAPI SH_ReadFile)(
              HANDLE       hFile,
                LPVOID       lpBuffer,
                  DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
  LPOVERLAPPED lpOverlapped
) 
{  
    unsigned char   SHALL_DECR = 0;
    if (!readPrev || hFile != readPrev)
    {
        if (hFile == dataSahHandle)
            printf("Reading DATA::%s\n", dataSahPath);
        else if (hFile == updateSahHandle)
            printf("Reading UPDATE::%s\n", updateSahPath);
        else 
        {
            char *fname = GetFileNameFromHandle(hFile);
            printf("Reading ??::%s [%x]\n", fname, hFile);
            free(fname);
        }
        readPrev = hFile;
    }
    if ((dataSahHandle && (hFile == dataSahHandle))  || (updateSahHandle && (hFile == updateSahHandle)))
        SHALL_DECR = 1;
    BOOL R = MS_ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
    if (SHALL_DECR)
    {
        unsigned long    pos = GetFilePointer(hFile) - *lpNumberOfBytesRead;
        unsigned int     i = 0;
        unsigned char   *rr = (unsigned char *) lpBuffer;
        while (i < *lpNumberOfBytesRead)
        {
             unsigned char *byte = rr + i;
             int offset = pos + i;
            *byte  = decr(*byte, offset);
            i += 1;
        }
    }
    return R;
}