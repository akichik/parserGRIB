#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <string>
#include <vector>
#include <tablessection1.h>
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


#ifndef MESSAGE_H
#define MESSAGE_H


class Message
{
public:
    Message();
    Message *readSecs();

private:
    IS sec0;
    PDS sec1;
};



#endif  MESSAGE_H
