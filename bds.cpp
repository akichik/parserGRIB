#include "bds.h"
#include<math.h>
BDS::BDS(){}

BDS::~BDS(){}

void BDS::readSec(ifstream *file, int D, string type)
{
    char message[4];
    pointData.clear();
    for(int i=0;i<=3;i++){
        message[i]=file->get();
    }
    cout<<"Section 4: "<<endl;
    sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sectionLength<<endl;

    mapPoint=((message[3]&128)==0);
    simplePack=((message[3]&64)==0);
    fPoint=((message[3]&32)==0);
    addflag=((message[3]&16)==0);
    if (simplePack){
        cout<<"Simple Pack"<<endl;
        simple(file, D, type);
    }



}

void BDS::ref(char a, char b, char c, char d)
{
    bool sign=((a&128)==0);
    char A=a&127;
    long B=((unsigned char)b<<16)+((unsigned char)c<<8)+(unsigned char)d;

    float Aa=B/(pow(2,24));
    float Bb=pow(16,A-64);
    if(sign){
        refValue=Aa*Bb;
    }
    else{
        refValue=-1*Aa*Bb;}
}

//https://www.geeksforgeeks.org/bitwise-and-of-n-binary-strings/

void BDS::simple(ifstream *file, int D, string type)

{
    char message[7];

    vector<float> dataF;
    string data;
    float pointD;
    for(int i=0;i<7;i++){
                    message[i]=file->get();}

    E=int2(message[0],message[1]);
    ref(message[2],message[3],message[4],message[5]);
    cout<<"refValue: "<<refValue<<endl;
    bit=message[6];
    cout<<"bit in data: "<<bit<<endl;
    for(int i=11;i<sectionLength;i++){
                    data.push_back(file->get());}
    finishData(bit, data, &dataF);

    for(int i=0;i<dataF.size();i++)
    {
        pointD=(refValue+dataF[i]*pow(2,E))/pow(10,D);
        if(type=="Temp")
            pointD=pointD - 273,15;//Перевод из К в С
        else if(type=="Temp_pot")
             pointD=pointD - 273,15;//Перевод из К в С
        else if(type=="Pressure")
             pointD=pointD/133,3224;//перевод в мм.рт.ст из Па
        else if(type=="Pressure_Msl")
             pointD=pointD/133,3224;//перевод в мм.рт.ст из Па
        pointData.push_back(pointD);
        cout<<type<<": "<<pointData[i]<<endl;
    }

}

void BDS::finishData(size_t bit, string data, vector<float>* dataF )
{
    /*for (int i=0;i< data.size ();i++) {
        cout << std::bitset<8>(data[i])<<endl;
    }*/

    int help=0;
    int cnt=data.size ()*8/bit;
    vector<bool> bits;
    int16_t rez;
    for (int i=0;i< data.size ();i++) {
        char c = data[i];
          for (int j = 0; j <8; j++) {
            bits.push_back (c & 0x80);
            c <<= 1;

          }

      }

    int pos;
    for (int i=0;i<cnt;i++) {
        rez=0;
        for (int j=0;j<bit;j++)
        {
            if(bits[j+bit*i])
            {
                switch(j)
                {
                case 0:
                    rez=rez|1;
                    break;
                case 1:
                    rez=rez|2;
                    break;
                case 2:
                    rez=rez|4;
                    break;
               case 3:
                   rez=rez|8;
                    break;
                case 4:
                    rez=rez|16;
                    break;
                case 5:
                    rez=rez|32;
                    break;
                case 6:
                    rez=rez|64;
                    break;
                case 7:
                    rez=rez|128;
                    break;
                }

            }

//cout<<"data: "<<data<<endl;
        }
        dataF->push_back(rez);

    }

}
