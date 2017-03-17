@echo off

rem add -Wall
rem rmdir /s /q ..\build

set path=c:\mingw64;c:\mingw64\bin;%path%

rem forfiles /P . /M *.gch /C "cmd /c del @file"

if not exist "..\build" mkdir ..\build

pushd ..\build

rem move config files to build dir
rem forfiles /P . /M *.cfg /C "cmd /c del @file"
forfiles /P ..\code /M *.cfg /C "cmd /c copy @file ..\build\@file"

rem move media files to build dir
echo Y | rmdir /s media
xcopy ..\media .\media /E /I

rem Do compile
rem g++ -g -ggdb ..\code\*.cpp -I..\SFML-2.4.2\include 
rem g++ -g -ggdb -static -static-libgcc -static-libstdc++ *.o -o main.exe -I..\code -L..\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lShlwapi
cl -Zi -EHsc ..\code\*.cpp -I..\SFML-2.4.2\include /link /LIBPATH:..\SFML-2.4.2\lib sfml-system.lib sfml-graphics.lib sfml-window.lib Shlwapi.lib 

rem delete intermediate files
rem forfiles /P . /M *.o /C "cmd /c del @file"
rem forfiles /P . /M *.obj /C "cmd /c del @file"

popd
