param
(
                    [Parameter()]
                    [String]$path
)
Import-Module       "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"; 
Enter-VsDevShell    cc53693b
cd                  "$PSScriptRoot"
Set-Location -Path  "$PSScriptRoot"
echo                "path: $PSScriptRoot"
cl /I $PSScriptRoot\Detours\src /LD  C:\Users\admin\Desktop\vcpkg\packages\detours_x86-windows\lib\detours.lib user32.lib $PSScriptRoot\injected_dll\injected_dll.cpp
cl $PSScriptRoot\file_packer\packer.cpp
cl $PSScriptRoot\file_packer\unpacker.cpp
cl $PSScriptRoot\encrypt_const\encrypt_const.cpp


exit
