#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QFileDialog>
#include <QString>

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

    //QString path=QFileDialog::getOpenFileName(0,"Open file","","*.grb");
    QString path="C:\\Users\\kicha\\Downloads\\Telegram Desktop\\Anna\\Anna\\Diplom\\grib files\\gfs20200112200203822.grb";
    Message mess(path);

    QList<uniData> listD;
    listD.append (mess.getList());

    std:: cout << "Uspehhh" << std::endl;

    return app.exec();
}
