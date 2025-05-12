/*     
* @file  Dugum.hpp
* @description  Dugum sınıfı başlık dosyası
* @course  1-B
* @assignment  2.Ödev
* @date  14.12.2024
* @author  Mustafa Arkan - mustafaarkan004@gmail.com
*/

#ifndef DUGUM_HPP
#define DUGUM_HPP

#include <IkiliAgac.hpp>


class Dugum
{
    public:
    char veri; // veri türünü değiştirebilriim
    Dugum* sonraki; // sonraki düğüme işaretci
    IkiliAgac* agac;  // Düğümdeki ağaç yapısı

    Dugum(char val); // yapıcı
};

#endif