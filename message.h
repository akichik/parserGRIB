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

typedef struct uniData{
    PDS sec1;
    GDS sec2;
    BMS sec3;
    BDS sec4;
}UniData;

/*!
  \brief Класс хранящий сообщение полностью
 */
class Message
{
public:
    Message(QString);
    ~Message();
    bool checkEOF();
    QList<UniData> getList();
private:
    ifstream file;
    QList<UniData> listData;
};



#endif MESSAGE_H
