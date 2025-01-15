@echo off

if "%OLDPATH%"=="" set OLDPATH=%PATH%

if "%QT32PATH%"=="" set QT32PATH=c:\Qt\qt-5.6.2-x86-msvc2013\5.6\msvc2013\bin
if "%QT64PATH%"=="" set QT64PATH=c:\Qt\qt-5.6.2-x64-msvc2013\5.6\msvc2013_64\bin
if "%QTCREATORPATH%"=="" set QTCREATORPATH=c:\Qt\qtcreator-4.3.1\bin
if "%VSVARSALLPATH%"=="" set VSVARSALLPATH=%VS120COMNTOOLS%\..\..\VC\vcvarsall.bat

if "%1"=="x32" (
    goto x32
) else if "%1"=="x64" (
    goto x64
) else (
    echo "Usage: setenv x32/x64"
    goto :eof
)

:x32
echo Setting Qt in PATH
set PATH=%PATH%;%QT32PATH%
set PATH=%PATH%;%QTCREATORPATH%
echo Setting VS in PATH
call "%VSVARSALLPATH%"
goto :eof

:x64
echo Setting Qt in PATH
set PATH=%PATH%;%QT64PATH%
set PATH=%PATH%;%QTCREATORPATH%
echo Setting VS in PATH
call "%VSVARSALLPATH%" amd64
goto :eof