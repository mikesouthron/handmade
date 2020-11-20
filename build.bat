@echo off

mkdir build
pushd build
cl -Zi ..\win32_window.cpp /link user32.lib
popd
