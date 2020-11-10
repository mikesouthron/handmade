@echo off

mkdir build
pushd build
cl -Zi ..\test.c
popd
