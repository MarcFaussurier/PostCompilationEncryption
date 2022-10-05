#include <windows.h>

HFILE  ( WINAPI *MS_OpenFile)(LPCSTR     lpFileName, LPOFSTRUCT lpReOpenBuff, UINT       uStyle) = OpenFile;
//HFILE  ( WINAPI *MS_OpenFileA)(LPCSTR     lpFileName, LPOFSTRUCT lpReOpenBuff, UINT       uStyle) = OpenFileA;




HFILE  ( WINAPI SH_OpenFile)(LPCSTR     lpFileName, LPOFSTRUCT lpReOpenBuff, UINT       uStyle)
{
    HFILE k = MS_OpenFile(lpFileName,lpReOpenBuff, uStyle);
    printf("[OpenFile hook] Opening %s (%x)\n", lpFileName, k);
    return k;
}