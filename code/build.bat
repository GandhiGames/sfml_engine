@echo off

rem add -Wall
rem rmdir /s /q ..\build

set path=c:\mingw64;c:\mingw64\bin;%path%

forfiles /P . /M *.gch /C "cmd /c del @file"

if not exist "..\build" mkdir ..\build

pushd ..\build

rem move config files to build dir
forfiles /P . /M *.cfg /C "cmd /c del @file"
forfiles /P ..\code /M *.cfg /C "cmd /c copy @file ..\build\@file"

rem move media files to build dir
echo Y | rmdir /s media
xcopy ..\media .\media /E /I

rem Do compile
rem g++ -g -ggdb ..\code\*.cpp -I..\SFML-2.4.2\include 
rem g++ -g -ggdb -static -static-libgcc -static-libstdc++ *.o -o main.exe -I..\code -L..\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lShlwapi
cl -Zi ..\code\*.cpp -I..\SFML-2.4.2\include /link /LIBPATH:..\SFML-2.4.2\lib libsfml-system.a

rem delete intermediate files
forfiles /P . /M *.o /C "cmd /c del @file"

popd
