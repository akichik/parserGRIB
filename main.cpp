#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QFileDialog>
#include<QString>

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <reader.h>
#include <windows.h>

#include <map>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString path=QFileDialog::getOpenFileName(0,"Open file","","*.grb");
    Reader reader(path);
    int i=1;
    map <int, Reader*> msgs;
    while(!reader.getEOF ()){
       msgs[i]=reader.readSecs ();
    }

    return app.exec();
}
