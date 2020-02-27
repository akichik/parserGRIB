#ifndef GDS_H
#define GDS_H
#pragma once
#include <reader.h>

/*!
\file
\brief Заголовочный файл с описанием cекции 2
*/

/*!
  \brief Класс для обработки 2 секции
  \todo Таблица 7
 */
class GDS:public Reader
{
public:
    GDS();
    virtual ~GDS();
    virtual void readSec(ifstream *file);
    /*!
     * \brief typeLanLon
     * \param file читаемый файл
     * Разбирает секцию, если сетка широта/долгота или широта/долгота Гаусса
     */
    void typeLanLon(ifstream *file);
    /*!
     * \brief dataType
     * \return название сетки
     */
    string dataType(char);


private:
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

#endif // GDS_H

//NOTE //TODO таблица 7
