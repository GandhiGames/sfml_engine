@echo off

rem forfiles /P . /M *.gch /C "cmd /c echo @file"
rem add -Wall
rem rmdir /s /q ..\build

set path=c:\mingw64;c:\mingw64\bin;%path%

if not exist "..\build" mkdir ..\build

pushd ..\build

rem move config files to build dir
forfiles /P . /M *.cfg /C "cmd /c del @file"
forfiles /P ..\code /M *.cfg /C "cmd /c copy @file ..\build\@file"

rem move media files to build dir
echo Y | rmdir /s media
xcopy ..\media .\media /E /I

g++ -g -c ..\code\*.cpp -I..\SFML-2.4.2\include 
g++ -static -static-libgcc -static-libstdc++ *.o -o main.exe -I..\code -L..\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lShlwapi

rem delete intermediate files
forfiles /P . /M *.o /C "cmd /c del @file"

popd
