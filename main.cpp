#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include "src/qt_mainwindow.cpp"

void debugSyl(){
    Letter letter1, letter2, letter3, letter4, letter5, letter6;
    letter1.character = "g";
    letter2.character = "a";
    letter3.character = "r";
    letter4.character = "p";
    letter5.character = "i";
    letter6.character = "tc";
    LetterGroup lgroup1, lgroup2;
    lgroup1.group_identifier = "C";
    lgroup2.group_identifier = "V";
    lgroup1.letters.push_back(letter1);
    lgroup1.letters.push_back(letter3);
    lgroup1.letters.push_back(letter4);
    lgroup1.letters.push_back(letter6);
    lgroup2.letters.push_back(letter2);
    lgroup2.letters.push_back(letter5);
    std::vector<LetterGroup> lgrps = {lgroup1, lgroup2};
    std::string str = "r_a r_i r_g tc_a_i";
    std::vector<Syllable> sylbls = Syllable::SyllablesFromArgString(str, &lgrps);
    for (Syllable syl : sylbls){
        qInfo() << syl.GetDebugString();
    }
}

int main(int argc, char **argv){
    QApplication app (argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}
