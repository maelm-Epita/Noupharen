#include "include/qt_langsettingswindow.h"
#include "include/qt_tbvcomboboxdelegate.h"
#include "ui_langsettingswindow.h"


void LangSettingsWindow::SetupCustomUi(){
    wattr_tbv = new AttributeTableView(ui->window);
    wattr_tbv->langwin = this;
    ui->gridLayout_4->replaceWidget(ui->wattrTblView, wattr_tbv);
    ui->wattrTblView->hide();
    ui->wattrTblView->deleteLater();
    ui->wattrTblView = wattr_tbv;
    ui->wattrTblView->horizontalHeader()->setStretchLastSection(true);
    wgrp_model = new QStandardItemModel(0, 2, 0);
    wattr_model = new QStandardItemModel(0, 3, 0);
    wgrp_model->setHorizontalHeaderLabels({"Name", "Attribute(s)"});
    ui->wgrpTblView->setModel(wgrp_model);
    wattr_model->setHorizontalHeaderLabels({"Name", "Function", "Edit Function Parameter(s)"});
    ui->wattrTblView->setModel(wattr_model);
    ui->wattrTblView->setItemDelegateForColumn(1, new TBVComboBoxDelegate(wattr_tbv));
    connect(wattr_model, &QStandardItemModel::dataChanged, this, &LangSettingsWindow::OnWattrmodelDatachanged);
}

void LangSettingsWindow::LoadContextSettings(){
    // first tab
    std::string lgrpstr = LetterGroup::LGStringFromLetterGroups(mainwin->context.generator.letter_groups);
    ui->ltrgrpTxtEdit->setPlainText(QString::fromStdString(lgrpstr));
    std::string spstr = LetterGroup::SPStringFromSyllablePatterns(mainwin->context.generator.syllable_patterns);
    ui->sylptnTxtEdit->setPlainText(QString::fromStdString(spstr));
    // second tab
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
                row << new QStandardItem(QString::fromStdString(WordAttributeFunctionPreset::GetWattrPresetName(wattr.attribute_func_preset.func_preset)));
                wattr_model->appendRow(row);
                pending_wordattributes.push_back(wattr);
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
    std::string LGString = ui->ltrgrpTxtEdit->toPlainText().toStdString();
    std::string SPString = ui->sylptnTxtEdit->toPlainText().toStdString();
    mainwin->context.generator.letter_groups = LetterGroup::LetterGroupsFromLGString(LGString);
    std::vector<LetterGroup> *grps = &mainwin->context.generator.letter_groups;
    mainwin->context.generator.syllable_patterns = LetterGroup::SyllablePatternsFromSPString(SPString, grps);
    //mainwin->context.generator.word_groups = pend
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
    WordAttribute new_attr;
    new_attr.attribute_identifier = "AttributeName";
    new_attr.attribute_func_preset = WordAttributeFunctionPreset::WordAttributeFunctionPresets[ENUM_WATTR_PRESET_DONOTHING];
    pending_wordattributes.push_back(new_attr);
}


void LangSettingsWindow::on_delwattrBtn_clicked()
{
    QModelIndexList selection = wattr_tbv->selectionModel()->selectedIndexes();
    for (QModelIndex item : selection){
        wattr_model->removeRow(item.row());
        if (item.row() < pending_wordattributes.size()){
            pending_wordattributes.erase(pending_wordattributes.begin() + item.row());
        }
    }
}

void LangSettingsWindow::OnWattrmodelDatachanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles){
    for (unsigned int i=topLeft.row(); i<=bottomRight.row(); i++){
        pending_wordattributes[i].attribute_identifier = wattr_model->index(i, 0).data().toString().toStdString();
        WATTR_PRESET_FUNCTION func_preset = WordAttributeFunctionPreset::GetWattrPresetEnum(wattr_model->index(i, 1).data().toString().toStdString());
        pending_wordattributes[i].attribute_func_preset = WordAttributeFunctionPreset::WordAttributeFunctionPresets[func_preset];
    }
}
