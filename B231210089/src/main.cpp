/*     
* @file  Main.cpp
* @description  Ana fonksiyon
* @course  1-B
* @assignment  2.Ödev
* @date  14.12.2024
* @author  Mustafa Arkan - mustafaarkan004@gmail.com
*/

#include <iostream>
#include "BagliListe.hpp"
using namespace std;

int main() {
    BagliListe liste;
     IkiliAgac agac;
     liste.dosyaOku("agaclar.txt");
     
       char tus;
    while (true) {
        #ifdef _WIN32
            system("cls");  // Windows için ekranı temizle
        #else
            system("clear");  // Diğer sistemler için ekranı temizle
        #endif

        // Bağlı listeyi yazdır
        liste.bagliListeYaz(); 
               
        // Kullanıcı girişi
        cout << "\n -> ";
        cin >> tus;

        if (tus == 'q' || tus=='Q') break; // Çıkış

        // Kullanıcı girdisine göre imleci hareket ettir
        liste.imlecHareketi(tus);
    }


    return 0;
}
