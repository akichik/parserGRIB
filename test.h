//#ifndef TEST_H
#define TEST_H
#include <reader.h>


class test: public Reader
{
public:
    test(){}
    ~test();
    void readSec();


private:
    long totalLength;
    int editNumber;
};

//#endif // TEST_H
