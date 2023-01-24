#include <windows.h>
#include ".\..\crypto\decr.hpp"
#include "handle_storage.hpp"
#include <algorithm>

using namespace std;


BOOL(WINAPI* MS_ReadFileEx)(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPOVERLAPPED lpOverlapped,
    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine

    ) = ReadFileEx;

BOOL(WINAPI SH_ReadFileEx)(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPOVERLAPPED lpOverlapped,
    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    )
{
    printf("ReadFileEx!!\n");
    BOOL R = MS_ReadFileEx(hFile, lpBuffer, nNumberOfBytesToRead, lpOverlapped, lpCompletionRoutine);
   
    return R;
}


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
   /*
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
    */
    if (dataSahHandle == hFile && hFile)
    {
        if (readPrev != hFile)
            printf("dataSahHandle\n");
        SHALL_DECR = 1;
    }

    readPrev = hFile;
    
     //   fname = fname + strlen(fname) - 8;
       //
   /*
   if (!strcmp(fname, "data.sah"))
        SHALL_DECR = 1;*/
    //SHALL_DECR = 0;
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