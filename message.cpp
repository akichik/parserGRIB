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
    /*msgBox.setWindowTitle("Ошибка");
    msgBox.setText("Данный файл не найден");
    msgBox.exec();*/
    }
}


//Вызывать чтение секций одного сообщения из одной функции,
//проверить sec1 на наличие второй и третьей секции
Message* Message::readSecs(){

    sec0.readSec(&file);
    //if(getEOF ()) endM=true;
    sec1.readSec(&file);
    if(sec1.getGDS())
        sec2.readSec (&file);
    //if(sec1.getBMS ())
        //sec3.readSec(&file);
    sec4.readSec(&file);
    sec5.readSec(&file);



    return this;
}

bool Message::getEOF()
{
    return file.eof ();
}

/*ifstream Message::getFile()
{
    return file;
}*/













