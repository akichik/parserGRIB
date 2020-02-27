#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <QFile>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <time.h>
#pragma once
#include<is.h>
#include<pds.h>
#include<bds.h>
#include<es.h>
#include<gds.h>
#include<bms.h>


#ifndef MESSAGE_H
#define MESSAGE_H

/*!
  \brief Класс хранящи сообщение полностью
 */
class Message
{
public:
    Message();
    Message(QString);
    ~Message();
    Message *readSecs();

    bool checkEOF();


    bool endM;

private:
    ifstream file;
    IS  sec0;
    PDS sec1;
    GDS sec2;
    BMS sec3;
    BDS sec4;
    ES  sec5;

    QMessageBox msgBox;

};



#endif MESSAGE_H
