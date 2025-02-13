#ifndef QT_TBVBUTTONDELEGATE_H
#define QT_TBVBUTTONDELEGATE_H

#include <QStyledItemDelegate>


class TBVButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TBVButtonDelegate(QObject* parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // QT_TBVBUTTONDELEGATE_H
