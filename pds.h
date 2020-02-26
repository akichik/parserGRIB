#ifndef PDS_H
#define PDS_H
#pragma once
#include<reader.h>
#include <string>
#include<tablessection1.h>

#define isleapyear(y) ((((y)%4==0) && ((y)%100!=0))||((y)%400==0))

//Первая секция

class PDS: public Reader
{
public:
    PDS();
    virtual ~PDS();
    virtual void readSec(ifstream*);

    string centerIndentification(char);
    uint period(int,int,int,int);
    long long UTC_mktime (int year,int month,int day,int hour,int min,int sec);
    bool getGDS();
    bool getBMS();
    char  getDataType(){ return indicator_of_parameter_and_units; }
    int getfactorD(){return factorD;}
private:
    long sectionLength;
    int editNumber;
    int parameter_table_version_number;
    string identification_of_center;
    int generating_process_ID_number;
    int grid_identification;
    bool GDS;//if true-included,else omitted
    bool BMS;//if true-included,else omitted
    char indicator_of_parameter_and_units;
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

#endif // PDS_H
