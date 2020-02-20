#include <QApplication>
#include <QTextCodec>
#include <QTextStream>


#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <reader.h>
#include <windows.h>
#include <test.h>
#include <map>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    Reader reader("C:\\Users\\Aleks\\Documents\\Anna\\gfs20200112200203822.grb");
    int i=1;
    map <int, Reader*> msgs;
    while(!reader.getEOF ()){
       msgs[i]=reader.readSecs ();
    }

    return app.exec();
}
