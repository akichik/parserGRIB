#include "pds.h"
#include "pds.h"

PDS::PDS(){}

PDS::~PDS(){}

void PDS::readSec(ifstream *file)
{
    char message[30];
    //string message;

    for(int i=0;i<=2;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file->get();
    }
    cout<<"Section 1: "<<endl;
    sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sectionLength<<endl;

    for(int i=3;i<sectionLength;i++){
        message[i]=file->get();
    }
    parameter_table_version_number=message[3];
    if(parameter_table_version_number==2) cout<<"International exchange"<<endl;
    else if(parameter_table_version_number>=128&&parameter_table_version_number<=254)   cout<<"Reserved for local use"<<endl;

    identification_of_center=centerIndentification(message[4]);
    cout<<"Indentification of center: "<<identification_of_center<<endl;

    generating_process_ID_number=(unsigned char)message[5];
    cout<<"Generating process ID number"<<generating_process_ID_number<<endl;


    grid_identification=message[7];
    cout<<"Grid Identification"<<grid_identification<<endl;

    GDS=(message[7]&128)!=0;
    BMS=(message[7]&64)!=0;

    indicator_of_parameter_and_units=message[8];
    cout<<"indicator_of_parameter_and_units: "<<indicator_of_parameter_and_units<<endl;

    indicator_of_type_of_level_or_layer=message[9];
    cout<<"indicator_of_type_of_level_or_layer: "<<indicator_of_type_of_level_or_layer<<endl;

    info_of_the_level_or_layer=int2(message[10],message[11]);
    cout<<"info_of_the_level_or_layer: "<<info_of_the_level_or_layer<<endl;

    year=message[12]+message[24]*100-100;
    month=message[13];
    day=message[14];
    hour=message[15];
    minut=(int)message[16];
    refDate=UTC_mktime(year,month,day,hour,minut,0);
    cout<<"date "<<year<<"."<<month<<"."<<day<<endl;
    cout<<"time "<<hour<<":"<<minut<<endl;

    forecast_time_unit=message[17];
    P1=message[18];
    P2=message[19];
    time_range_indicator=message[20];
    periodSec=period (forecast_time_unit,P1,P2,time_range_indicator);
    curDate=UTC_mktime(year,month,day,hour,minut,periodSec);
    //21,22?
    cout<<"UTC: "<<curDate<<endl;
    number_missing_from_averages_or_accumulations=message[23];
    century=message[24];
    identification_of_sub_center=message[25];



    D=factorD(message[26],message[27]);//
    cout<<"factorD "<<D<<endl;
}

long long PDS::UTC_mktime (
    int year,int month,int day,int hour,int min,int sec)
{
    if (year<1970 || month<1 || month>12 || day<1
            || hour<0 || min<0 || sec<0)
        return -1;
    long long r = 0;

    for (int y=1970; y<year; y++) {
        r += 365*24*3600;
        if (isleapyear(y))
            r += 24*3600;
    }
    if (month > 1) {
        for (int m=1; m<month; m++) {
            if (m==2) {
                r += 28*24*3600;
                if (isleapyear(year))
                    r += 24*3600;
            }
            else if (m==1||m==3||m==5||m==7||m==8||m==10||m==12) {
                r += 31*24*3600;
            }
            else {
                r += 30*24*3600;
            }
        }
    }
    r += (day-1)*24*3600;
    r += hour*3600;
    r += min*60;
    r += sec;
    return r;
}

bool PDS::getGDS()
{
    if (GDS)
        return true;
}

bool PDS::getBMS()
{
    if (BMS)
        return true;
}

int PDS::factorD(char a,char b)
{
         bool sign=((a&128)!=0);
         a=a&127;
         if (sign)
             D=-int2(a,b);
         else D=int2(a,b);

         return D;
}

int PDS::getfactorD()
{
    return D;
}

string PDS::centerIndentification(char a)
{
    string s;
    switch(a){
    case static_cast<int>(OrigCenters::USWS_NationalMetCenter):
        s="USWS_NationalMetCenter";
         break;
    case static_cast<int>(OrigCenters::USWS_NWSTelecommsGateway):
         s="USWS_NWSTelecommsGateway";
         break;
    case static_cast<int>(OrigCenters::USWS_FieldStations):
         s="USWS_FieldStations";
         break;
    case static_cast<int>(OrigCenters::JapaneseMA_Tokyo):
        s="JapaneseMA_Tokyo";
        break;
    case static_cast<int>(OrigCenters::NHC_Miami):
        s="NHC_Miami";
        break;
    case static_cast<int>(OrigCenters::CanadianMS_Montreal):
        s="CanadianMS_Montreal";
        break;
    case static_cast<int>(OrigCenters::USAF_GWC):
        s="USAF_GWC";
        break;
    case static_cast<int>(OrigCenters::USNavy_FNOC):
        s="USNavy_FNOC";
        break;
    case static_cast<int>(OrigCenters::NOAAFSL_BoulderCO):
        s="NOAAFSL_BoulderCO";
        break;
    case static_cast<int>(OrigCenters::UKMO_Bracknell):
        s="UKMO_Bracknell";
        break;
    case static_cast<int>(OrigCenters::FWS_Toulouse):
        s="FWS_Toulouse";
        break;
    case static_cast<int>(OrigCenters::ESA):
       s="ESA";
       break;
    case static_cast<int>(OrigCenters::ECforMediumRangeForecaste):
        s="ECforMediumRangeForecaste";
        break;
    case static_cast<int>(OrigCenters::DeBilt):
        s="DeBilt";
        break;
    default:
        s="Unknown";
    }
    return s;
}

uint PDS::period(int unit,int P1,int P2, int range)
{
    int res, dur;
    switch (unit) {
        case 0: //	Minute
            res = 60; break;
        case 1: //	Hour
            res = 3600; break;
        case 2: //	Day
            res = 86400; break;
        case 10: //	3 hours
            res = 10800; break;
        case 11: //	6 hours
            res = 21600; break;
        case 12: //	12 hours
            res = 43200; break;
        case 254: // Second
            res = 1; break;
        case 3: //	Month
        case 4: //	Year
        case 5: //	Decade (10 years)
        case 6: //	Normal (30 years)
        case 7: //	Century (100 years)
        default:

            res = 0;

    }

    dur = 0;
    switch (range) {
        case 0:
            dur = (int)P1; break;
        case 1:
            dur = 0; break;
        case 2:
        case 3:

            dur = (int)P2; break;
         case 4:
            dur = (int)P2; break;
        case 10:
            dur = ((int)P1<<8) + (int)P2; break;
        default:
            dur = 0;
           // ok = false;
    }
    return res*dur;
}
