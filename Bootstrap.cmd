rmdir /Q/S .\vsbuild
mkdir vsbuild
pushd vsbuild

@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=install ../
SET BUILD_ERRORLEVEL=!ERRORLEVEL!

if "%BUILD_ERRORLEVEL%" neq "0" (
    popd
    @echo Error: cmake encountered an error.
)
