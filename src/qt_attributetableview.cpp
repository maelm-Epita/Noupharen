
#include "include/qt_attributetableview.h"

#include <QPushButton>

AttributeTableView::AttributeTableView(QWidget *parent) : QTableView(parent){};

void AttributeTableView::handleButtonClick(int row){
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
