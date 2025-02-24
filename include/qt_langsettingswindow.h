#ifndef LANGSETTINGSWINDOW_H
#define LANGSETTINGSWINDOW_H

#include "qt_attributetableview.h"
#include "include/syllable.hpp"

#include <QDialog>
#include <include/qt_mainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class LangSettingsWindow;
}
QT_END_NAMESPACE

class LangSettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LangSettingsWindow(MainWindow *mainwin, QWidget *parent = nullptr);
    ~LangSettingsWindow();
    MainWindow *mainwin;
    std::vector<std::vector<std::string>> pending_attribarg_fields;
    QStandardItemModel *wattr_model;

private slots:

    void on_applyBtn_clicked();

    void on_quitBtn_clicked();

    void on_addwgrpBtn_clicked();

    void on_delwgrpBtn_clicked();

    void on_addwattrBtn_clicked();

    void on_delwattrBtn_clicked();

private:
    Ui::LangSettingsWindow *ui;
    QStandardItemModel *wgrp_model;
    QStandardItemModel *sylptn_prob_model;
    QStandardItemModel *ltr_prob_model;
    QStandardItemModel *wgrp_prob_model;
    QStandardItemModel *wattr_prob_model;
    AttributeTableView *wattr_tbv;

    void SetupCustomUi();
    SETTINGS_ERROR ApplySettings();
    void LoadContextSettings();
};

#endif // LANGSETTINGSWINDOW_H
