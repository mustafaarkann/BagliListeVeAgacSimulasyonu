/*     
* @file  BagliListe.hpp
* @description   
* @course  1-B
* @assignment  2.Ödev
* @date  14.12.2024
* @author  Mustafa Arkan - mustafaarkan004@gmail.com
*/

#ifndef BAGLILISTE_HPP
#define BAGLILISTE_HPP

#include "Dugum.hpp"
#include <string>
#include <vector>
using namespace std;

class BagliListe
{
    private:
    
        Dugum* son;
        Dugum* mevcut; // SEÇİLİ DÜĞÜM 
        int boslukMiktari = 5; // Yazdırma sırasında kullanılan boşluk miktarı
        int dugumSayisi;
        int sayfa;
        int dugumIndex;
        IkiliAgac ikiliAgac;

    public: 

        Dugum* ilk;
        
        BagliListe();
        ~BagliListe();
        void agaclariYazdir();
        void indeksleriGuncelle();
        void agaciYaz(Dugum* dugum);
        Dugum* getIlk() const;  // İlk düğümü döndüren fonksiyon
        void listeyiYazdir();
        void ekle(Dugum* yeniDugum);
        void dosyaOku(const string& dosyaAdi);
        void bagliListeYaz(); // Listeyi yazdırma
    
        void imlecHareketi(char tus); // İmleç hareketini yönetme
        void dugumSil();

        void cizgiYaz(); // Çizgi yazma
        void isaretYaz(int indeks); // İmleç işareti yazma
        void degerYaz(Dugum* deger); // Değer yazma
        void satirCiz(); // Satır çizme
        void adresYaz(Dugum* adres); // Adres yazma
        void sonrakiAdresYaz(Dugum* sonrakiAdres); // Sonraki adres yazma
        void boslukYaz(int miktar); // Boşluk yazma (tekrar eden işlemi toparlamak için)
        int dugumIndeks(Dugum* hedef);
        void guncelleIndeks(int yeniIndeks); 



};







#endif