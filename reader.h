#ifndef READER_H
#pragma once
#define READER_H

#include <QDebug>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
//#include <message.h>
using namespace std;


class Reader
{
public:
    Reader();

    virtual ~Reader();
    virtual void readSec(ifstream*);


    long secLength(char,char,char);
    int int2(char,char);


private:
    QMessageBox msgBox;
    //Message mess;
};

#endif // READER_H
