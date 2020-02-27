#include "message.h"

#include "QDebug"



Message::~Message()
{
    file.close ();
}

Message::Message(){

    //reader();
}

Message::Message(QString fileName)
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

Message* Message::readSecs(){

    sec0.readSec(&file);
    //if(getEOF ()) endM=true;
    sec1.readSec(&file);
    if(sec1.getGDS())
        sec2.readSec (&file);
    if(sec1.getBMS ())
        sec3.readSec(&file);
    sec4.readSec(&file);
    sec5.readSec(&file);



    return this;
}

bool Message::checkEOF()
{
    char c=file.get();

    if (file.eof ())
        return true;
    else{
        file.unget();
        return false;
    }
}

/*ifstream Message::getFile()
{
    return file;
}*/













