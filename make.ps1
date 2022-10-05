param
(
                    [Parameter()]
                    [String]$path
)
Import-Module       "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"; 
Enter-VsDevShell    c32ca37b
cd                  "$PSScriptRoot"
Set-Location -Path  "$PSScriptRoot"
echo                "path: $PSScriptRoot"
cl /I $PSScriptRoot\Detours\src /LD C:\Users\admin\Desktop\vcpkg\installed\x86-windows\lib\detours.lib $PSScriptRoot\file_detour\os.cpp
cl $PSScriptRoot\file_packer\packer.cpp
cl $PSScriptRoot\file_packer\unpacker.cpp
exit
