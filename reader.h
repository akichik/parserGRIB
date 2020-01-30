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

#ifndef READER_H
#define READER_H

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
    int forecast_time_unit; //tablessection1.h TimeUnit
    int P1,P2;
    int time_range_indicator;//parse Table 5
    int number_missing_from_averages_or_accumulations;
    int century;
    int identification_of_sub_center;
    int factorD;// A negative value is indicated by setting the high order bit (bit No. 1) in octet 27 to 1 (on).
};

class Reader
{
public:
    Reader();
    ~Reader();
    //get
    void readSec0(/*string*/);
    void readSec1(/*string*/);
    long secLength(char,char,char);
    int int2(char,char);
    string centerIndentification(char);
private:
    QMessageBox msgBox;
    Section0 sec0;
    Section1 sec1;
    ifstream file;
};



#endif // READER_H
