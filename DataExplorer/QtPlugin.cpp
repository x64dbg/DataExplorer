#include "QtPlugin.h"
#include "PluginDialog.h"
#include "PluginTabWidget.h"
#include "pluginmain.h"

#include <QFile>

static PluginDialog* pluginDialog;
static PluginTabWidget* pluginTabWidget;
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
};

extern "C" __declspec(dllexport) void CBMENUENTRY(CBTYPE, PLUG_CB_MENUENTRY* info)
{
    if(info->hEntry == MenuOpen)
    {
        GuiExecuteOnGuiThread([]()
        {
            pluginDialog->show();
        });
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

    pluginDialog = new PluginDialog(parent);

    //pluginTabWidget = new PluginTabWidget(parent);
    //GuiAddQWidgetTab(pluginTabWidget);

    auto iconPng = getResourceBytes(":/icons/images/icon.png");
    ICONDATA icon = {};
    icon.data = iconPng.constData();
    icon.size = iconPng.size();

    _plugin_menuseticon(Plugin::hMenu, &icon);

    _plugin_menuaddentry(Plugin::hMenu, MenuOpen, "Open");
    _plugin_menuentryseticon(Plugin::handle, MenuOpen, &icon);
    _plugin_menuentrysethotkey(Plugin::handle, MenuOpen, "Ctrl+Shift+D");

    SetEvent(hSetupEvent);
}

void QtPlugin::WaitForSetup()
{
    WaitForSingleObject(hSetupEvent, INFINITE);
}

void QtPlugin::Stop()
{
    //GuiCloseQWidgetTab(pluginTabWidget);
    //pluginTabWidget->close();

    pluginDialog->close();
    delete pluginDialog;

    //delete pluginTabWidget;

    SetEvent(hStopEvent);
}

void QtPlugin::WaitForStop()
{
    WaitForSingleObject(hStopEvent, INFINITE);
}

void QtPlugin::ShowTab()
{
    //GuiShowQWidgetTab(pluginTabWidget);
}
