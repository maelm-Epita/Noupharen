#ifndef QT_TBVSPINBOXDELEGATE_H
#define QT_TBVSPINBOXDELEGATE_H

#include <QStyledItemDelegate>

class TBVSpinBoxDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    TBVSpinBoxDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // QT_TBVSPINBOXDELEGATE_H
