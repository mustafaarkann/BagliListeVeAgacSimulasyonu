/*     
* @file  Dugum.cpp
* @description   Dugum sınıfı
* @course  1-B
* @assignment  2.Ödev
* @date  14.12.2024
* @author  Mustafa Arkan - mustafaarkan004@gmail.com
*/
#include "Dugum.hpp"

Dugum::Dugum(char val)
{
    agac=new IkiliAgac();    //  yapılan değişiklik 
    veri=val;
    sonraki = 0;
    agac=nullptr;
}