#include "bms.h"

BMS::BMS(){}

BMS::~BMS(){}

void BMS::readSec(ifstream *file)
{
    char message[80];

    for(int i=0;i<=2;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file->get();
    }
    cout<<"Section 3: "<<endl;
    sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sectionLength<<endl;

    for(int i=3;i<sectionLength;i++){
        message[i]=file->get();
    }

    unusedBit=message[3];
    if(int2(message[4],message[5])==1)
        specificBitmap=true;
    else {
        specificBitmap=false;
    }

    //TODO bit-map

}
