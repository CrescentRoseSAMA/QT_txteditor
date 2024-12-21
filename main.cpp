#include <iostream>
#include "mainwin.hpp"
#include <QFile>
#include <QApplication>
#include <QProxyStyle>
#include <QStyle>
#include <QTextStream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile file(":/ui/style/style.qss");
    if (file.open(QFile::ReadOnly))
    {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        app.setStyleSheet(styleSheet);
    }
    MainWindow win;
    win.show();
    return app.exec();
}