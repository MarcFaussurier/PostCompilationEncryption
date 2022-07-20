
#include <windows.h>

BOOL (WINAPI * MS_ReadFile)(
              HANDLE       hFile,
                LPVOID       lpBuffer,
                  DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
  LPOVERLAPPED lpOverlapped
) = ReadFile;


BOOL (WINAPI SH_ReadFile)(
              HANDLE       hFile,
                LPVOID       lpBuffer,
                  DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
  LPOVERLAPPED lpOverlapped
) 
{
     //printf("[OpenFile hook] reading....\n");
    char *name=  GetFileNameFromHandle(hFile);
  
   // printf("%s %i\n", name, nNumberOfBytesToRead);


    if (!strcmp(name, "C:\\shaiyaarchive\\shaiya-us\\original\\data.sah"))
    {
            free(name);

        BOOL R = MS_ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
        unsigned long    pos = GetFilePointer(hFile) - *lpNumberOfBytesRead;

        unsigned int     i = 0;

      
            unsigned char *rr = (unsigned char *) lpBuffer;
        //    printf("pos: %x " , pos);





        while (i < *lpNumberOfBytesRead)
        {
             unsigned char *byte = rr + i;
             int offset = pos + i;
        

             int r = *byte ^ 42 * offset;


            *byte  = (char) (( r + 2 - offset));


            i += 1;
        }
        return R;
    }
    free(name);
    return MS_ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}
