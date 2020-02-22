#ifndef ES_H
#define ES_H
#pragma once
#include <reader.h>

class ES :public Reader
{
public:
    ES();
    virtual ~ES();
    virtual void redSec();
};

#endif // ES_H
