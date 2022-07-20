#include <windows.h>

HFILE  ( WINAPI *MS_OpenFile)(LPCSTR     lpFileName, LPOFSTRUCT lpReOpenBuff, UINT       uStyle) = OpenFile;



HFILE  ( WINAPI SH_OpenFile)(LPCSTR     lpFileName, LPOFSTRUCT lpReOpenBuff, UINT       uStyle)
{
    printf("[OpenFile hook] Opening %s\n", lpFileName);
    return MS_OpenFile(lpFileName,lpReOpenBuff, uStyle);
}