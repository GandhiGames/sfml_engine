@echo off

rem set path=c:\mingw64;c:\mingw64\bin;%path%
rem g++ -g -ggdb ..\code\*.cpp -I..\SFML-2.4.2\include 
rem g++ -g -ggdb -static -static-libgcc -static-libstdc++ *.o -o main.exe -I..\code -L..\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lShlwapi

rem Recreate build directory
if not exist ..\build mkdir ..\build

pushd ..\build

rem move libs to build dir
for %%G in (sfml-graphics-2.dll, sfml-system-2.dll, sfml-window-2.dll) do ^
forfiles /P ..\SFML-2.4.2\bin /M %%G /C "cmd /c if not exist ..\..\build\@file copy @file ..\..\build\@file"

rem move config files to build dir
forfiles /P ..\code /M *.cfg /C "cmd /c copy @file ..\build\@file"

rem move media files to build dir
echo Y | rmdir /s media
xcopy ..\media .\media /E /I

rem compile
cl -Zi -EHsc ..\code\*.cpp -I..\SFML-2.4.2\include /link /LIBPATH:..\SFML-2.4.2\lib sfml-system.lib sfml-graphics.lib sfml-window.lib Shlwapi.lib 

rem delete intermediate files
rem forfiles /P . /M *.o /C "cmd /c del @file"
rem forfiles /P . /M *.obj /C "cmd /c del @file"

popd
