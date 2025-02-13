#ifndef QT_ATTRIBUTETABLEVIEW_H
#define QT_ATTRIBUTETABLEVIEW_H

#include <QTableView>


class AttributeTableView : public QTableView{
    Q_OBJECT
public:
    AttributeTableView(QWidget *parent = nullptr);
    void showButtonInCell(int row);
    void handleButtonClick(int row);
protected:
    void showEvent (QShowEvent *event) override;
};

#endif // QT_ATTRIBUTETABLEVIEW_H
