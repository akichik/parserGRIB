#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QFileDialog>
#include<QString>

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <message.h>
#include <windows.h>

#include <map>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString path=QFileDialog::getOpenFileName(0,"Open file","","*.grb");

    Message mess(path);
    int i=1;
    map <int, Message*> msgs;

    do
    {
        msgs[i]=mess.readSecs ();
        i++;
    }
    while (!mess.checkEOF ());

    return app.exec();
}
