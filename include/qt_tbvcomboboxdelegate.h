#ifndef QT_TBVCOMBOBOXDELEGATE_H
#define QT_TBVCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class TBVComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TBVComboBoxDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // QT_TBVCOMBOBOXDELEGATE_H
