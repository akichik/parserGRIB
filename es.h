#ifndef ES_H
#define ES_H
#pragma once
#include <reader.h>

/*!
\file
\brief Заголовочный файл с описанием cекции 5
*/


/*!
  \brief Класс для обработки 5 секции
 */
class ES :public Reader
{
public:
    ES();
    virtual ~ES();
    virtual void readSec(ifstream *file);
};

#endif // ES_H
