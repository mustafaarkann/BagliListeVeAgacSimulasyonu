/*     
* @file  IkiliAgac.hpp
* @description  IkiliAgac sınıfı başlık dosyası
* @course  1-B
* @assignment  2.Ödev
* @date  14.12.2024
* @author  Mustafa Arkan - mustafaarkan004@gmail.com
*/


#ifndef IKILIAGAC_HPP
#define IKILIAGAC_HPP
#include<iostream>
#include <string>
using namespace std;
class IkiliAgac {
public:
    struct AgacDugumu {
        char veri;
        AgacDugumu* sol;
        AgacDugumu* sag;
        
        AgacDugumu(char val) : veri(val), sol(nullptr), sag(nullptr) {}
    };
    
    AgacDugumu* kok;  // Ağacın kökü
    IkiliAgac();  // Yapıcı
    ~IkiliAgac();  // Yıkıcı
   int toplamDeger(AgacDugumu* dugum);
    int degerToInt(char deger);
    void agacYaz();
    int Yukseklik(AgacDugumu *dugum);
    void agacYazTest();
    void agacekle(int veri , AgacDugumu* aktifdugum);
    void aynalaRec(AgacDugumu* dugum); // Ağacı aynalamak için fonksiyon
    void aynalamaIslemi(AgacDugumu* seciliDugum); // Seçili düğümle ayna işlemi yapacak fonksiyon
private:
     // Ağaç kök düğümü
   
    void inorderYaz(AgacDugumu* node) {
        if (node != nullptr) {
            inorderYaz(node->sol);
            cout << node->veri << " ";  // Veya başka bir yazdırma yöntemi
            inorderYaz(node->sag);
        }
    }
    void agacSil(AgacDugumu* dugum);  // Ağacın belleğini temizle
};



#endif
