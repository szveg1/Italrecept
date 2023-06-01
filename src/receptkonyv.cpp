///
/// \file receptkonyv.cpp
/// \brief Receptkönyv osztály függvényeinek definíciói.
///
#include <iostream>
#include <fstream>
#include "receptkonyv.h"
#include "memtrace.h"
///
/// \brief Új recept hozzáadását koordináló függvény.
///
void Receptkonyv::ujRecept(std::istream& is, std::ostream& os) {
    String nev;
    bool letezik = false;
    size_t valasz;
    double mennyi;
//  bekérjük a recept nevét
    try{bemenetKezel(is, os, "\nMi legyen a recept neve?\n", nev);}
    catch(const char *e){std::cerr << e;}
// megnézzük, hogy van-e már ilyen nevű recept
// ha igen akkor nem engedjük a felhasználónak,
// hogy létrehozzon egy duplikátumot
    for(size_t i = 0; i < receptek.size(); i++){
        if(receptek[i]->getNev() == nev){
            letezik = true;
            throw "Mar letezik ilyen nevu recept!\n";
        }
    }
    if(letezik)
        return;
// egyébként létrehozzuk az új receptet
    Recept* r = new Recept(nev);
// majd a felhasználó kiválogatja milyen alapanyagokból
// és mennyiségekből álljon a recept, esetleg új alapanyagot
// is hozzáadhat.
// minden lépés után kiírjuk a receptet, hogy lássuk
// milyen állapotban van.
// ha a felhasználó nem ad hozzá egy alapanyagot sem
// akkor a recept nem kerül mentésre
    do{
        alapanyagokKiir(os);
        os << '[' << alapanyagok.size() << "] Uj alapanyag" << std::endl;
        os << '[' << alapanyagok.size() + 1 << "] Kesz" << std::endl;
        os << '[' << alapanyagok.size() + 2 << "] Megse" << std::endl;
        os << "A recept eddig: " << std::endl;
        r->kiir(os);
        try{bemenetKezel(is, os, "Valasszon alapanyagot : ", valasz);
            if(valasz < alapanyagok.size()){
                bemenetKezel(is, os, "Mennyit?\n", mennyi);
                r->hozzaad(alapanyagok[valasz]->clone(), mennyi);
            }else if(valasz == alapanyagok.size()){
                ujAlapanyag();
            }else if(valasz == alapanyagok.size() + 1 || valasz == alapanyagok.size() + 2){
                break;
            }else{}
        }catch (const char* e){std::cerr << e;}
    }while(true);
    if(valasz == alapanyagok.size() + 2){
        delete r;
    }else{
        if(r->size() == 0){
            delete r;
            throw "Nem hozhat letre ures receptet!\n";
        }else
            receptek.hozzaad(r);
    }
}
///
/// \brief Új alapanyag hozzáadását koordináló függvény.
///
void Receptkonyv::ujAlapanyag(std::istream& is, std::ostream& os){
    String nev, mertekegyseg, tipus;
    double alkoholTartalom;
    bool letezik = false;
//  bekérjük az alapanyag nevét
//  megnézzük, hogy van-e már ilyen nevű alapanyag
    bemenetKezel(is, os, "Mi legyen az alapanyag neve?\n", nev);
    for(size_t i = 0; i < alapanyagok.size(); i++){
        if(alapanyagok[i]->getNev() == nev){
            throw "Mar letezik ilyen nevu alapanyag!\n";
            letezik = true;
        }
    }
//  ha van ilyen nevű alapanyag akkor visszatérünk
    if(letezik)
        return;
//  egyébként bekérjük az alapanyag adatait

    bemenetKezel(is, os, "Mi legyen az alapanyag mertekegysege?\n", mertekegyseg);
    bemenetKezel(is, os, "Mi legyen az alapanyag tipusa?\n[A] - Alkoholos\n[M] - Alkoholmentes\n[D] - Diszites\n", tipus);
    if(tipus == "A"){
        bemenetKezel(is, os, "Mennyi legyen az alapanyag alkoholtartalma?\n", alkoholTartalom);
        alapanyagok.hozzaad(new Alkoholos(nev, mertekegyseg, alkoholTartalom));
    }else if(tipus == "M"){
        bemenetKezel(is, os, "Milyen kategoria?\n", tipus);
        alapanyagok.hozzaad(new Alkoholmentes(nev, mertekegyseg, tipus));
    }else if(tipus == "D"){
        alapanyagok.hozzaad(new Diszites(nev, mertekegyseg));
    }else{
        throw "Hibas tipus!\n";
    }
    os << "Alapanyag letrehozva!\n";
}
///
/// \brief Fájlból olvasást koordináló függvény.
/// \param fajlnev A fájl neve.
/// \param os Output stream
///
void Receptkonyv::fajlbolOlvas(const String& fajlnev, std::ostream& os) {
    String sor, nev, mertekegyseg, tipus;
    size_t hany_db = 0;
    double mennyiseg, alkoholTartalom;
    std::ifstream fin;
    Recept* r;
    fin.open(fajlnev.c_str());
//  ha nem sikerült megnyitni a fájlt akkor hibát dobunk
    if(fin.fail()){
        fin.close();
        throw std::ifstream::failure("Nem sikerult megnyitni a fajlt!\n");
    }
// fájl végéig olvasunk
    while(fin >> sor){
//  ha a sorban van | akkor receptet olvasunk
        if(sor.contains('|')){
            nev = sor.remove('|');
            r = new Recept(nev);
//  ha a sorban van ; akkor alapanyagot olvasunk
        }else if(sor.contains(';')){
//  a sor első karaktere határozza meg az alapanyag típusát
            tipus = sor.split(';');
//  ha a sor első karaktere A akkor alkoholos alapanyagot olvasunk
            if(tipus == "A"){
                nev = sor.split(';');
                alkoholTartalom = atof(sor.split(';').c_str()); 
                mertekegyseg = sor.split(';');
                mennyiseg = atof(sor.split(';').c_str());
                try{r->hozzaad(new Alkoholos(nev, mertekegyseg, alkoholTartalom), mennyiseg);}
                catch (const char* e){std::cerr << e;}
                alapanyagok.hozzaad(new Alkoholos(nev, mertekegyseg, alkoholTartalom));
//  ha a sor első karaktere M akkor alkoholmentes alapanyagot olvasunk
            }else if(tipus == "M"){
                nev = sor.split(';');
                mertekegyseg = sor.split(';');
                tipus = sor.split(';');
                mennyiseg = atof(sor.split(';').c_str());
                try{r->hozzaad(new Alkoholmentes(nev, mertekegyseg, tipus), mennyiseg);}
                catch (const char* e){std::cerr << e;}
                alapanyagok.hozzaad(new Alkoholmentes(nev, mertekegyseg, tipus));
//  ha a sor első karaktere D akkor diszito alapanyagot olvasunk
            }else if(tipus == "D"){
                nev = sor.split(';');
                mertekegyseg = sor.split(';');
                mennyiseg = atof(sor.split(';').c_str());
                try{r->hozzaad(new Diszites(nev, mertekegyseg), mennyiseg);}
                catch (const char* e){std::cerr << e;}
                alapanyagok.hozzaad(new Diszites(nev, mertekegyseg));
//  ha ezek közül egyik se, akkor hibás a fájl, hibát dobunk
            }else{
                delete r;
                fin.close();
                throw "Hibas a fajl formazasa!";
            }
//  ha a sorban - van akkor receptet zárunk
        }else if(sor.contains('-')){
            receptek.hozzaad(r);
            hany_db++;
        }
    }
    fin.close();
    os << hany_db << " db recept beolvasva." << std::endl;
}
///
/// \brief Fájlba írást koordináló függvény.
/// \param fajlnev A fájl neve.
///
void Receptkonyv::fajlbaIr(const String& fajlnev) const{
    std::ofstream fout;
    fout.open(fajlnev.c_str());
    if(fout.fail()){
        throw std::ofstream::failure("Nem sikerult megnyitni a fajlt!\n");
    }

    for(size_t i = 0; i < receptek.size(); i++){
        fout << "|" << receptek[i]->getNev() << "|\n";
        for(size_t j = 0; j < receptek[i]->size(); j++){;
            receptek[i]->operator[](j)->fajlbaIr(fout);
            fout << receptek[i]->getMennyisegek()[j] << ";\n";
        }
        fout << "-\n";
    }
    fout.close();
}
///
/// \brief Recept törlését koordináló függvény.
///
void Receptkonyv::receptTorol(std::istream& is, std::ostream& os){
//  kiírjuk a recepteket
    for(size_t i = 0; i < receptek.size(); i++){
        os << "[" << i + 1 << "] " << receptek[i]->getNev() << std::endl;
    }
//  plusz a lehetőséget hogy ne töröljünk semmit
    os << "[" << receptek.size() + 1 << "] Megse\n" << std::endl;
    size_t idx;
//  bekérjük a felhasználó választását
    try{bemenetKezel(is, os, "Melyik recept keruljon torlesre?\n", idx);}
    catch(const char* e){std::cerr << e;}
    if(idx <= receptek.size()){
        receptek.torol(idx - 1);
    }else if(idx == receptek.size() + 1){
        return;
    }else{
        throw "Nincs ilyen recept!\n";
    }
}
///
/// \brief Kiír minden tárolt alapanyagot
/// \param os Output stream
///
void Receptkonyv::alapanyagokKiir(std::ostream& os) const{
    os << "\nAlapanyagok:\n------------" << std::endl;
    alapanyagok.kiir(os);
}
///
/// \brief Kiír minden tárolt receptet
///
/// A felhasználó választásától függően kiírja a recept hozzávalóit
///
/// \param is Input stream
/// \param os Output stream
///
void Receptkonyv::receptekKiir(std::istream& is,std::ostream& os) const {
    os << "\nReceptek:\n---------" << std::endl;
    for(size_t i = 0; i < receptek.size(); i++){
        os << "[" << i + 1 << "] " << receptek[i]->getNev() << std::endl;
    }
    os << "[" << receptek.size() + 1 << "] Vissza\n" << std::endl;
    size_t valasz;
    try{bemenetKezel(is, os, "Valasszon receptet: ", valasz);}
    catch(const char* e){std::cerr << e;}
    if(valasz <= receptek.size()){
        receptek[valasz - 1]->kiir(os);
    }else if(valasz == receptek.size() + 1){
        return;
    }
}
///
/// \brief Kiírja a főmenüt
/// \param os Output stream
///
void Receptkonyv::fomenu(std::ostream& os){
    os << "\n[1] Uj recept" << std::endl;
    os << "[2] Uj alapanyag" << std::endl;
    os << "[3] Receptek listazasa" << std::endl;
    os << "[4] Alapanyagok listazasa" << std::endl;
    os << "[5] Recept torlese" << std::endl;
    os << "[6] Kilepes" << std::endl;
}