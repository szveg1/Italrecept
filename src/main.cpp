#include <iostream>

#include "gtest_lite.h"
#include "string.h"
#include "alapanyag.h"
#include "tarolok.h"
#include "receptkonyv.h"
#include "tesztek.h"
#include "memtrace.h"

int main() {
    bool tesztek;
    bemenetKezel(std::cin, std::cout, "Tesztek futtatasa? (1 - igen, 0 - nem): ", tesztek);
    if(tesztek){
        test();
    }else{
    Receptkonyv rk;
    try{rk.fajlbolOlvas("receptek.dat");}
    catch (const char* e){std::cerr << e;}
    size_t valasz;
    do{
        Receptkonyv::fomenu();
        bemenetKezel(std::cin, std::cout, "Valasszon menupontot: ", valasz);
        switch(valasz){
            case 1:
                try{rk.ujRecept();}
                catch (const char* e){std::cerr << e;}
                break;
            case 2:
                try{rk.ujAlapanyag();}
                catch (const char* e){std::cerr << e;}
                break;
            case 3:
                rk.receptekKiir();
                break;
            case 4:
                rk.alapanyagokKiir();
                break;
            case 5:
                try{rk.receptTorol();}
                catch (const char* e){std::cerr << e;}
                break;
            case 6:
                rk.fajlbaIr();
                std::cout << "Viszlat!" << std::endl;
                break;
            default:
                std::cout << "Hibas bemenet! Valasszon ujra!" << std::endl;
                break;
        }
    }while(valasz != 6);
    }
}
