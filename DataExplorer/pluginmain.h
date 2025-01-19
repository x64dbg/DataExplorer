#pragma once

#include <windows.h>
#include "pluginsdk\_plugins.h"

namespace Plugin
{
    extern int handle;
    extern HWND hwndDlg;
    extern int hMenu;
    extern int hMenuDisasm;
    extern int hMenuDump;
    extern int hMenuStack;
    extern int hMenuGraph;
    extern int hMenuMemmap;
    extern int hMenuSymmod;
    extern wchar_t szDllDir[MAX_PATH];
} //Plugin
