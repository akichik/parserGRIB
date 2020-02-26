#include "reader.h"
#include <QFileDialog>

Reader::Reader()
{
    /*QString fileName = QFileDialog::getOpenFileName(0,"Open file","","*.grb");
    file.open(fileName.toStdString(),ios::binary);
    if (file.is_open()){
      cout<<"File is open"<<endl;
    }
    else{
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText("Данный файл не найден");
    msgBox.exec();
    }*/
}


Reader::~Reader()
{
}

void Reader::readSec(ifstream *file)
{
    qDebug()<<"read section";
}

long Reader::secLength(char a, char b, char c)
{
    return ((unsigned char)a<<16)+((unsigned char)b<<8)+(unsigned char)c;
}

int Reader::int2(char a, char b)
{
    int res = ((unsigned char)a<<8)+(unsigned char)b;
    return  ((unsigned char)a<<8)+(unsigned char)b;
}


