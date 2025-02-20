
#include "include/qt_attributetableview.h"
#include "include/qt_wattrsettingswindow.h"

#include <QPushButton>

AttributeTableView::AttributeTableView(QWidget *parent) : QTableView(parent){};

void AttributeTableView::handleButtonClick(int row){
    std::string n = model()->data(model()->index(row, 0)).toString().toStdString();
    std::string pstr = model()->data(model()->index(row, 1)).toString().toStdString();
    WordAttributeFunctionPreset p = WordAttributeFunctionPreset::WordAttributeFunctionPresets[WordAttributeFunctionPreset::GetWattrPresetEnum(pstr)];
    WattrSettingsWindow *win = new WattrSettingsWindow(langwin, row, n, p, langwin);
    win->exec();
}

void AttributeTableView::showButtonInCell(int row) {
    QPushButton *button = new QPushButton("...", this);
    connect(button, &QPushButton::clicked, this, [this, row]() {
        AttributeTableView::handleButtonClick(row);
    });
    setIndexWidget(model()->index(row, 2), button);
}

void AttributeTableView::showEvent(QShowEvent *event){
    QTableView::showEvent(event);
    for (unsigned int row=0; row<model()->rowCount(); ++row){
        QModelIndex index = model()->index(row, 2);
        if (!indexWidget(index)){
            showButtonInCell(row);
        }
    }

}
