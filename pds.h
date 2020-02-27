#ifndef PDS_H
#define PDS_H
#pragma once
#include<reader.h>
#include <string>
#include<tablessection1.h>

#define isleapyear(y) ((((y)%4==0) && ((y)%100!=0))||((y)%400==0))

/*!
\file
\brief Заголовочный файл с описанием cекции 1
*/

/*!
  \brief Класс для обработки 1 секции
  \todo функция для определения параметра и единиц измерения из tablessection1.h
  \todo проверить индекатор промежутка времени
  \todo добавить идентификаторы суб-центра
 */

class PDS: public Reader
{
public:
    PDS();
    virtual ~PDS();
    virtual void readSec(ifstream*);
    /*!
     * \brief centerIndentification
     * \param[in] char 5 октет
     * \return идентификатор центра
     */
    string centerIndentification(char a);
    uint period(int,int,int,int);

    /*!
     * \brief UTC_mktime
     * \param year год
     * \param month месяц
     * \param day день
     * \param hour часы
     * \param min минуты
     * \param sec секунды
     * \return значение в формате UTC
     */
    long long UTC_mktime (int year,int month,int day,int hour,int min,int sec);
    bool getGDS();
    bool getBMS();
    char  getDataType(){ return indicator_of_parameter_and_units; }
    /*!
     * \brief factorD
     * Вычисляет D по двум октетам
     * \param a 27 октет
     * \param b 28 октет
     * \return
     */
    int factorD(char a,char b);
    int getfactorD();


private:
    long sectionLength;  ///Длина секции
    int parameter_table_version_number;///Номер версии основных таблиц GRIB
    string identification_of_center;///Идентификатор центрального производителя
    int generating_process_ID_number;///Цифровой  ID  процесса генерации
    int grid_identification;///Идентификация сетки (географическое положение и площадь)
    bool GDS; ///Флаг наличия GDS(true-included,else omitted)
    bool BMS;///Флаг наличия BMS(true-included,else omitted)
    char indicator_of_parameter_and_units;///Индикатор параметра и единиц измерения
    int indicator_of_type_of_level_or_layer;///Индикатор типа уровня или слоя
    int info_of_the_level_or_layer;///Высота, давление и т. д. уровня или слоя
    int year;
    int month;
    int day;
    int hour;
    int minut;
    long long refDate;
    long long curDate;
    int forecast_time_unit; ///Единица времени прогноза tablessection1.h TimeUnit
    int P1,P2;
    int time_range_indicator;//parse Table 5
    int periodSec;
    int number_missing_from_averages_or_accumulations;
    int century;
    int identification_of_sub_center;
    int D;///Десятичный масштабный коэффициент D
};

#endif // PDS_H

//TODO функция для определения параметра и единиц измерения из tablessection1.h
//TODO проверить индекатор промежутка времени
//TODO добавить идентификаторы суб-центра
