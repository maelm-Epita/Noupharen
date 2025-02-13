#include "include/qt_langsettingswindow.h"
#include "include/qt_tbvcomboboxdelegate.h"
#include "include/qt_tbvbuttondelegate.h"
#include "ui_langsettingswindow.h"



void LangSettingsWindow::SetupCustomUi(){
    wattr_tbv = new AttributeTableView();
    ui->gridLayout_4->replaceWidget(ui->wattrTblView, wattr_tbv);
    delete ui->wattrTblView;
    ui->wattrTblView = wattr_tbv;
    ui->wattrTblView->horizontalHeader()->setStretchLastSection(true);
    wgrp_model = new QStandardItemModel(0, 2, 0);
    wattr_model = new QStandardItemModel(0, 3, 0);
    wgrp_model->setHorizontalHeaderLabels({"Name", "Attribute(s)"});
    ui->wgrpTblView->setModel(wgrp_model);
    wattr_model->setHorizontalHeaderLabels({"Name", "Function", "Edit Function Parameter(s)"});
    ui->wattrTblView->setModel(wattr_model);
    ui->wattrTblView->setItemDelegateForColumn(1, new TBVComboBoxDelegate(wattr_tbv));
}

void LangSettingsWindow::LoadContextSettings(){
    std::vector<WordGroup> wgroups = mainwin->context.generator.word_groups;
    for (WordGroup grp : wgroups){
        std::string wgrp_id = grp.group_identifier;
        std::string wgrp_attr = "";
        for (unsigned int i=0; i<grp.possible_attributes.size(); i++){
            WordAttribute wattr = grp.possible_attributes[i];
            wgrp_attr += wattr.attribute_identifier;
            if (i<grp.possible_attributes.size()-1){
                wgrp_attr += ", ";
            }
            bool alreadyAdded=0;
            for (unsigned int j=0; j<wattr_model->rowCount(); j++){
                std::string row_txt = wattr_model->data(wattr_model->index(j, 0)).toString().toStdString();
                if (row_txt == wattr.attribute_identifier) alreadyAdded=1;
            }
            if (!alreadyAdded){
                QList<QStandardItem*> row;
                row << new QStandardItem(QString::fromStdString(wattr.attribute_identifier));
                row << new QStandardItem(QString::fromStdString(WordAttribute::GetWattrPresetName(wattr.attribute_func_preset)));
                wattr_model->appendRow(row);
            }
        }
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(wgrp_id));
        row << new QStandardItem(QString::fromStdString(wgrp_attr));
        wgrp_model->appendRow(row);
    }
}

LangSettingsWindow::LangSettingsWindow(MainWindow* main, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LangSettingsWindow)
{
    mainwin = main;
    ui->setupUi(this);
    SetupCustomUi();
    LoadContextSettings();
}

LangSettingsWindow::~LangSettingsWindow()
{
    delete ui;
}

void LangSettingsWindow::on_applyBtn_clicked()
{
    //mainwin->context;

}

void LangSettingsWindow::on_quitBtn_clicked()
{
    close();
}


void LangSettingsWindow::on_addwgrpBtn_clicked()
{
    QList<QStandardItem*> row;
    row << new QStandardItem(QString::fromStdString("GroupName"));
    row << new QStandardItem(QString::fromStdString("GroupAttributes"));
    wgrp_model->appendRow(row);
}


void LangSettingsWindow::on_delwgrpBtn_clicked()
{
    QModelIndexList selection = ui->wgrpTblView->selectionModel()->selectedIndexes();
    for (QModelIndex item : selection){
        wgrp_model->removeRow(item.row());
    }
}


void LangSettingsWindow::on_addwattrBtn_clicked()
{
    QList<QStandardItem*> row;
    row << new QStandardItem(QString::fromStdString("AttributeName"));
    row << new QStandardItem(QString::fromStdString("Do nothing"));
    int row_index = wattr_model->rowCount();
    wattr_model->appendRow(row);
    wattr_tbv->showButtonInCell(row_index);
}


void LangSettingsWindow::on_delwattrBtn_clicked()
{
    //QModelIndexList selection = ui->wattrTblView->selectionModel()->selectedIndexes();
    QModelIndexList selection = wattr_tbv->selectionModel()->selectedIndexes();
    for (QModelIndex item : selection){
        wattr_model->removeRow(item.row());
    }
}

