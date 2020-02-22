#ifndef READER_H
#pragma once
#define READER_H

#include <QDebug>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <message.h>
using namespace std;


class Reader
{
public:
    Reader();
    Reader (QString); //конструктор с файлом, открытие через проводник
    virtual ~Reader();
    virtual void readSec();


    long secLength(char,char,char);
    int int2(char,char);
    bool getEOF();

    ifstream file;
private:
    QMessageBox msgBox;
    Message mess;
};

#endif // READER_H
