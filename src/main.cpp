#include "sys.h"
#include<iostream>
#include<stdlib.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SYS w;
    w.show();
    return a.exec();
}
