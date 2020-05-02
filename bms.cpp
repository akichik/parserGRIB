#include "bms.h"

BMS::BMS(){}

BMS::~BMS(){}

void BMS::readSec(ifstream *file)
{
    GDS data;
    char message[80];

    int i;
    for(i=0;i<=2;i++){
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
    if(int2(message[4],message[5])==0){
        int cnt=data.getPointCnt ();

       // for(i=0;i<cnt;i++)
         //  bitMap[i]=(message[i+8]==1)?true:false;
    }
    else {
        specificBitmap=true;
    }


}
