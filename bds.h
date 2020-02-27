#ifndef BDS_H
#define BDS_H
#include <vector>
#pragma once
#include <reader.h>

/*!
\file
\brief Заголовочный файл с описанием cекции 4
*/


/*!
  \brief Класс для обработки 4 секции
  \todo чтение данных и распаковка простой упаковки
  \todo распаковка остальных упаковок
 */
class BDS:public Reader
{
public:
    BDS();
    virtual ~BDS();
    virtual void readSec(ifstream *file);
    /*!
     * \brief Вычисляет референсное значение
     * \param октеты 7-10
     */
    void ref(char,char,char,char);
private:
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

#endif // BDS_H
