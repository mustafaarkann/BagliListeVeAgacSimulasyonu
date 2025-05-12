/*     
* @file  BagliListe.cpp
* @description   Bağlı listeyi yazdırma, imleç hareketini yönetme ve kullanıcı etkileşimi
* @course  1-B
* @assignment  2.Ödev
* @date  14.12.2024
* @author  Mustafa Arkan - mustafaarkan004@gmail.com
*/

#include "BagliListe.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "IkiliAgac.hpp"
#include "Dugum.hpp"
using namespace std;

// Constructor
BagliListe::BagliListe() {
    ilk = nullptr;
    son = nullptr;
    mevcut = nullptr;  // İmleç başta null olmalı
    dugumSayisi=0;
    sayfa=0;   
    int dugumIndex = 0;
}

// Destructor
BagliListe::~BagliListe() {
    Dugum* gec = ilk;
    while (gec != nullptr) {
        Dugum* sil = gec;
        gec = gec->sonraki;
        delete sil;
    }
}

// Yeni düğüm ekle
void BagliListe::ekle(Dugum* yeniDugum) {
    if (ilk == nullptr) {
        ilk = yeniDugum;    // İlk düğüm olarak yeniDugum ekleniyor
        son = yeniDugum;    // Son düğüm de yeniDugum oluyor
        mevcut = ilk;       // Mevcut imleç ilk düğüme yönlendiriliyor
    } else {
        son->sonraki = yeniDugum; // Son düğümün sonraki işaretçisi yeniDugum'a yönlendirilir
        son = yeniDugum;          // Son düğüm yeniDugum olur
    }
}


// Dosyadan okuma işlemi
void BagliListe::dosyaOku(const std::string& dosyaAdi) {
    std::ifstream dosya(dosyaAdi);
    if (!dosya.is_open()) {
        std::cerr << "Dosya açılamadı: " << dosyaAdi << std::endl;
        return;
    }

    std::string satir;
    while (getline(dosya, satir)) {
        if (!satir.empty()) {
            // Yeni düğüm oluşturuluyor
            Dugum* yeniDugum = new Dugum(satir[0]);

            // Yeni bir ikili ağaç oluşturuluyor
            IkiliAgac* yeniAgac = new IkiliAgac();
            for (char ch : satir) {
                yeniAgac->agacekle(ch, yeniAgac->kok); // Ağaç her karakterle güncelleniyor
            }

            // Düğümün ağacını ata
            yeniDugum->agac = yeniAgac;

            // Yeni düğümü bağlı listeye ekle
            ekle(yeniDugum); // Bu kısımda artık yeniDugum ekleniyor
            dugumSayisi++;
        }
        
    }
    dosya.close();
}

// Boşluk yazdırma (daha temiz kod için)
void BagliListe::boslukYaz(int miktar) 
{

    for (int i = 0; i < miktar; i++) {
        cout << " ";
    }
}

// Çizgi yazdırma
void BagliListe::cizgiYaz() {
    boslukYaz(boslukMiktari);
    cout << "***********";
}

// İmleç işareti yazdırma
void BagliListe::isaretYaz(int indeks) {
    // İmleç hizalaması için boşluk miktarını hesaplayarak yazdır
    cout<<"     ";
    boslukYaz(indeks * (boslukMiktari + 11)); // Her düğümün genişliği kadar boşluk bırak
    cout << "^^^^^^^^^^^"<<endl;  // İmleç işareti

    cout<<"     ";
    boslukYaz(indeks * (boslukMiktari + 11)); // Her düğümün genişliği kadar boşluk bırak
    cout << "|||||||||||"<<endl;

    cout<<"     ";
    boslukYaz(indeks * (boslukMiktari + 11)); // Her düğümün genişliği kadar boşluk bırak
    cout << "|||||||||||";
}

// Değer yazdırma
void BagliListe::degerYaz(Dugum* gecici) {
    boslukYaz((boslukMiktari));
    cout << "*";
    cout << setw(9) << gecici->agac->toplamDeger(gecici->agac->kok);
    cout << "*";
}

// Satır çizme    !!!! DÜĞÜM SAYISI KADAR SATIR ÇİZ !!!!
void BagliListe::satirCiz() 
{
    for (int i = 0; i < dugumSayisi; i++) { // !!! düğümsayısıkadar olan değişkeni ekle
        cizgiYaz(); 
    }
    cout << endl;
}

void BagliListe::bagliListeYaz() 
{
    satirCiz();  // Üst sınır çizgisi
    Dugum* gecici = ilk;
    int index = 0;

    // Düğümleri yazdır (Adresler)
    while (gecici != nullptr && index < (sayfa + 1) * 10) {
        if (index >= sayfa * 10) {
            adresYaz(gecici);  // Düğüm adresi
        }
        gecici = gecici->sonraki;
        index++;
    }
    cout << endl;

    satirCiz();  // Ara çizgi

    gecici = ilk;
    index = 0;

    // Düğüm değerlerini yazdır
    while (gecici != nullptr && index < (sayfa + 1) * 10) {
        if (index >= sayfa * 10) {
            degerYaz(gecici);  // Düğümdeki değer
        }
        gecici = gecici->sonraki;
        index++;
    }
    cout << endl;

    satirCiz();  // Ara çizgi (Sonraki adresler için)

    gecici = ilk;
    index = 0;

    // Sonraki düğüm adreslerini yazdır
    while (gecici != nullptr && index < (sayfa + 1) * 10) {
        if (index >= sayfa * 10) {
            if (gecici->sonraki == nullptr) {
                cout<<"     ";
                cout<<"*";
                cout << "NULL";  // Son düğüm için NULL yaz
                cout<<"      *";
            } else {
                sonrakiAdresYaz(gecici->sonraki);  // Sonraki düğüm adresi
            }
        }
        gecici = gecici->sonraki;
        index++;
    }
    cout << endl<<endl;

    satirCiz();  // Alt sınır çizgisi

    // İmleci yazdırma (en alt satırda)
  
    gecici = ilk;
    index = 0;
    while (gecici != nullptr && index < (sayfa + 1) * 10) {
        if (index >= sayfa * 10) {
            if (gecici == mevcut) {
                isaretYaz(index % 10);  // Sayfa içindeki pozisyonu kullan
                break;  // İmleç bir kez yazıldıktan sonra döngüden çık
            }
        }
        gecici = gecici->sonraki;
        index++;
    }

    cout<<endl<<endl<<endl;

   // Seçili düğümün kontrolü ve ağacın yazdırılması
    if (mevcut != nullptr && mevcut->agac != nullptr) {
        mevcut->agac->agacYaz();  // Mevcut düğümün ağacını yazdır
    } else {
        cout << " " <<endl;
    }

}

// getIlk fonksiyonunu implement ediyoruz
Dugum* BagliListe::getIlk() const {
    return ilk;  // ilk düğümü döndürüyoruz
}

void BagliListe::imlecHareketi(char tus) {
    if (tus == 'a' || tus=='A' && mevcut != nullptr) {
        // Eğer mevcut düğüm listenin başıysa, hareket etme
        if (mevcut == ilk) {
            // Başlangıç noktasında hareket engellenir
            return;
        } else {
            // Bir önceki düğüme geç
            Dugum* gecici = ilk;
            while (gecici->sonraki != mevcut) {
                gecici = gecici->sonraki;
            }
            mevcut = gecici;

            // Eğer sayfa başını geçtiysek, bir önceki sayfaya geç
            int mevcutIndex = dugumIndeks(mevcut);
            if (mevcutIndex < sayfa * 10) {
                sayfa--;
            }
        }
    } else if (tus == 'd' || tus=='D' && mevcut != nullptr) {
        // Eğer mevcut düğüm listenin sonundaysa, hareket etme
        if (mevcut->sonraki == nullptr) {
            // Son düğümde hareket engellenir
            return;
        } else {
            // Sonraki düğüme git
            mevcut = mevcut->sonraki;

            // Eğer sayfa sonunu geçtiysek, bir sonraki sayfaya geç
            int mevcutIndex = dugumIndeks(mevcut);
            if (mevcutIndex >= (sayfa + 1) * 10) {
                sayfa++;
            }
        }
    }else if (tus == 's' || tus=='S') {
        dugumSil();
    }else if(tus=='w' || tus=='W')
    {
        if (mevcut != nullptr && mevcut->agac != nullptr) {
                mevcut->agac->aynalamaIslemi(mevcut->agac->kok);  // Mevcut ağacın aynalanması
            } else {
                std::cout << "Mevcut düğümde bağlantili bir ağaç yok!" << std::endl;
            }
    }

    bagliListeYaz();
}

void BagliListe::dugumSil() {
    if (mevcut == nullptr) {
        return;  // Eğer mevcut düğüm yoksa, hiçbir şey yapma
    }

    // Eğer mevcut düğüm ilk düğümse
    if (mevcut == ilk) {
        Dugum* silinecek = ilk;
        ilk = ilk->sonraki;  // İlk düğümü bir sonraki düğümle değiştir

        // Eğer ilk düğüm varsa, onun sonrakini NULL yapmaya gerek yok, çünkü tek yönlü liste
        if (ilk == nullptr) {
            son = nullptr;  // Eğer liste boşsa, son işaretçisi de null olmalı
        }

        // Eğer ilk düğüm silindiyse, imlecini bir sonraki düğüme yönlendir
        if (mevcut->sonraki != nullptr) {
            mevcut = mevcut->sonraki;
        } else {
            mevcut = nullptr;  // Eğer liste boşsa imleç null olur
        }

        delete silinecek;  // Silinen düğümü serbest bırak
    } 
    else { // Eğer silinen düğüm ilk düğüm değilse
        Dugum* silinecek = mevcut;
        Dugum* onceki = ilk;

        // Mevcut düğümü bul
        while (onceki->sonraki != mevcut) {
            onceki = onceki->sonraki;
        }

        // Düğüm silme
        onceki->sonraki = mevcut->sonraki;
        if (mevcut->sonraki == nullptr) {
            // Eğer mevcut son düğümse, mevcut pointer'ı NULL yapılır
            mevcut = onceki;
        } else {
            // Sonraki düğümü güncelleriz
            mevcut = mevcut->sonraki;
        }

        delete silinecek;  // Silinen düğümü serbest bırak

        //indeksleriGuncelle();
    }
}

int BagliListe::dugumIndeks(Dugum* hedef) {
    Dugum* gecici = ilk;
    int index = 0;

    while (gecici != nullptr) {
        if (gecici == hedef) {
            return index;  // Hedef düğüm bulundu
        }
        gecici = gecici->sonraki;
        index++;
    }
    return -1;  // Hedef düğüm bulunamazsa
}

// Adres yazdırma
void BagliListe::adresYaz(Dugum* adres) {
    boslukYaz(boslukMiktari);
    cout << "*";
    cout << setw(1) << (void*)adres;  // Gerçek bellek adresi yazdırma
    cout << "*";
}

// Sonraki adres yazdırma
void BagliListe::sonrakiAdresYaz(Dugum* sonrakiAdres) {
    boslukYaz(boslukMiktari);
    cout << "*";
    if (sonrakiAdres != nullptr) {
        cout << setw(1) << (void*)sonrakiAdres;  // Eğer sonraki düğüm varsa, adresini yazdır
    } else {
        cout << setw(3) << "NULL";  // Eğer sonraki düğüm yoksa "NULL" yazdır
    }
    cout << "*";
}









