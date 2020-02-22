#include "gds.h"

GDS::GDS()
{

}

GDS::~GDS()
{

}

void GDS::readSec()
{
    char message[6];
    //string message;

    for(int i=0;i<=5;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file.get();
    }
    cout<<"Section 2: "<<endl;
    sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sectionLength<<endl;

    /*for(int i=3;i<sec2.sectionLength;i++){
        message[i]=file.get();
    }*/

    NV=message[3];
    PV_LV=message[4];
    DataType=dataType(message[5]);

    if ((DataType=="Latitude/Longitude Grib")||(.DataType=="Gaussian Latitude/Longitude Grib"))
        typeLanLon();

}

string dataType(int dataType)
{
    string type;
    switch(dataType){
    case 0:
       type="Latitude/Longitude Grib";
        break;
    case 4:
        type="Gaussian Latitude/Longitude Grib";
        break;
    default:
        cout<<"I don't know this type";
    }
    return type;
}

void GDS::typeLanLon()
{
    char message[25];
    //string message;

    for(int i=0;i<=25;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file.get();
    }

    Ni=int2(message[0],message[1]);
    cout<<"Ni: "<<Ni<<endl;
    Nj=int2(message[2],message[3]);
    cout<<"Nj: "<<Nj<<endl;
    La1=secLength(message[4],message[5],message[6]);//+1
    cout<<"Lo1: "<<Lo1<<endl;
    Lo1=secLength(message[7],message[8],message[9]);//+1
    cout<<"Lo2: "<<Lo2<<endl;
    flags=message[10];//cделать таблицей
    cout<<"Flags: "<<flags<<endl;;
    La2=secLength(message[11],message[12],message[13]);//+1
    Lo2=secLength(message[14],message[15],message[16]);//+1
    cout<<"La1: "<<La1<<endl;
    cout<<"La2: "<<La2<<endl;
    Di=int2(message[17],message[18]);
    Dj_N=int2(message[19],message[20]);
    scanFlags=message[21];


}


