#ifndef BDS_H
#define BDS_H
#include <vector>
#pragma once
#include <reader.h>

//Четвертая секция

class BDS:public Reader
{
public:
    BDS();
    virtual ~BDS();
    virtual void readSec();

private:
    long sectionLength;
    int flag;
    bool simplePack;
    bool fPoint;
    bool mapPoint;
    bool addflag;
    int E;
    float refValue;
    int bit;
    vector<int> data;
};

#endif // BDS_H
