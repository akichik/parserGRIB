#include "reader.h"
#include "reader.h"

Reader::Reader()
{

}


Reader::Reader(QString fileName)
{

   file.open(fileName.toStdString(),ios::binary);
    if (file.is_open()){
      cout<<"File is open"<<endl;
    }
    else{
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText("Данный файл не найден");
    msgBox.exec();
    }
}

Reader::~Reader()
{
    file.close ();
}

void Reader::readSec()
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

bool Reader::getEOF()
{
   return file.eof ();
}
