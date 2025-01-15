#include "pluginmain.h"
#include "QtPlugin.h"

#define plugin_name "DataExplorer"
#define plugin_version 1

int Plugin::handle;
HWND Plugin::hwndDlg;
int Plugin::hMenu;
int Plugin::hMenuDisasm;
int Plugin::hMenuDump;
int Plugin::hMenuStack;
int Plugin::hMenuGraph;
int Plugin::hMenuMemmap;
int Plugin::hMenuSymmod;
wchar_t Plugin::szDllDir[MAX_PATH];

extern "C" __declspec(dllexport) bool pluginit(PLUG_INITSTRUCT* initStruct)
{
    initStruct->pluginVersion = plugin_version;
    initStruct->sdkVersion = PLUG_SDKVERSION;
    strcpy_s(initStruct->pluginName, plugin_name);

    Plugin::handle = initStruct->pluginHandle;
    QtPlugin::Init();
    return true;
}

extern "C" __declspec(dllexport) void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
    Plugin::hwndDlg = setupStruct->hwndDlg;
    Plugin::hMenu = setupStruct->hMenu;
    Plugin::hMenuDisasm = setupStruct->hMenuDisasm;
    Plugin::hMenuDump = setupStruct->hMenuDump;
    Plugin::hMenuStack = setupStruct->hMenuStack;
    Plugin::hMenuGraph = setupStruct->hMenuGraph;
    Plugin::hMenuMemmap = setupStruct->hMenuMemmap;
    Plugin::hMenuSymmod = setupStruct->hMenuSymmod;
    GuiExecuteOnGuiThread(QtPlugin::Setup);
    QtPlugin::WaitForSetup();
}

extern "C" __declspec(dllexport) bool plugstop()
{
    GuiExecuteOnGuiThread(QtPlugin::Stop);
    QtPlugin::WaitForStop();
    return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID)
{
    if(fdwReason == DLL_PROCESS_ATTACH)
    {
        GetModuleFileNameW(hinstDLL, Plugin::szDllDir, _countof(Plugin::szDllDir));
        auto slash = wcsrchr(Plugin::szDllDir, L'\\');
        if(slash != nullptr)
            *slash = L'\0';
    }
    return TRUE;
}
