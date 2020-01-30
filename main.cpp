#include <QApplication>
#include <QTextCodec>
#include <QTextStream>


#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <reader.h>
#include <windows.h>





int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*QTextStream outStream(stdout);
        outStream.setCodec(QTextCodec::codecForName("cp866"));
        outStream << QString("Русский текст в консоли") << endl;*/

    Reader reader;

   // vector<string> v;

   /* v=reader.reader();
    for(int i=0;i<v.size();i++){
       reader.readSec0 (v.at (i));
       cout<<endl;
    }*/

    return app.exec();
}
