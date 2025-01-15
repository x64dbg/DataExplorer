@echo off

echo Saving PATH
if "%OLDPATH%"=="" set OLDPATH=%PATH%

cd %~dp0

if /i "%1"=="x32"	call setenv.bat x32&goto build
if /i "%1"=="x64"	call setenv.bat x64&goto build

goto usage


:build
rmdir /S /Q build-%1
mkdir build-%1
pushd build-%1
qmake ..\QtPlugin\QtPlugin.pro CONFIG+=release
if not %ERRORLEVEL%==0 exit /b
jom
if not %ERRORLEVEL%==0 exit /b
popd
goto :restorepath

:usage
echo "Usage: build.bat x32/x64"
echo.
echo Examples:
echo   build.bat x32               : builds 32-bit release build
echo   build.bat x64               : builds 64-bit release build
goto :restorepath

:restorepath
echo Resetting PATH
set PATH=%OLDPATH%
set OLDPATH=