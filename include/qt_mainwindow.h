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

struct Context{
    Generator generator;
    Dictionary dictionary;
};

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Context context;
    std::vector<Word> current_generated_output;
private slots:
    void on_generateBtn_clicked();

    void on_clearOutBtn_clicked();

    void on_langSetngsBtn_clicked();

    void on_saveToDictBtn_clicked();

    void on_delDictBtn_clicked();

    void on_dictModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

    void on_saveDictBtn_clicked();

    void on_loadDictBtn_clicked();

    void on_clearSetngsBtn_clicked();

    void on_saveSetngsBtn_clicked();

    void on_loadSetngsBtn_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *output_model;
    QStandardItemModel *dict_model;

    void SetupContext();
    void SetupCustomUi();
    SETTINGS_ERROR ApplySettings();
};

#endif // QT_MAINWINDOW_H
