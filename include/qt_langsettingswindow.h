#ifndef LANGSETTINGSWINDOW_H
#define LANGSETTINGSWINDOW_H

#include <QDialog>
#include <include/qt_mainwindow.h>

namespace Ui {
class LangSettingsWindow;
}

class LangSettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LangSettingsWindow(MainWindow *mainwin, QWidget *parent = nullptr);
    ~LangSettingsWindow();

private slots:

    void on_applyBtn_clicked();

    void on_quitBtn_clicked();

    void on_addwgrpBtn_clicked();

    void on_delwgrpBtn_clicked();

    void on_addwattrBtn_clicked();

    void on_delwattrBtn_clicked();

private:
    MainWindow *mainwin;
    Ui::LangSettingsWindow *ui;
    QStandardItemModel *wgrp_model;
    QStandardItemModel *wattr_model;

    void SetupCustomUi();
    void ApplySettings();
    void LoadContextSettings();
};

#endif // LANGSETTINGSWINDOW_H
