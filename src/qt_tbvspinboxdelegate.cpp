#include "include/qt_tbvspinboxdelegate.h"
#include <QSpinBox>

TBVSpinBoxDelegate::TBVSpinBoxDelegate(QObject *parent) : QStyledItemDelegate(parent){}
QWidget *TBVSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox= new QDoubleSpinBox(parent);
    return spinBox;
}
void TBVSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(editor);
    unsigned int value = index.model()->data(index, Qt::EditRole).toDouble();
    spinBox->setValue(value);
}
void TBVSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(editor);
    model->setData(index, spinBox->value(), Qt::EditRole);
}
