#ifndef GDS_H
#define GDS_H
#pragma once
#include <reader.h>

//Вторая секция

class GDS:public Reader
{
public:
    GDS();
    virtual ~GDS();
    virtual void readSec();

    void typeLanLon();
    string dataType(int dataType);
private:
    long sectionLength;
    int NV;
    int PV_LV;
    string DataType;
    int Ni;
    int Nj;
    int La1;
    int Lo1;
    int flags;
    int La2;
    int Lo2;
    int Di;
    int Dj_N;
    int scanFlags;
};

#endif // GDS_H
