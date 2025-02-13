#ifndef QT_ATTRIBUTETABLEVIEW_H
#define QT_ATTRIBUTETABLEVIEW_H


#include <QTableView>

class LangSettingsWindow;

class AttributeTableView : public QTableView{
    Q_OBJECT
public:
    AttributeTableView(QWidget *parent = nullptr);
    void showButtonInCell(int row);
    void handleButtonClick(int row);
    LangSettingsWindow *langwin;
protected:
    void showEvent (QShowEvent *event) override;
};

#endif // QT_ATTRIBUTETABLEVIEW_H
