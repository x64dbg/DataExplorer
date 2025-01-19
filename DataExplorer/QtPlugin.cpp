#include "QtPlugin.h"
#include "DataExplorerDialog.h"
#include "pluginmain.h"

#include <QFile>
#include <QUrl>
#include <QDesktopServices>

static DataExplorerDialog* dataExplorerDialog;
static HANDLE hSetupEvent;
static HANDLE hStopEvent;

static QByteArray getResourceBytes(const char* path)
{
    QByteArray b;
    QFile s(path);
    if(s.open(QFile::ReadOnly))
        b = s.readAll();
    return b;
}

static QWidget* getParent()
{
    return QWidget::find((WId)Plugin::hwndDlg);
}

enum
{
    MenuOpen,
    MenuDocumentation,
};

extern "C" __declspec(dllexport) void CBMENUENTRY(CBTYPE, PLUG_CB_MENUENTRY* info)
{
    switch(info->hEntry)
    {
    case MenuOpen:
        dataExplorerDialog->show();
        dataExplorerDialog->activateWindow();
        break;
    case MenuDocumentation:
        QDesktopServices::openUrl(QUrl("https://docs.werwolv.net/pattern-language"));
        break;
    default:
        break;
    }
}

void QtPlugin::Init()
{
    hSetupEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
    hStopEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
}

void QtPlugin::Setup()
{
    QWidget* parent = getParent();

    dataExplorerDialog = new DataExplorerDialog(parent);

    auto pngOpen = getResourceBytes(":/images/icon.png");
    ICONDATA iconOpen = {};
    iconOpen.data = pngOpen.constData();
    iconOpen.size = pngOpen.size();

    _plugin_menuseticon(Plugin::hMenu, &iconOpen);

    _plugin_menuaddentry(Plugin::hMenu, MenuOpen, "Open");
    _plugin_menuentryseticon(Plugin::handle, MenuOpen, &iconOpen);
    _plugin_menuentrysethotkey(Plugin::handle, MenuOpen, "Ctrl+Shift+D");

    auto pngDocumentation = getResourceBytes(":/images/documentation.png");
    ICONDATA iconDocumentation = {};
    iconDocumentation.data = pngDocumentation.constData();
    iconDocumentation.size = pngDocumentation.size();

    _plugin_menuaddentry(Plugin::hMenu, MenuDocumentation, "Documentation");
    _plugin_menuentryseticon(Plugin::handle, MenuDocumentation, &iconDocumentation);

    SetEvent(hSetupEvent);
}

void QtPlugin::WaitForSetup()
{
    WaitForSingleObject(hSetupEvent, INFINITE);
}

void QtPlugin::Stop()
{
    dataExplorerDialog->close();
    delete dataExplorerDialog;
    dataExplorerDialog = nullptr;

    SetEvent(hStopEvent);
}

void QtPlugin::WaitForStop()
{
    WaitForSingleObject(hStopEvent, INFINITE);
}
