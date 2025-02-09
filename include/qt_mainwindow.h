#ifndef QT_MAINWINDOW_H
#define QT_MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "settingserror.hpp"
#include "include/generator.hpp"
#include "include/dictionary.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct Context{
        Generator generator;
        Dictionary dictionary;
    };
    Context context;
private slots:
    void on_generateBtn_clicked();

    void on_clearOutBtn_clicked();

    void on_langSetngsBtn_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

    void SetupContext();
    void SetupCustomUi();
    SETTINGS_ERROR ApplySettings();
};

#endif // QT_MAINWINDOW_H
