@echo off

call "c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

mkdir ..\build
pushd ..\build
cl -Zi ..\code\main.cpp sfml-graphics.lib 
popd
