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

#include<fstream>



#ifndef MESSAGE_H
#define MESSAGE_H


class Message
{
public:
    Message();
    Message(QString);
    ~Message();
    Message *readSecs();

    bool getEOF();

    ifstream getFile();
    bool endM;
    ifstream file;
private:
    //ifstream file;
    IS  sec0;
    PDS sec1;
    GDS sec2;
    BDS sec4;
    ES  sec5;

};



#endif MESSAGE_H
