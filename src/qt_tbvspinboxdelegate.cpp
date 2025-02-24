#include "include/qt_tbvspinboxdelegate.h"
#include <QSpinBox>

TBVSpinBoxDelegate::TBVSpinBoxDelegate(QObject *parent) : QStyledItemDelegate(parent){}
QWidget *TBVSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *spinBox= new QSpinBox(parent);
    return spinBox;
}
void TBVSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
    unsigned int value = index.model()->data(index, Qt::EditRole).toUInt();
    spinBox->setValue(value);
}
void TBVSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
    model->setData(index, spinBox->value(), Qt::EditRole);
}
