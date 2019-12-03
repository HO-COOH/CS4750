#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "maze.h"
int func(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    //Maze a(10,10);
    //a.Generate();
    //a.Show();
    return func(argc, argv);
}

