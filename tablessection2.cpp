#include "tablessection2.h"

tablessection2::tablessection2()
{

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
