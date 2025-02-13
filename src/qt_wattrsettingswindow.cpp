#include "include/qt_wattrsettingswindow.h"
#include "ui_wattrsettingswindow.h"

#include <QLabel>
#include <QLineEdit>

void WattrSettingsWindow::SetupCustomUi(){
    ui->attrargsLayout->setAlignment(Qt::AlignTop);
    std::string str_windowattrname = langwin->pending_wordattributes[row].attribute_identifier;
    ui->attrargsBox->setTitle(QString::fromStdString(str_windowattrname));
    QComboBox *cb = new QComboBox(ui->attrargsBox);
    presetcbBox = cb;
    presetcbBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    ui->attrargsLayout->addWidget(presetcbBox);
    for (unsigned int i=0; i<ENUM_WATTR_PRESET_LAST; i++){
        presetcbBox->addItem(QString::fromStdString(WordAttributeFunctionPreset::GetWattrPresetName((WATTR_PRESET_FUNCTION)i)));
    }
    for (WATTR_PRESET_ARGTYPE argtype : langwin->pending_wordattributes[row].attribute_func_preset.func_argtypes){
        QLabel *w_label;
        QWidget *w_input;
        if (argtype == WATTR_PRESET_ARGTYPE_SYLLABLE_VEC){
            w_label = new QLabel("Prefix/Suffix", ui->attrargsBox);
            w_input = new QLineEdit(ui->attrargsBox);
        }
        w_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        w_input->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        ui->attrargsLayout->addWidget(w_label);
        ui->attrargsLayout->addWidget(w_input);
        w_label->show();
        w_input->show();
        arg_widgets.append(w_input);
    }
};

WattrSettingsWindow::WattrSettingsWindow(LangSettingsWindow *window, unsigned int row_nb, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WattrSettingsWindow){
    ui->setupUi(this);
    langwin = window;
    row = row_nb;
    SetupCustomUi();
};

WattrSettingsWindow::~WattrSettingsWindow(){
    delete ui;
}


void WattrSettingsWindow::on_cancelBtn_clicked()
{
    close();
}


void WattrSettingsWindow::on_applyBtn_clicked()
{

}

