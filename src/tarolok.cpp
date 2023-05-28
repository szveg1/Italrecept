///
/// \file tarolok.cpp
/// \brief Tároló osztályok függvényeinek definíciói.
///
#include "tarolok.h"
#include "alapanyag.h"
#include <iostream>
///
/// \brief Hozzáad egy alapanyagot a recepthez.
/// \param alapanyag - Pointer a hozzáadandó alapanyagra
/// \param mennyiseg - Hozzáadandó alapanyag mennyisége
///
void Recept::hozzaad(Alapanyag* alapanyag, double mennyiseg){
// Ellenőrizzük, hogy az alapanyag már szerepel-e a receptben
    for(size_t i = 0; i < meret; i++){
        if(pData[i]->getNev() == alapanyag->getNev()){
            delete alapanyag;
            throw "Ez az alapanyag mar szerepel a receptben!";
        }
    }
// Ha nem, akkor mindkét tömböt egyel nagyobbra foglaljuk
    Alapanyag** uj = new Alapanyag*[meret+1];
    double* ujmennyi= new double[meret+1];
// Átmásoljuk az eddigi alapanyagokat, és mennyiségeket
    for(size_t i = 0; i < meret; i++){
        uj[i] = pData[i];
        ujmennyi[i] = mennyisegek[i];
    }
// Régi tömböket töröljük
    delete[] pData;
    delete[] mennyisegek;
// Az új alapanyagot és mennyiséget hozzáadjuk
    uj[meret] = alapanyag->clone();
    delete alapanyag;
    ujmennyi[meret] = mennyiseg;
// Átállítjuk a pointereket az új tömbre
    pData = uj;
    mennyisegek = ujmennyi;
// Növeljük a tároló méretét
    meret++;
}
///
/// \brief Kiírja a receptet.
/// \param os - Output stream
///
void Recept::kiir(std::ostream& os) const{
// kiírjuk a recept nevét
    os << '\n' << nev << std::endl;
// - karakterekkel elválasztjuk a recept nevét a hozzávalóktól
    for(size_t i = 0; i < nev.size(); i++){
        os << "-";
    }
    os << std::endl;
// kiírjuk a hozzávalókat
    for(size_t i = 0; i < meret; i++){
        pData[i]->alapanyagKiir(os);
        os << " " << mennyisegek[i] << pData[i]->getMertekegyseg() << std::endl;
    }
}
///
/// \brief Törli az alapanyagokat a receptből.
///
void Recept::clear(){
    for(size_t i = 0; i < meret; i++){
        delete pData[i];
        pData[i] = NULL;
    }
    meret = 0;
}
///
/// \brief Recept destruktora.
///
Recept::~Recept(){
// töröljük az alapanyagokat
    clear();
// töröljük a tömböt
    delete[] pData;
    delete[] mennyisegek;
}
///
/// \brief Hozzáad egy receptet a tárolóhoz.
/// \param recept - Pointer a hozzáadandó receptre
///
void ReceptTarolo::hozzaad(Recept* recept){
    for(size_t i = 0; i < meret; i++){
        if(receptek[i]->getNev() == recept->getNev()){
            delete recept;
            throw "Ez a recept mar szerepel a receptkonyben!";
        }
    }
// foglalunk egy egy elemmel nagyobb tömböt
    Recept** temp = new Recept*[meret+1];
// átmásoljuk az eddigi recepteket
    for(size_t i = 0; i < meret; i++){
        temp[i] = receptek[i];
    }
// hozzáadjuk az új receptet
    temp[meret] = recept;
// töröljük az eredeti tömböt
    delete[] receptek;
// átállítjuk a pointert az új tömbre
    receptek = temp;
// növeljük a méretet
    meret++;
}
///
/// \brief Töröl egy receptet a tárolóból.
/// \param idx - Törlendő recept indexe
///
void ReceptTarolo::torol(const size_t& idx){
    Recept** uj = new Recept*[meret-1];
    size_t j = 0;
    for(size_t i = 0; i < meret; i++){
        if(i != idx){
            uj[j] = receptek[i];
            j++;
        }
    }
    delete receptek[idx];
    delete[] receptek;
    receptek = uj;
    meret--;
}
///
/// \brief Kiírja a tároló tartalmát.
/// \param os - Output stream
///
void ReceptTarolo::kiir(std::ostream& os) const{
// egyesével kiír minden receptet
    for(size_t i = 0; i < meret; i++){
        receptek[i]->kiir(os);
        os << std::endl;
    }
}
///
/// \brief ReceptTarolo destruktora.
///
ReceptTarolo::~ReceptTarolo(){
    for(size_t i = 0; i < this->size(); i++){
        delete receptek[i];
    }
    delete[] receptek;
}
///
/// \brief Hozzáad egy alapanyagot a tárolóhoz.
///
/// A tárolóhoz csak akkor adunk hozzá alapanyagot,
/// ha még nem létezik benne azzal megegyező nevű.
///
/// \param alapanyag - Pointer a hozzáadandó alapanyagra
///
void AlapanyagTarolo::hozzaad(Alapanyag* alapanyag){
    bool letezik = false;
// végignézzük a tárolóban lévő alapanyagokat
    for(size_t i = 0; i < meret; i++){
// ha van "ugyanilyen" alapanyag
        if(pData[i]->getNev() == alapanyag->getNev()){
            letezik = true;
// töröljük a paraméterként kapott alapanyagot
            delete alapanyag;
// kilépünk a ciklusból
            break;
        }
    }
// ha nem létezett ilyen alapanyag
    if(!letezik){
// foglalunk egy egy elemmel nagyobb tömböt
        Alapanyag** tmp = new Alapanyag*[meret+1];
// átmásoljuk az eddigi alapanyagokat
        for(size_t i = 0; i < meret; i++){
            tmp[i] = pData[i];
        }
// hozzáadjuk az új alapanyagot
        tmp[meret] = alapanyag->clone();
        delete alapanyag;
// töröljük az eredeti tömböt
        delete[] pData;
// átállítjuk a pointert az új tömbre
        pData = tmp;
// növeljük a méretet
        meret++;
    }
}
///
/// \brief Kiírja a tároló tartalmát.
/// \param os - Output stream
///
void AlapanyagTarolo::kiir(std::ostream& os) const{
    for(size_t i = 0; i < meret; i++){
        os << '[' << i << "] ";
        pData[i]->alapanyagKiir(os);
        os << '(' << pData[i]->getMertekegyseg() << ")\n";
    }
    os << std::endl;
}
///
/// \brief AlapanyagTarolo destruktora.
///
AlapanyagTarolo::~AlapanyagTarolo(){
// töröljük az alapanyagokat
    for(size_t i = 0; i < meret; i++){
        delete pData[i];
    }
// töröljük a tömböt
    delete[] pData;
}



