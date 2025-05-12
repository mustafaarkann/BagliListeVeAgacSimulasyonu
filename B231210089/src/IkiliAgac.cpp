/*     
* @file  IkiliAgac.cpp
* @description  Agac işlemlerini yapan sınıf yapısı
* @course  1-B
* @assignment  2.Ödev
* @date  14.12.2024
* @author  Mustafa Arkan - mustafaarkan004@gmail.com
*/

#include "IkiliAgac.hpp"
#include <iostream>

IkiliAgac::IkiliAgac() : kok(nullptr)  {}



void IkiliAgac::agacekle(int veri, AgacDugumu* aktifdugum) {
    if (aktifdugum == nullptr) {
        // Eğer aktifdugum geçersizse, bu durumda ağacın kökünü kontrol et
        if (kok == nullptr) {
            // Kök düğüm null ise, yeni bir kök oluşturuyoruz
            kok = new AgacDugumu(veri);
            return;  // Kök düğüm oluşturulduktan sonra işlemi bitiriyoruz
        }
    }

    if (aktifdugum->veri > veri) {
        if (aktifdugum->sol) {
            agacekle(veri, aktifdugum->sol);
        } else {
            aktifdugum->sol = new AgacDugumu(veri);
        }
    } else if (aktifdugum->veri < veri) {
        if (aktifdugum->sag) {
            agacekle(veri, aktifdugum->sag);
        } else {
            aktifdugum->sag = new AgacDugumu(veri);
        }
    } else {
        // Aynı değer varsa, eklemiyoruz
        return;
    }
}

IkiliAgac::~IkiliAgac() {
    agacSil(kok);
}

void IkiliAgac::agacSil(AgacDugumu* dugum) {
    if (dugum == nullptr) return;
    agacSil(dugum->sol);
    agacSil(dugum->sag);
    delete dugum;
}

int IkiliAgac::Yukseklik(AgacDugumu* dugum) {
    if (dugum == nullptr) {
        return -1;  // Boş bir düğümde yükseklik -1 olarak kabul edilir (veya 0 da olabilir, tercihe göre)
    }

    // Sol ve sağ alt ağaçların yüksekliklerini hesapla
    int solYukseklik = Yukseklik(dugum->sol);
    int sagYukseklik = Yukseklik(dugum->sag);

    // En büyük yüksekliği seç ve 1 ekle (bu düğümün yüksekliği)
    return 1 + max(solYukseklik, sagYukseklik);
}

void IkiliAgac::agacYaz() {
    if (kok == nullptr) {
        return;  // Eğer ağaç boşsa, yazdırmaya gerek yok.
    }

    int derinlik = Yukseklik(kok) + 1;  // Ağacın yüksekliği +1
    int maxWidth = (1 << derinlik) - 1;  // En geniş satır uzunluğu

    struct DugumBilgi {
        AgacDugumu* dugum;
        int pozisyon;
    };

    DugumBilgi kuyruk[1024];  // Kuyruk yapısı
    int bas = 0, son = 0;  // Kuyruğun başı ve sonu

    kuyruk[son++] = {kok, maxWidth / 2};  // Kök düğüm başlangıç pozisyonu
    int currentLevel = 0;  // Başlangıç seviyesi

    while (bas < son) {
        int size = son - bas;  // Şu anki seviyedeki düğüm sayısı
        string nodesLine(maxWidth, ' ');  // Düğümler için boş alan
        string linksLine(maxWidth, ' ');  // Bağlantılar için boş alan

        for (int i = 0; i < size; i++) {
            DugumBilgi front = kuyruk[bas++];  // Kuyruğun başındaki öğe
            AgacDugumu* dugum = front.dugum;
            int pos = front.pozisyon;  // Düğümün pozisyonu

            if (dugum) {
                nodesLine[pos] = dugum->veri;  // Düğümün verisini yazdır

                // Sol alt ağacı ekleme
                if (dugum->sol) {
                    int solPos = pos - (1 << (derinlik - currentLevel - 2));  // Sol pozisyonu hesapla
                    kuyruk[son++] = {dugum->sol, solPos};  // Sol çocuğu kuyruğa ekle
                    linksLine[(pos + solPos) / 2] = '.';  // Sol bağlantıyı ekle
                }

                // Sağ alt ağacı ekleme
                if (dugum->sag) {
                    int sagPos = pos + (1 << (derinlik - currentLevel - 2));  // Sağ pozisyonu hesapla
                    kuyruk[son++] = {dugum->sag, sagPos};  // Sağ çocuğu kuyruğa ekle
                    linksLine[(pos + sagPos) / 2] = '.';  // Sağ bağlantıyı ekle
                }
            }
        }

        // Her seviyenin yazdırılması
        cout << nodesLine << endl;  // Düğüm satırı
        cout << linksLine << endl;  // Bağlantı satırı

        currentLevel++;  // Bir sonraki seviyeye geç
    }
}

void IkiliAgac::aynalamaIslemi(AgacDugumu* seciliDugum) {
    if (seciliDugum == nullptr) {
        cout << "Seçili düğüm bulunmuyor!" << endl;
        return;
    }

    aynalaRec(seciliDugum);
    cout << "Seçili düğümle bağlantılı ağaç aynalandı!" << endl;
}

void IkiliAgac::aynalaRec(AgacDugumu* dugum) {
    if (dugum == nullptr) {
        return;
    }

    // Sol ve sağ alt ağaçları takas et
    swap(dugum->sol, dugum->sag);

    // Rekürsif olarak sol ve sağ alt ağaçları aynala
    aynalaRec(dugum->sol);
    aynalaRec(dugum->sag);
}

int IkiliAgac::toplamDeger(AgacDugumu* dugum) {
    // Temel durum: Düğüm null ise, yani ağaç boşsa
    if (dugum == nullptr)
        return 0;

    int toplam = 0;

    // Eğer sol düğüm varsa, 2 katını alıyoruz
    if (dugum->sol != nullptr) {
        toplam += (2 * int(dugum->sol->veri));  // Sol düğümün değeri
        toplam += toplamDeger(dugum->sol);  // Sol alt düğümleri hesapla
    }

    // Eğer sağ düğüm varsa, değerini olduğu gibi alıyoruz
    if (dugum->sag != nullptr) {
        toplam += int(dugum->sag->veri);  // Sağ düğümün değeri
        toplam += toplamDeger(dugum->sag);  // Sağ alt düğümleri hesapla
    }

    // Kök düğümün değeri
    toplam += int(dugum->veri);

    return toplam;
}



