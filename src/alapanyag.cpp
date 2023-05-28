///
/// \file alapanyag.cpp
/// Ez a fájl tartalmazza az alapanyag osztályok
/// tagfüggvényeinek a definícióit.
///
#include "memtrace.h"
#include "alapanyag.h"
#include <iostream>
#include <fstream>
#include <string>
///
/// \brief Alkoholos alapanyag kiírása
///
/// Az alkoholos alapanyag kiírása a következő formában történik:
///     "Alapanyag neve (alkohol) mennyiségmértékegység (alkoholtartalom%)"
///
/// \param os - Output stream
//
void Alkoholos::alapanyagKiir(std::ostream& os) const{
    os << getNev() << " (alkohol " << getAlkoholTartalom() << "%) ";
}
///
/// \brief Alkoholos alapanyag kiírása fájlba
///
/// Az alkoholos alapanyag kiírása a következő formában történik:
///     "A;Alapanyag neve;alkoholtartalom;mértékegység;mennyiseg;"
///
/// \param ofs - Output filestream
///
void Alkoholos::fajlbaIr(std::ofstream& ofs) const{
    ofs << "A;" << getNev() << ";" << getAlkoholTartalom() << ";" << getMertekegyseg() << ";";
}
///
/// \brief Mélymásolatot készít az alkoholos alapanyagról
///
Alapanyag* Alkoholos::clone() const{
    Alkoholos* uj = new Alkoholos(this->getNev(), this->getMertekegyseg(), this->getAlkoholTartalom());
    return uj;
}
///
/// \brief Alkoholmentes alapanyag kiírása
///
/// Az alkoholmentes alapanyag kiírása a következő formában történik:
///     "Alapanyag neve (tipus (pl: udito, gyumolcsle, stb.)) mennyiségmértékegység"
///
/// \param os - Output stream
///
void Alkoholmentes::alapanyagKiir(std::ostream& os) const{
    os  << getNev() << " (" << getTipus() << ") ";
}
///
/// \brief Alkoholmentes alapanyag kiírása fájlba
///
/// Az alkoholmentes alapanyag kiírása a következő formában történik:
///     "M;Alapanyag neve;mértékegység;mennyiseg;"
///
/// \param ofs - Output filestream
///
void Alkoholmentes::fajlbaIr(std::ofstream& ofs) const{
    ofs << "M;" << getNev() << ";" << getMertekegyseg() << ";" << getTipus() << ";";
}
///
/// \brief Mélymásolatot készít az alkoholmentes alapanyagról
///
Alapanyag* Alkoholmentes::clone() const{
    Alkoholmentes* uj = new Alkoholmentes(this->getNev(), this->getMertekegyseg(), this->getTipus());
    return uj;
}
///
/// \brief Diszítő alapanyag kiírása
///
/// A diszítő alapanyag kiírása a következő formában történik:
///     "Alapanyag neve (diszites) mennyiségmértékegység"
///
/// \param os - Output stream
///
void Diszites::alapanyagKiir(std::ostream& os) const{
    os << getNev() << " (diszites) ";
}
///
/// \brief Diszítő alapanyag kiírása fájlba
///
/// A diszítő alapanyag kiírása a következő formában történik:
///     "D;Alapanyag neve;mértékegység;mennyiseg;"
///
/// \param ofs - Output filestream
///
void Diszites::fajlbaIr(std::ofstream& ofs) const{
    ofs << "D;" << getNev() << ";" << getMertekegyseg() << ";";
}
///
/// \brief Mélymásolatot készít a diszítő alapanyagról
///
Alapanyag* Diszites::clone() const{
    Diszites* uj = new Diszites(this->getNev(), this->getMertekegyseg());
    return uj;
}