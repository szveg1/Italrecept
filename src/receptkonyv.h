///
/// \file receptkonyv.h
/// Receptkönyv osztály deklarációja, inline függvényei
/// és egy globális bemenetkezelő függvénysablon.
///
#ifndef RECEPTKONYV_H
#define RECEPTKONYV_H
#include <iostream>
#include "tarolok.h"
#include "memtrace.h"
#include "string.h"
///
/// \class Receptkonyv
/// \brief Recepteket és alapanyagokat tároló osztály.
///
/// Ez az osztály valósítja meg a program fő funkcióit.
///
class Receptkonyv{
private:
    ReceptTarolo receptek;          ///< Recepteket tárolja 
    AlapanyagTarolo alapanyagok;    ///< Alapanyagokat tárolja
public:
    void ujRecept(std::istream& is = std::cin, std::ostream& os = std::cout);
    void ujAlapanyag(std::istream& is = std::cin, std::ostream& os = std::cout);
    void fajlbaIr(const String& fajlnev = "receptek.dat") const;
    void fajlbolOlvas(const String& fajlnev = "receptek.dat", std::ostream& os = std::cout);
    void receptTorol(std::istream& is = std::cin, std::ostream& os = std::cout);
    void alapanyagokKiir(std::ostream& os = std::cout) const;
    void receptekKiir(std::istream& is = std::cin, std::ostream& os = std::cout) const;
    static void fomenu(std::ostream& os = std::cout);
};
///
/// \brief Globális bemenetkezelő függvénysablon.
///
template <typename T>
    void bemenetKezel(std::istream& is, std::ostream& os, String uzenet, T& valasz){
        os << uzenet;
        is >> valasz;
//  ha nem sikerült a beolvasás akkor "reseteljük" az input streamet,
//  kiírjuk a hibaüzenetet és megpróbáljuk újra beolvasni a választ.
        while(is.fail()){
//  ha pedig EOF érkezik, akkor kivételt dobunk
            if(is.eof())
                throw("EOF kerult beutesre! Kilepes...");
            os << "Hibas bemenet! Valasszon ujra!" << std::endl;
            is.clear();
            is.ignore(1000, '\n');
            is >> valasz;
        }
    }
#endif // RECEPTKONYV_H
