#ifndef BMS_H
#define BMS_H
#include <reader.h>

/*!
\file
\brief Заголовочный файл с описанием cекции 3
*/


/*!
  \brief Класс для обработки 3 секции
  \todo bit-map
 */
class BMS:public Reader
{
public:
    BMS();
    virtual ~BMS();
    virtual void readSec(ifstream *file);

private:
    long sectionLength;
    int unusedBit;
    bool specificBitmap;
};

#endif // BMS_H
