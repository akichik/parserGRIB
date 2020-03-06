#include "message.h"

#include "QDebug"



Message::~Message(){}


Message::Message(QString fileName)
{

    IS  sec0;
    PDS sec1;
    GDS sec2;
    BMS sec3;
    BDS sec4;
    ES  sec5;
    QMessageBox msgBox;

   file.open(fileName.toStdString(),ios::binary);
    if (file.is_open()){
      cout<<"File is open"<<endl;

      UniData data;
      do
      {

        //sec0.readSec(&file);
        sec0.readSec (&file);
        data.sec1.readSec (&file);
        if(data.sec1.getGDS())
            data.sec2.readSec (&file);
        if(data.sec1.getBMS ())
            data.sec3.readSec (&file);
        data.sec4.readSec (&file);

        sec5.readSec (&file);

        //data.sec0.readSec (&file);

        /*sec1.readSec(&file);
        data.sec1 = &sec1;

        if(data.sec1->getGDS()){
            sec2.readSec (&file);
            data.sec2=&sec2;
        }

        if(data.sec1->getBMS ()){
            sec3.readSec(&file);
            data.sec3=&sec3;
        }

        sec4.readSec(&file);
        data.sec4=&sec4;

        sec5.readSec(&file);*/

        listData.append (data);
      }while(!checkEOF());

      file.close ();
    }
    else
    {
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Данный файл не найден");
        msgBox.exec();
    }
}

/*Message* Message::readSecs(){

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
*/
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

QList<UniData> Message::getList()
{
    return listData;
}















