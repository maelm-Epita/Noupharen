#include "include/qt_tbvcomboboxdelegate.h"
#include "include/wordattribute.hpp"
#include <QComboBox>

TBVComboBoxDelegate::TBVComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent){}
QWidget *TBVComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);
    for (unsigned int i=0; i<ENUM_WATTR_PRESET_LAST; i++){
        comboBox->addItem(QString::fromStdString(WordAttribute::GetWattrPresetName((ENUM_WATTR_PRESET)i)));
    }
    return comboBox;
}
void TBVComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    QString value = index.model()->data(index, Qt::EditRole).toString();
    int idx = comboBox->findText(value);
    if (idx != -1){
        comboBox->setCurrentIndex(idx);
    }
}
void TBVComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}
