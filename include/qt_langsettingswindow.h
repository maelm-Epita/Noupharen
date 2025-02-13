#ifndef LANGSETTINGSWINDOW_H
#define LANGSETTINGSWINDOW_H

#include "qt_attributetableview.h"
#include "include/wordattribute.hpp"

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
    std::vector<WordAttribute> pending_wordattributes;

private slots:

    void on_applyBtn_clicked();

    void on_cancelBtn_clicked();

    void on_addwgrpBtn_clicked();

    void on_delwgrpBtn_clicked();

    void on_addwattrBtn_clicked();

    void on_delwattrBtn_clicked();

    void OnWattrmodelDatachanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList <int> &roles);

private:
    MainWindow *mainwin;
    Ui::LangSettingsWindow *ui;
    QStandardItemModel *wgrp_model;
    QStandardItemModel *wattr_model;
    AttributeTableView *wattr_tbv;

    void SetupCustomUi();
    void ApplySettings();
    void LoadContextSettings();
};

#endif // LANGSETTINGSWINDOW_H
