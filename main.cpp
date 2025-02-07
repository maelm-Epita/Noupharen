#include <QApplication>
#include <QPushButton>
#include "src/qt_mainwindow.cpp"

int main(int argc, char **argv){
    QApplication app (argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}
