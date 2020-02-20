#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <string>
#include <vector>
#include <tablessection1.h>
#include <map>
#include <QFile>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <time.h>
#include<tablessection2.h>
#include <bds.h>

#ifndef READER_H
#define READER_H
#define isleapyear(y) ((((y)%4==0) && ((y)%100!=0))||((y)%400==0))
using namespace std;

struct Section0
{
    long totalLength;
    int editNumber;
};

struct Section1
{
    long sectionLength;
    int editNumber;
    int parameter_table_version_number;
    string identification_of_center;
    int generating_process_ID_number;
    int grid_identification;
    bool GDS;//if true-included,else omitted
    bool BMS;//if true-included,else omitted
    int indicator_of_parameter_and_units;
    int indicator_of_type_of_level_or_layer;
    int info_of_the_level_or_layer;
    int year;
    int month;
    int day;
    int hour;
    int minut;
    long long refDate;
    long long curDate;
    int forecast_time_unit; //tablessection1.h TimeUnit
    int P1,P2;
    int time_range_indicator;//parse Table 5
    int periodSec;
    int number_missing_from_averages_or_accumulations;
    int century;
    int identification_of_sub_center;
    int factorD;// A negative value is indicated by setting the high order bit (bit No. 1) in octet 27 to 1 (on).
};

struct Section2{
     long sectionLength;
     int NV;
     int PV_LV;
     string DataType;
     int Ni;
     int Nj;
     int La1;
     int Lo1;
     int flags;
     int La2;
     int Lo2;
     int Di;
     int Dj_N;
     int scanFlags;
};

struct Section4{
    long sectionLength;
    int flag;
    bool simplePack;
    bool fPoint;
    bool mapPoint;
    bool addflag;
    int E;
    float refValue;
    int bit;
    vector<int> data;


};

class Reader
{
public:
    Reader();
    Reader (QString); //конструктор с файлом, открытие через проводник
    ~Reader();
    bool getEOF();
    Reader *readSecs();
    void readSec0(/*string*/);
    void readSec1(/*string*/);
    void readSec2(/*string*/);
    void readSec3(/*string*/);
    void readSec4();
    void readSec5();
    long secLength(char,char,char);
    int int2(char,char);
    string centerIndentification(char);
    uint period(int,int,int,int);
    long long UTC_mktime (int year,int month,int day,int hour,int min,int sec);
    void typeLanLon();

private:
    ifstream file;
    QMessageBox msgBox;
    Section0 sec0;
    Section1 sec1;
    Section2 sec2;
    Section4 sec4;
};



#endif // READER_H
