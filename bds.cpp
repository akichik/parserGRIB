#include "bds.h"

BDS::BDS(){}

BDS::~BDS(){}

void BDS::readSec(ifstream *file)
{
    char message[80];
    //string message;

    for(int i=0;i<=2;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file->get();
    }
    cout<<"Section 4: "<<endl;
    sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sectionLength<<endl;

    for(int i=3;i<sectionLength;i++){
        message[i]=file->get();
    }

    //sec4.flag=message[3];
    mapPoint=((message[3]&128)==0);
    simplePack=((message[3]&64)==0);
    fPoint=((message[3]&32)==0);
    addflag=((message[3]&16)==0);
    if (simplePack)
        cout<<"Simple Pack"<<endl;

    E=int2(message[4],message[5]);
    //функция для ref
    bit=message[10];
   /* for (int i=0;i<sec4.sectionLength-11;i=+sec4.bit){
        sec4.data.push_back(int2(message[i],message[i+1]));
    }
    cout<<"data: ";
    for(int i=0;i<sec4.data.size();i++)
        cout<<sec4.data[i]<<" ";

    cout<<endl;
*/

}
