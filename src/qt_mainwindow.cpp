#include "include/qt_mainwindow.h"
#include "include/qt_langsettingswindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


void MainWindow::SetupContext(){
  Letter letter1, letter2, letter3, letter4, letter5, letter6;
  letter1.character = "g";
  letter2.character = "a";
  letter3.character = "r";
  letter4.character = "p";
  letter5.character = "i";
  letter6.character = "t";
  LetterGroup lgroup1, lgroup2;
  lgroup1.group_identifier = "C";
  lgroup2.group_identifier = "V";
  lgroup1.letters.push_back(letter1);
  lgroup1.letters.push_back(letter3);
  lgroup1.letters.push_back(letter4);
  lgroup1.letters.push_back(letter6);
  lgroup2.letters.push_back(letter2);
  lgroup2.letters.push_back(letter5);
  context.generator.letter_groups.push_back(lgroup1);
  context.generator.letter_groups.push_back(lgroup2);
  SyllablePattern pat1, pat2, pat3;
  /*pat1.push_back(&context.generator.letter_groups[0]);
  pat1.push_back(&context.generator.letter_groups[1]);
  pat1.push_back(&context.generator.letter_groups[1]);
  pat1.push_back(&context.generator.letter_groups[0]);
  pat2.push_back(&context.generator.letter_groups[0]);
  pat2.push_back(&context.generator.letter_groups[1]);
  pat2.push_back(&context.generator.letter_groups[0]);
  pat3.push_back(&context.generator.letter_groups[0]);
  pat3.push_back(&context.generator.letter_groups[1]);
  context.generator.syllable_patterns.push_back(pat1);
  context.generator.syllable_patterns.push_back(pat2);
  context.generator.syllable_patterns.push_back(pat3);
  Syllable wattr3syl, wattr4syl;
  std::vector<Syllable> wattr3suf, wattr4pref;
  wattr3syl.letters.push_back(&context.generator.letter_groups[0].letters[1]);
  wattr3syl.letters.push_back(&context.generator.letter_groups[1].letters[1]);
  wattr3syl.pattern.push_back(&context.generator.letter_groups[0]);
  wattr3syl.pattern.push_back(&context.generator.letter_groups[1]);
  wattr3suf = {wattr3syl};
  wattr4syl.letters.push_back(&context.generator.letter_groups[0].letters[0]);
  wattr4syl.letters.push_back(&context.generator.letter_groups[1].letters[0]);
  wattr4syl.pattern.push_back(&context.generator.letter_groups[0]);
  wattr4syl.pattern.push_back(&context.generator.letter_groups[1]);
  wattr4pref = {wattr4syl, wattr4syl};
  WordAttribute wattr1, wattr2, wattr3, wattr4;
  wattr1.attribute_identifier = "masculine";
  wattr2.attribute_identifier = "feminine";
  wattr3.attribute_identifier = "godan";
  wattr4.attribute_identifier = "ichidan";
  wattr1.attribute_function = WordAttributeFunctionPreset::WATTR_PRESET_DONOTHING;
  wattr1.attribute_func_preset = WordAttributeFunctionPreset::WordAttributeFunctionPresets[ENUM_WATTR_PRESET_DONOTHING];
  wattr2.attribute_function = WordAttributeFunctionPreset::WATTR_PRESET_DONOTHING;
  wattr2.attribute_func_preset = WordAttributeFunctionPreset::WordAttributeFunctionPresets[ENUM_WATTR_PRESET_DONOTHING];
  wattr3.attribute_function = [wattr3suf](Word *word) {WordAttributeFunctionPreset::WATTR_PRESET_ADD_SUFFIX(wattr3suf, word);};
  wattr3.attribute_func_arguments.push_back(wattr3suf);
  wattr3.attribute_func_preset = WordAttributeFunctionPreset::WordAttributeFunctionPresets[ENUM_WATTR_PRESET_ADD_SUFFIX];
  wattr4.attribute_function = [wattr4pref](Word *word) {WordAttributeFunctionPreset::WATTR_PRESET_ADD_PREFIX(wattr4pref, word);};
  wattr4.attribute_func_arguments.push_back(wattr4pref);
  wattr4.attribute_func_preset = WordAttributeFunctionPreset::WordAttributeFunctionPresets[ENUM_WATTR_PRESET_ADD_PREFIX];
  WordGroup wgroup1, wgroup2;
  wgroup1.group_identifier = "Noun";
  wgroup2.group_identifier = "Verb";
  wgroup1.possible_attributes.push_back(wattr1);
  wgroup1.possible_attributes.push_back(wattr2);
  wgroup2.possible_attributes.push_back(wattr3);
  wgroup2.possible_attributes.push_back(wattr4);
  context.generator.word_groups.push_back(wgroup1);
  context.generator.word_groups.push_back(wgroup2);
  context.generator.min_syllable_count = 2;
  context.generator.max_syllable_count = 6;
  context.generator.nb_words = 10;
*/
}

SETTINGS_ERROR MainWindow::ApplySettings(){
    unsigned int minNbSyl = ui->minNbSSpin->value();
    unsigned int maxNbSyl = ui->maxNbSSpin->value();
    unsigned int nbWords = ui->nbWSpin->value();
    if (minNbSyl > maxNbSyl){
        return SETTINGS_ERROR_SYLLABLECOUNT_MAX_MIN;
    }
    if (context.generator.letter_groups.size() == 0){
        return SETTINGS_ERROR_NO_LETTERGROUP;
    }
    if (context.generator.syllable_patterns.size() == 0){
        return SETTINGS_ERROR_NO_SYLLABLEPATTERN;
    }
    if (context.generator.word_groups.size() == 0){
        return SETTINGS_ERROR_NO_WORDGROUP;
    }
    context.generator.min_syllable_count = minNbSyl;
    context.generator.max_syllable_count = maxNbSyl;
    context.generator.nb_words = nbWords;
    return SETTINGS_ERROR_NOERR;
}

void MainWindow::SetupCustomUi(){
    output_model = new QStandardItemModel(0, 2, 0);
    output_model->setHorizontalHeaderLabels({"Word", "Group(s)"});
    ui->outpuTblView->setModel(output_model);
    dict_model = new QStandardItemModel(0,3,0);
    dict_model->setHorizontalHeaderLabels({"Word", "Group(s)", "Meaning"});
    ui->dictTblView->setModel(dict_model);
    connect(dict_model, &QAbstractItemModel::dataChanged, this, &MainWindow::on_dictModelDataChanged);
    ui->errLabel->setVisible(false);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    SetupCustomUi();
    //SetupContext();
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_generateBtn_clicked()
{
    ui->errLabel->setVisible(false);
    SETTINGS_ERROR err = ApplySettings();
    if (err != SETTINGS_ERROR_NOERR){
        ui->errLabel->setVisible(true);
        ui->errLabel->setText(QString::fromStdString("Invalid settings : " + GetSettingsErrorMessage(err)));
        return;
    }
    std::vector<Word> generated_words = context.generator.GenerateWords();
    for (Word word : generated_words){
        current_generated_output.push_back(word);
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(word.GetString()));
        row << new QStandardItem(QString::fromStdString(word.GetGroupString()));
        output_model->appendRow(row);
    }
}


void MainWindow::on_clearOutBtn_clicked()
{
    current_generated_output.clear();
    output_model->clear();
    output_model->setHorizontalHeaderLabels({"Word", "Group(s)"});
}


void MainWindow::on_langSetngsBtn_clicked()
{
    LangSettingsWindow *win = new LangSettingsWindow(this, this);
    win->exec();
}


void MainWindow::on_saveToDictBtn_clicked()
{
    QModelIndexList selection = ui->outpuTblView->selectionModel()->selectedIndexes();
    std::vector<Word> w;
    for (QModelIndex item : selection){
        w.push_back(current_generated_output[item.row()]);
    }
    context.dictionary.AddWords(w);
    for (unsigned int i=0; i<w.size(); i++){
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(w[i].GetString()));
        row << new QStandardItem(QString::fromStdString(w[i].GetGroupString()));
        row << new QStandardItem(QString::fromStdString(""));
        dict_model->appendRow(row);
    }
}

void MainWindow::on_delDictBtn_clicked()
{
    QModelIndexList selection = ui->dictTblView->selectionModel()->selectedIndexes();
    for (QModelIndex item : selection){
        dict_model->removeRow(item.row());
        if (context.dictionary.words.size() > item.row()){
            context.dictionary.words.erase(context.dictionary.words.begin() + item.row());
        }
    }
}

void MainWindow::on_dictModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight){
    if (topLeft.row() != bottomRight.row() || topLeft.column() != bottomRight.column()){
        return;
    }
    std::string str = dict_model->data(dict_model->index(topLeft.row(), topLeft.column())).toString().toStdString();
    if (topLeft.column() == 0){
        context.dictionary.words[topLeft.row()].word= str;
    }
    if (topLeft.column() == 1){
        context.dictionary.words[topLeft.row()].group = str;
    }
    if (topLeft.column() == 2){
        context.dictionary.words[topLeft.row()].meaning = str;
    }
}

void MainWindow::on_saveDictBtn_clicked()
{
    std::string filename = QFileDialog::getSaveFileName().toStdString();
    if (filename == ""){
        return;
    }
    std::string extension = ".ndict";
    std::string test = filename.substr(filename.size()-extension.size(), extension.size());
    if (test != extension){
        filename += extension;
    }
    context.dictionary.SaveToFile(filename);
}


void MainWindow::on_loadDictBtn_clicked()
{
    std::string filename = QFileDialog::getOpenFileName().toStdString();
    if (filename == ""){
        return;
    }
    if (!context.dictionary.LoadFromFile(filename)){
        return;
    }
    dict_model->clear();
    for (DictWord w : context.dictionary.words){
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(w.word));
        row << new QStandardItem(QString::fromStdString(w.group));
        row << new QStandardItem(QString::fromStdString(w.meaning));
        dict_model->appendRow(row);
    }
}

void MainWindow::on_saveSetngsBtn_clicked()
{
    ApplySettings();
    std::string filename = QFileDialog::getSaveFileName().toStdString();
    if (filename == ""){
        return;
    }
    std::string extension = ".nsetting";
    std::string test = filename.substr(filename.size()-extension.size(), extension.size());
    if (test != extension){
        filename += extension;
    }
    context.generator.SaveToFile(filename);
}

void MainWindow::on_loadSetngsBtn_clicked()
{
    ui->errLabel->hide();
    std::string filename = QFileDialog::getOpenFileName().toStdString();
    if (filename == ""){
        return;
    }
    Generator backup = context.generator;
    if (!context.generator.LoadFromFile(filename)){
        ui->errLabel->setText("Failed to load settings file. Please make sure this is a valid settings file. Please do not modify settings files as this could corrupt them.");
        ui->errLabel->show();
        context.generator = backup;
    }
    else{
        ui->maxNbSSpin->setValue(context.generator.max_syllable_count);
        ui->minNbSSpin->setValue(context.generator.min_syllable_count);
        ui->nbWSpin->setValue(context.generator.nb_words);
    }
}

void MainWindow::on_clearSetngsBtn_clicked()
{
    context.generator.ClearSettings();
    ui->maxNbSSpin->setValue(0);
    ui->minNbSSpin->setValue(0);
    ui->nbWSpin->setValue(0);
}





