#include "message.h"

#include "QDebug"




Message::Message(){}




//Вызывать чтение секций одного сообщения из одной функции,
//проверить sec1 на наличие второй и третьей секции
Message* Message::readSecs(){

    sec0.readSec();


    sec1.readSec();


   /* readSec1();
    if(sec1.GDS=true)
        readSec2 ();/*
    if(sec1.BMS=true)
        readSec3 ();*/
   // readSec4();
   // readSec5();/*
    return this;
}















