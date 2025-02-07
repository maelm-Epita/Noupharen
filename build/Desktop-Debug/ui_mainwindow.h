/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *fullwindow;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab1_2;
    QGridLayout *gridLayout_3;
    QGroupBox *settings;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_5;
    QFrame *set;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_6;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QGroupBox *output;
    QGridLayout *gridLayout_7;
    QLabel *label_4;
    QPushButton *pushButton_10;
    QPushButton *pushButton_9;
    QLabel *label_5;
    QListWidget *listWidget;
    QWidget *tab_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(810, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/assets/icons/app_icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setWindowOpacity(1.000000000000000);
        MainWindow->setTabShape(QTabWidget::TabShape::Rounded);
        fullwindow = new QWidget(MainWindow);
        fullwindow->setObjectName("fullwindow");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fullwindow->sizePolicy().hasHeightForWidth());
        fullwindow->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(fullwindow);
        gridLayout_2->setObjectName("gridLayout_2");
        tabWidget = new QTabWidget(fullwindow);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setElideMode(Qt::TextElideMode::ElideNone);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab1_2 = new QWidget();
        tab1_2->setObjectName("tab1_2");
        gridLayout_3 = new QGridLayout(tab1_2);
        gridLayout_3->setObjectName("gridLayout_3");
        settings = new QGroupBox(tab1_2);
        settings->setObjectName("settings");
        gridLayout_4 = new QGridLayout(settings);
        gridLayout_4->setObjectName("gridLayout_4");
        pushButton_5 = new QPushButton(settings);
        pushButton_5->setObjectName("pushButton_5");

        gridLayout_4->addWidget(pushButton_5, 5, 0, 1, 1);

        set = new QFrame(settings);
        set->setObjectName("set");
        set->setFrameShape(QFrame::Shape::StyledPanel);
        set->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_5 = new QGridLayout(set);
        gridLayout_5->setObjectName("gridLayout_5");
        pushButton_6 = new QPushButton(set);
        pushButton_6->setObjectName("pushButton_6");

        gridLayout_5->addWidget(pushButton_6, 4, 0, 1, 1);

        label_2 = new QLabel(set);
        label_2->setObjectName("label_2");

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(set);
        label_3->setObjectName("label_3");

        gridLayout_5->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(set);
        label->setObjectName("label");

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(set);
        pushButton_7->setObjectName("pushButton_7");

        gridLayout_5->addWidget(pushButton_7, 4, 2, 1, 1);

        pushButton_8 = new QPushButton(set);
        pushButton_8->setObjectName("pushButton_8");

        gridLayout_5->addWidget(pushButton_8, 4, 1, 1, 1);

        spinBox_3 = new QSpinBox(set);
        spinBox_3->setObjectName("spinBox_3");

        gridLayout_5->addWidget(spinBox_3, 2, 1, 1, 1);

        spinBox_2 = new QSpinBox(set);
        spinBox_2->setObjectName("spinBox_2");

        gridLayout_5->addWidget(spinBox_2, 1, 1, 1, 1);

        spinBox = new QSpinBox(set);
        spinBox->setObjectName("spinBox");

        gridLayout_5->addWidget(spinBox, 0, 1, 1, 1);


        gridLayout_4->addWidget(set, 0, 0, 2, 1);

        pushButton_3 = new QPushButton(settings);
        pushButton_3->setObjectName("pushButton_3");

        gridLayout_4->addWidget(pushButton_3, 6, 0, 1, 1);

        pushButton_2 = new QPushButton(settings);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout_4->addWidget(pushButton_2, 3, 0, 1, 1);

        pushButton = new QPushButton(settings);
        pushButton->setObjectName("pushButton");

        gridLayout_4->addWidget(pushButton, 2, 0, 1, 1);

        pushButton_4 = new QPushButton(settings);
        pushButton_4->setObjectName("pushButton_4");

        gridLayout_4->addWidget(pushButton_4, 4, 0, 1, 1);


        gridLayout_3->addWidget(settings, 0, 0, 1, 1);

        output = new QGroupBox(tab1_2);
        output->setObjectName("output");
        gridLayout_7 = new QGridLayout(output);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(output);
        label_4->setObjectName("label_4");

        gridLayout_7->addWidget(label_4, 0, 0, 1, 1);

        pushButton_10 = new QPushButton(output);
        pushButton_10->setObjectName("pushButton_10");

        gridLayout_7->addWidget(pushButton_10, 2, 1, 1, 1);

        pushButton_9 = new QPushButton(output);
        pushButton_9->setObjectName("pushButton_9");

        gridLayout_7->addWidget(pushButton_9, 2, 0, 1, 1);

        label_5 = new QLabel(output);
        label_5->setObjectName("label_5");

        gridLayout_7->addWidget(label_5, 0, 1, 1, 1);

        listWidget = new QListWidget(output);
        listWidget->setObjectName("listWidget");

        gridLayout_7->addWidget(listWidget, 1, 0, 1, 2);


        gridLayout_3->addWidget(output, 0, 1, 1, 1);

        tabWidget->addTab(tab1_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(fullwindow);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_2, &QPushButton::clicked, listWidget, qOverload<>(&QListWidget::clear));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Noupharen", nullptr));
        settings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Load settings", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Letters and syllable patterns...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Minimum number of syllables", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Maximum number of syllables", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Number of words to generate", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Probabilities...", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Word groups...", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Clear settings", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Clear Output", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Save settings", nullptr));
        output->setTitle(QCoreApplication::translate("MainWindow", "Output", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Word", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Save to new dictionary", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Save to current dictionary", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Group(s)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1_2), QCoreApplication::translate("MainWindow", "Generation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Dictionary", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
