#ifndef IS_H
#define IS_H
//#pragma once

#include <reader.h>

/*!
\file
\brief Заголовочный файл с описанием cекции 0
*/

/*!
  \brief Класс для обработки 0 секции
 */
class IS:public Reader{
public:
    IS();
    virtual ~IS();
    virtual void readSec(ifstream*);

    //IS* get();

private:
    long totalLength;
    int editNumber;
};

#endif // IS_H
