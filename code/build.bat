@echo off
mkdir ..\build

pushd ..\build
set path=C:\mingw64\bin;%path%
g++ -g -c ..\code\*.cpp -c -I..\SFML-2.4.2\include
g++ *.o -o main.exe -I..\code -I..\SFML-2.4.2\include -L..\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system
popd
