#ifndef WATTRSETTINGSWINDOW_H
#define WATTRSETTINGSWINDOW_H

#include <QComboBox>
#include <QDialog>
#include "qt_langsettingswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class WattrSettingsWindow;
}
QT_END_NAMESPACE

class WattrSettingsWindow: public QDialog
{
    Q_OBJECT

public:
    explicit WattrSettingsWindow(LangSettingsWindow *langwin, unsigned int row_nb, QWidget *parent = nullptr);
    ~WattrSettingsWindow();

private slots:

    void on_quitBtn_clicked();

    void on_applyBtn_clicked();

    void on_presetCbBox_currentIndexChanged(int index);

private:
    Ui::WattrSettingsWindow *ui;
    LangSettingsWindow *langwin;
    QList<QWidget*> arg_widgets;
    WordAttributeFunctionPreset pending_preset;
    unsigned int row;
    void ApplySettings();
    void SetupCustomUi();
    void LoadArgSettings();
    void LoadArgFields(WordAttributeFunctionPreset);
};

#endif // WATTRSETTINGSWINDOW_H
