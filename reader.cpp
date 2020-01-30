#include "reader.h"
using namespace std;
Reader::Reader()
{
    reader.file.setFileName("C:\\Users\\Aleks\\Documents\\Anna\\gfs20200112200203822.grb");
    if (file.isOpen()){
      qDebug()<<"File is open";
      cout<<"File is open";
    }
    reader.readSec0();
}
Reader::~Reader(){
    //close
}
//
vector<string> Reader::reader()//удалить
{
    unsigned int ch=0;  //Сюда считываются символы нужно считывать символы
    string s;  //Сообщение
    vector<string> v; //Вектор cообщений
    int count;
    bool endM=false;
    ifstream myFile;//файл чтения
    myFile.open ("C:\\Users\\Aleks\\Documents\\Anna\\gfs20200112200203822.grb", std::ios::binary);

    while((ch = myFile.get()) != EOF){
        if (ch<0)
            cout<<ch<<endl;
        if(ch==55)
        {
            if(count==3)
                endM=true;

            if(myFile.peek ()==55) count++;
            else
            {
                count=0;
            }
        }
        if(!endM) s=s+char(ch);
        else {
            s=s+char(ch);
            v.push_back(s); //Если текущий символ перенос, то записываем строку в вектор
            s.clear(); //Очищаем строку
            endM=false;
            }
    }
   // v.push_back(s); //Дописываем последнюю строку в вектор.
    myFile.close(); //Закрываем файл

    cout<<"Length of GRIB: "<<v.size ()<<endl;

    return v;
    }


void Reader::readSec0(){
    cout<<"Section 0: "<<endl;
    //myFile.close ();
    Reader reader;
    bool ok;
    QByteArray message=reader.file.read(8);

   if(((char)message[0]=='G')&&((char)message[1]=='R')&&((char)message[2]=='I')&&((char)message[3]=='B'))
   {
       reader.sec0.totalLength=reader.secLength (message[4],message[5],message[6]);
       cout<<"Length of message: "<<reader.sec0.totalLength<<endl;

       /*if((message[7].toInt(&ok,10))==1){
         reader.sec0.editNumber=1;
       }
       else {
          reader.sec0.editNumber=2;
       }
       cout<<"GRIB type: "<<reader.sec0.editNumber<<endl;*/
   }
   reader.file.seek (2*8);

   //message.erase(0,8); // удаляет из строки символ с индексом i
   //readSec1(message);
   //cout<<message<<endl;

}

/*void Reader::readSec1(){
    Reader reader;
    cout<<"Section 1: "<<endl;
    reader.sec1.sectionLength=reader.secLength (message[0],message[1],message[2]);
    cout<<"Length: "<<reader.sec1.sectionLength<<endl;

    reader.sec1.parameter_table_version_number=message[3];
    if(reader.sec1.parameter_table_version_number==2) cout<<"International exchange"<<endl;
    else if(reader.sec1.parameter_table_version_number>=128&&reader.sec1.parameter_table_version_number<=254)   cout<<"Reserved for local use"<<endl;

    reader.sec1.identification_of_center=reader.centerIndentification(message[4]);
    cout<<"Indentification of center: "<<reader.sec1.identification_of_center<<endl;

    reader.sec1.generating_process_ID_number=(unsigned char)message[5];
    cout<<"Generating process ID number"<<reader.sec1.generating_process_ID_number<<endl;

    cout<<"--Grid Identification"<<endl;

    reader.sec1.GDS=(message[7]&128)!=0;
    reader.sec1.BMS=(message[7]&64)!=0;
    if(reader.sec1.GDS)
        cout<<"GDS included"<<endl;
    else
        cout<<"GDS omitted"<<endl;
    if(reader.sec1.BMS)
        cout<<"BMS included"<<endl;
    else
        cout<<"BMS omitted"<<endl;



    reader.sec1.indicator_of_parameter_and_units=message[8];
    cout<<"indicator_of_parameter_and_units: "<<reader.sec1.indicator_of_parameter_and_units<<endl;

    reader.sec1.indicator_of_type_of_level_or_layer=message[9];
    cout<<"indicator_of_type_of_level_or_layer: "<<reader.sec1.indicator_of_type_of_level_or_layer<<endl;

    reader.sec1.info_of_the_level_or_layer=reader.int2(message[10],message[11]);
    cout<<"info_of_the_level_or_layer: "<<reader.sec1.info_of_the_level_or_layer<<endl;

    reader.sec1.year=message[12];
    reader.sec1.month=message[13];
    reader.sec1.day=message[14];
    reader.sec1.hour=message[15];
    reader.sec1.minut=message[16];
    cout<<"date "<<reader.sec1.year<<"."<<reader.sec1.month<<"."<<reader.sec1.day<<endl;
    cout<<"time "<<reader.sec1.hour<<":"<<reader.sec1.minut<<endl;

    reader.sec1.forecast_time_unit=message[17];
    reader.sec1.P1=message[18];
    reader.sec1.P2=message[19];
    reader.sec1.time_range_indicator=message[20];
    //21,22?
    reader.sec1.number_missing_from_averages_or_accumulations=message[23];
    reader.sec1.century=message[24];
    reader.sec1.identification_of_sub_center=message[25];
    reader.sec1.factorD=reader.int2 (message[26],message[27]);//
    cout<<"reader.sec1.factorD"<<reader.sec1.factorD<<endl;

    message.erase(message.begin(),message.begin()+reader.sec1.sectionLength);
}
*/
long Reader::secLength (QByteRef a,QByteRef b, QByteRef c){
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
