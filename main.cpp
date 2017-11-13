#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // QString filename="C:\\Output\\Collection.txt";
    Collection array;
    //CoffeeMachine machine;
    //machine.load("C:\\Output\\machine.txt");
    //array.setMachine(machine);
    //array.load(filename);
    w.setList(array);
    w.initializeLog();
    w.showMaximized();
    w.show();
    return a.exec();
}
