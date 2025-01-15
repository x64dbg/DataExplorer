#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QDialog>
#include <windows.h>

#include "PatternLanguage.h"

namespace Ui
{
class PluginDialog;
}

class PluginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginDialog(QWidget* parent);
    ~PluginDialog();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_buttonShowTab_clicked();
    void on_buttonParse_pressed();
    void on_logEdit_anchorClicked(const QUrl &url);

private:
    void logHandler(LogLevel level, const char *message);
    void compileError(const CompileError& error);
    void evalError(const EvalError& error);

    Ui::PluginDialog *ui;
    struct PatternVisitor* mVisitor = nullptr;
    class PatternHighlighter* mHighlighter = nullptr;
};

#endif // PLUGINDIALOG_H
