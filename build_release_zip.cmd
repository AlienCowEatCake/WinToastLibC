@echo off
set "SOURCE_DIR=%~dp0"
set "ARCH=x86"
if NOT "%Platform%"=="" set "ARCH=%Platform%"
if NOT "%VSCMD_ARG_TGT_ARCH%"=="" set "ARCH=%VSCMD_ARG_TGT_ARCH%"
set "BUILD_DIR=wintoastlibc_%ARCH%"
rmdir /s /q "%BUILD_DIR%" 2> nul
md "%BUILD_DIR%"
cd "%BUILD_DIR%"
cl /nologo /Ox /GS- /EHsc /MT ^
    /D_USRDLL /D_WINDLL /DUNICODE /D_UNICODE /DNDEBUG ^
    advapi32.lib ole32.lib shlwapi.lib user32.lib ^
    "/I%SOURCE_DIR%\src" ^
    "%SOURCE_DIR%\src\wintoastlib.cpp" "%SOURCE_DIR%\src\wintoastlibc.cpp" ^
    /LD /Fewintoastlibc.dll /link
del /Q *.obj
copy /Y "%SOURCE_DIR%\src\wintoastlibc.h" "wintoastlibc.h"
cd ..
tar.exe -acvf "%BUILD_DIR%.zip" "%BUILD_DIR%"
rmdir /s /q "%BUILD_DIR%"
