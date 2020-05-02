#ifndef BMS_H
#define BMS_H
#include <reader.h>
#include <gds.h>
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
    BMS & operator =(const BMS&obj)
    {
        specificBitmap = obj.specificBitmap;
       /* Ni = obj.Ni;
        Nj=obj.Nj;
        La1=obj.La1;
        Lo1=obj.Lo1;
        La2=obj.La2;
        Lo2=obj.Lo2;*/
        return *this;
    }
    virtual void readSec(ifstream *file);
    QList<bool> getBitMap();
private:
    QList<bool> bitMap;
    long sectionLength;
    int unusedBit;
    bool specificBitmap;
};

#endif // BMS_H
