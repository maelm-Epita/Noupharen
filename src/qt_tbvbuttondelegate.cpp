#include "include/qt_tbvbuttondelegate.h"

#include <QPushButton>

TBVButtonDelegate::TBVButtonDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

QWidget* TBVButtonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QPushButton *btn = new QPushButton(parent);
    btn->setText("...");
    return btn;
}
void TBVButtonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    editor->setGeometry(option.rect);
}
