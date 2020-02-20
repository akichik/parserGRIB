#include "reader.h"

#include "QDebug"


using namespace std;
Reader::Reader(QString fileName)
{

   file.open(fileName.toStdString(),ios::binary);
    if (file.is_open()){
      cout<<"File is open"<<endl;
    }
    else{
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText("Данный файл не найден");
    msgBox.exec();
    }
}

Reader::Reader(){}

Reader::~Reader(){
    file.close ();
}


//Вызывать чтение секций одного сообщения из одной функции,
//проверить sec1 на наличие второй и третьей секции
Reader* Reader::readSecs(){
    readSec0();
    readSec1();
    if(sec1.GDS=true)
        readSec2 ();/*
    if(sec1.BMS=true)
        readSec3 ();*/
    readSec4();
    readSec5();
    return this;
}
void Reader::readSec0(){
    cout<<"Section 0: "<<endl;
    string message;
    for(int i=0;i<=7;i++){
        message[i]=file.get();
    }

   if(((char)message[0]=='G')&&((char)message[1]=='R')&&((char)message[2]=='I')&&((char)message[3]=='B'))
   {
       sec0.totalLength=secLength (message[4],message[5],message[6]);
       cout<<"Length of message: "<<sec0.totalLength<<endl;

       if(message[7]==1){
         sec0.editNumber=1;
       }
       else {
          sec0.editNumber=2;
       }
       cout<<"GRIB type: "<<sec0.editNumber<<endl;
   }
 // readSec1();

}

void Reader::readSec1(){
    char message[30];
    //string message;

    for(int i=0;i<=2;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file.get();
    }
    cout<<"Section 1: "<<endl;
    sec1.sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sec1.sectionLength<<endl;

    for(int i=3;i<sec1.sectionLength;i++){
        message[i]=file.get();
    }
    sec1.parameter_table_version_number=message[3];
    if(sec1.parameter_table_version_number==2) cout<<"International exchange"<<endl;
    else if(sec1.parameter_table_version_number>=128&&sec1.parameter_table_version_number<=254)   cout<<"Reserved for local use"<<endl;

    sec1.identification_of_center=centerIndentification(message[4]);
    cout<<"Indentification of center: "<<sec1.identification_of_center<<endl;

    sec1.generating_process_ID_number=(unsigned char)message[5];
    cout<<"Generating process ID number"<<sec1.generating_process_ID_number<<endl;

    cout<<"--Grid Identification"<<endl;

    sec1.GDS=(message[7]&128)!=0;
    sec1.BMS=(message[7]&64)!=0;
    if(sec1.GDS)
        cout<<"GDS included=>Sec 2 with us"<<endl;
    else
        cout<<"GDS omitted"<<endl;
    if(sec1.BMS)
        cout<<"BMS included=>Sec 3 with us"<<endl;
    else
        cout<<"BMS omitted"<<endl;



    sec1.indicator_of_parameter_and_units=message[8];
    cout<<"indicator_of_parameter_and_units: "<<sec1.indicator_of_parameter_and_units<<endl;

    sec1.indicator_of_type_of_level_or_layer=message[9];
    cout<<"indicator_of_type_of_level_or_layer: "<<sec1.indicator_of_type_of_level_or_layer<<endl;

    sec1.info_of_the_level_or_layer=int2(message[10],message[11]);
    cout<<"info_of_the_level_or_layer: "<<sec1.info_of_the_level_or_layer<<endl;
//Why minut=-80?
    sec1.year=message[12]+message[24]*100-100;
    sec1.month=message[13];
    sec1.day=message[14];
    sec1.hour=message[15];
    sec1.minut=(int)message[16];
    sec1.refDate=UTC_mktime(sec1.year,sec1.month,sec1.day,sec1.hour,sec1.minut,0);
    cout<<"date "<<sec1.year<<"."<<sec1.month<<"."<<sec1.day<<endl;
    cout<<"time "<<sec1.hour<<":"<<sec1.minut<<endl;

    sec1.forecast_time_unit=message[17];
    sec1.P1=message[18];
    sec1.P2=message[19];
    sec1.time_range_indicator=message[20];
    sec1.periodSec=period (sec1.forecast_time_unit,sec1.P1,sec1.P2,sec1.time_range_indicator);
    sec1.curDate=UTC_mktime(sec1.year,sec1.month,sec1.day,sec1.hour,sec1.minut,sec1.periodSec);
    //21,22?
    cout<<"UTC: "<<sec1.curDate<<endl;
    sec1.number_missing_from_averages_or_accumulations=message[23];
    sec1.century=message[24];
    sec1.identification_of_sub_center=message[25];
    sec1.factorD=int2(message[26],message[27]);//
    cout<<"reader.sec1.factorD "<<sec1.factorD<<endl;

}

void Reader::readSec2()
{
    char message[6];
    //string message;

    for(int i=0;i<=5;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file.get();
    }
    cout<<"Section 2: "<<endl;
    sec1.sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sec1.sectionLength<<endl;

    /*for(int i=3;i<sec2.sectionLength;i++){
        message[i]=file.get();
    }*/

    sec2.NV=message[3];
    sec2.PV_LV=message[4];
    sec2.DataType=dataType(message[5]);

    if ((sec2.DataType=="Latitude/Longitude Grib")||(sec2.DataType=="Gaussian Latitude/Longitude Grib"))
        typeLanLon();

}

void Reader::readSec4()
{
    char message[80];
    //string message;

    for(int i=0;i<=2;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file.get();
    }
    cout<<"Section 4: "<<endl;
    sec4.sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sec4.sectionLength<<endl;

    for(int i=3;i<sec4.sectionLength;i++){
        message[i]=file.get();
    }

    //sec4.flag=message[3];
    sec4.mapPoint=((message[3]&128)==0);
    sec4.simplePack=((message[3]&64)==0);
    sec4.fPoint=((message[3]&32)==0);
    sec4.addflag=((message[3]&16)==0);
    if (sec4.simplePack)
        cout<<"Simple Pack"<<endl;

    sec4.E=int2(message[4],message[5]);
    //функция для ref
    sec4.bit=message[10];
   /* for (int i=0;i<sec4.sectionLength-11;i=+sec4.bit){
        sec4.data.push_back(int2(message[i],message[i+1]));
    }
    cout<<"data: ";
    for(int i=0;i<sec4.data.size();i++)
        cout<<sec4.data[i]<<" ";

    cout<<endl;
*/

}

void Reader::readSec5()
{
    char message[4];
    for(int i=0;i<=3;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file.get();
    }
    if(message[0]=='7' && message[1]=='7' && message[2]=='7' && message[3]=='7')
        cout<<"End message"<<endl<<endl;

}

long Reader::secLength (char a,char b, char c){
    return ((unsigned char)a<<16)+((unsigned char)b<<8)+(unsigned char)c;
}

int Reader::int2(char a,char b){
    int res = ((unsigned char)a<<8)+(unsigned char)b;
    return  ((unsigned char)a<<8)+(unsigned char)b;
}

string Reader::centerIndentification(char a)
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

uint Reader::period(int unit,int P1,int P2, int range)
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
            //erreur("id=%d: unknown time unit in PDS b18=%d",id,unit);
            res = 0;
           // ok = false;
    }
   // debug("id=%d: PDS (time range) b21=%d P1=%d P2=%d",id,range,P1,P2);
    dur = 0;
    switch (range) {
        case 0:
            dur = (int)P1; break;
        case 1:
            dur = 0; break;
        case 2:
        case 3:
            // dur = ((zuint)P1+(zuint)P2)/2; break;     // TODO
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
bool Reader::getEOF()
{
   return file.eof ();
}

long long Reader::UTC_mktime (
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

void Reader::typeLanLon()
{
    char message[25];
    //string message;

    for(int i=0;i<=25;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file.get();
    }

    sec2.Ni=int2(message[0],message[1]);
    cout<<"Ni: "<<sec2.Ni<<endl;
    sec2.Nj=int2(message[2],message[3]);
    cout<<"Nj: "<<sec2.Nj<<endl;
    sec2.La1=secLength(message[4],message[5],message[6]);//+1
    cout<<"Lo1: "<<sec2.Lo1<<endl;
    sec2.Lo1=secLength(message[7],message[8],message[9]);//+1
    cout<<"Lo2: "<<sec2.Lo2<<endl;
    sec2.flags=message[10];//cделать таблицей
    cout<<"Flags: "<<sec2.flags<<endl;;
    sec2.La2=secLength(message[11],message[12],message[13]);//+1
    sec2.Lo2=secLength(message[14],message[15],message[16]);//+1
    cout<<"La1: "<<sec2.La1<<endl;
    cout<<"La2: "<<sec2.La2<<endl;
    sec2.Di=int2(message[17],message[18]);
    sec2.Dj_N=int2(message[19],message[20]);
    sec2.scanFlags=message[21];


}
