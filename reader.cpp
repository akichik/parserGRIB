#include "reader.h"
using namespace std;
Reader::Reader()
{
   file.open("C:\\Users\\Aleks\\Documents\\Anna\\gfs20200112200203822.grb",ios::binary);
    if (file.is_open()){
      cout<<"File is open"<<endl;
      readSec0();
    }
    else{
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText("Данный файл не найден");
    msgBox.exec();
    }
}
Reader::~Reader(){
    file.close ();
}

void Reader::readSec0(){
    //cout<<file.tellg()<<endl;
    cout<<"Section 0: "<<endl;
    //myFile.close ();
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
   //is.seekg (0, is.end);
   //file.seekg ()
  readSec1();

}

void Reader::readSec1(){
    string message;

    for(int i=0;i<=2;i++){
        //cout<<file.tellg()<<endl;
        message[i]=file.get();
    }
    cout<<"Section 1: "<<endl;
    sec1.sectionLength=secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<sec1.sectionLength<<endl;
    for(int i=3;i<=sec1.sectionLength;i++){
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
        cout<<"GDS included"<<endl;
    else
        cout<<"GDS omitted"<<endl;
    if(sec1.BMS)
        cout<<"BMS included"<<endl;
    else
        cout<<"BMS omitted"<<endl;



    sec1.indicator_of_parameter_and_units=message[8];
    cout<<"indicator_of_parameter_and_units: "<<sec1.indicator_of_parameter_and_units<<endl;

    sec1.indicator_of_type_of_level_or_layer=message[9];
    cout<<"indicator_of_type_of_level_or_layer: "<<sec1.indicator_of_type_of_level_or_layer<<endl;

    sec1.info_of_the_level_or_layer=int2(message[10],message[11]);
    cout<<"info_of_the_level_or_layer: "<<sec1.info_of_the_level_or_layer<<endl;

    sec1.year=message[12];
    sec1.month=message[13];
    sec1.day=message[14];
    sec1.hour=message[15];
    sec1.minut=message[16];
    cout<<"date "<<sec1.year<<"."<<sec1.month<<"."<<sec1.day<<endl;
    cout<<"time "<<sec1.hour<<":"<<sec1.minut<<endl;

    sec1.forecast_time_unit=message[17];
    sec1.P1=message[18];
    sec1.P2=message[19];
    sec1.time_range_indicator=message[20];
    //21,22?
    sec1.number_missing_from_averages_or_accumulations=message[23];
    sec1.century=message[24];
    sec1.identification_of_sub_center=message[25];
    sec1.factorD=int2 (message[26],message[27]);//
    cout<<"reader.sec1.factorD"<<sec1.factorD<<endl;

    //message.erase(message.begin(),message.begin()+reader.sec1.sectionLength);
}

long Reader::secLength (char a,char b, char c){
    return ((unsigned char)a<<16)+((unsigned char)b<<8)+(unsigned char)c;
}

int Reader::int2(char a,char b){
    return (unsigned char)a<<8+(unsigned char)b;
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
