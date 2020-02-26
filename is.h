#ifndef IS_H
#define IS_H
//#pragma once

#include <reader.h>

//Нулевая секция

class IS:public Reader{
public:
    IS();
    virtual ~IS();
    virtual void readSec(ifstream*);

private:
    long totalLength;
    int editNumber;
};

#endif // IS_H
