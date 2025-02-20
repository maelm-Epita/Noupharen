#include "include/qt_wattrsettingswindow.h"
#include "ui_wattrsettingswindow.h"

#include <QLabel>
#include <QLineEdit>

void WattrSettingsWindow::LoadArgFields(WordAttributeFunctionPreset preset){
  for (WATTR_PRESET_ARGTYPE argtype : preset.func_argtypes){
        QLabel *w_label;
        QWidget *w_input;
        if (argtype == WATTR_PRESET_ARGTYPE_SYLLABLE_VEC){
            w_label = new QLabel("Prefix/Suffix", ui->argsFrame);
            QFont f = w_label->font();
            f.setUnderline(true);
            w_label->setFont(f);
            w_label->setToolTip(QString::fromStdString("FORMAT : Each letter must be separated by "
                                                       "an underscore ('_'). \nEvery syllable must be separated "
                                                       "by a space (' ').\n"
                                                       "Exemple :<letter>_<letter> <letter>_<letter>"));
            w_input = new QLineEdit(ui->argsFrame);
            if (langwin->pending_attribarg_fields[row].size() == 1){
                std::string arg_str = langwin->pending_attribarg_fields[row][0];
                qobject_cast<QLineEdit*>(w_input)->setText(QString::fromStdString(arg_str));
            }
        }
        w_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        w_input->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        ui->argsLayout->addWidget(w_label);
        ui->argsLayout->addWidget(w_input);
        w_label->show();
        w_input->show();
        arg_widgets.append(w_input);
    }
}

void WattrSettingsWindow::SetupCustomUi(){
    ui->argsLayout->setAlignment(Qt::AlignTop);
    std::string str_windowattrname = atr_name;
    ui->mainBox->setTitle(QString::fromStdString(str_windowattrname));
    for (unsigned int i=0; i<ENUM_WATTR_PRESET_LAST; i++){
        ui->presetCbBox->addItem(QString::fromStdString(WordAttributeFunctionPreset::GetWattrPresetName((WATTR_PRESET_FUNCTION)i)));
    }
};

WattrSettingsWindow::WattrSettingsWindow(LangSettingsWindow *window,
                                         unsigned int row_nb, std::string atrname, WordAttributeFunctionPreset pendingpreset,
                                         QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WattrSettingsWindow){
    ui->setupUi(this);
    langwin = window;
    row = row_nb;
    atr_name = atrname;
    SetupCustomUi();
    pending_preset = pendingpreset;
    ui->presetCbBox->setCurrentIndex(pending_preset.func_preset);
};

WattrSettingsWindow::~WattrSettingsWindow(){
    delete ui;
}


void WattrSettingsWindow::on_quitBtn_clicked()
{
    close();
}


void WattrSettingsWindow::on_applyBtn_clicked()
{
    langwin->pending_attribarg_fields[row].clear();
    QModelIndex index = langwin->wattr_model->index(row, 1);
    langwin->wattr_model->setData(index, QString::fromStdString(WordAttributeFunctionPreset::GetWattrPresetName(pending_preset.func_preset)));
    switch (pending_preset.func_preset){
    case ENUM_WATTR_PRESET_ADD_PREFIX:
    case ENUM_WATTR_PRESET_ADD_SUFFIX:
    {
        std::string sylblsstr = qobject_cast<QLineEdit*>(arg_widgets[0])->text().toStdString();
        langwin->pending_attribarg_fields[row].push_back(sylblsstr);
    }
    case ENUM_WATTR_PRESET_DONOTHING:
    default:
        break;
    }
}


void WattrSettingsWindow::on_presetCbBox_currentIndexChanged(int index)
{
    pending_preset = WordAttributeFunctionPreset::WordAttributeFunctionPresets[index];
    for (QObject *obj : ui->argsFrame->children()){
        obj->deleteLater();
    }
    arg_widgets.clear();
    LoadArgFields(pending_preset);
}

