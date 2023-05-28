#ifndef TAROLOK_H
#define TAROLOK_H
///
/// \file tarolok.h
/// \brief Tároló osztályok deklarációi, inline függvényei.
///
#include "string.h"
#include "alapanyag.h"
///
/// \class Recept
/// \brief Recept osztály
///
class Recept{
    private:
        String nev;             /**< Recept neve */
        Alapanyag** pData;      /**< Ősosztály pointerek tömbje */
        double* mennyisegek;    /**< Mennyiségek tömbje */
        size_t meret;           /**< Tömb mérete */
/// Másoló konstruktor és értékadás operátor privát, így nem lehet másolni
        Recept(const Recept& r);
        Recept& operator=(const Recept& r);
    public:
///
/// \brief Recept konstruktor
///
/// Létrehoz egy receptet, amelynek a neve alapértelmezetten üres string.
/// \param nev - Recept neve
///
        Recept(const String&  nev = ""): nev(nev), pData(NULL), mennyisegek(NULL), meret(0) {};
///
/// \brief Név setter
/// \param nev - Recept neve
///
        void setNev(const String& nev) { this->nev = nev; };
///
/// \brief Név getter
/// \return Recept neve
///
        String getNev() const { return nev; };
        void hozzaad(Alapanyag* alapanyag, double mennyiseg);
        void kiir(std::ostream& os) const;
///
/// \brief Méret getter
/// \return Recept mérete
///
        size_t size() const { return meret; };
///
/// \brief Indexelő operátor
/// \param idx - Index
/// \return Pointer az idx-edik alapanyagra
///
        Alapanyag* operator[](const size_t& idx) const { return pData[idx]; };
///
/// \brief Mennyiségek getter
/// \return Mennyiségek tömbje
///
        double* getMennyisegek() const { return mennyisegek; };
        void clear();
        ~Recept();
};
///
/// \class ReceptTarolo
/// \brief Receptek tárolására szolgáló osztály
///
class ReceptTarolo{
    private:
        Recept** receptek;         /**< Receptek pointereinek tömbje */
        size_t meret;           /**< Tömb mérete */
/// Másoló konstruktor és értékadás operátor privát, így nem lehet másolni        
        ReceptTarolo(const ReceptTarolo& rt);
        ReceptTarolo& operator=(const ReceptTarolo& rt);
    public:
///
/// \brief ReceptTarolo konstruktor
///
/// Létrehoz egy üres tárolót, 0 mérettel.
///
        ReceptTarolo(): receptek(NULL), meret(0) {};
        void hozzaad(Recept* recept);
        void torol(const size_t& idx);
        void kiir(std::ostream& os) const;
///
/// \brief Méret getter
/// \return Recepttároló mérete
///
        size_t size() const { return meret; };
///
/// \brief Indexelő operátor
/// \param idx - Index
/// \return Pointer az idx-edik receptre
///
        Recept* operator[](const size_t& idx) const { return receptek[idx]; };
        ~ReceptTarolo();
};

///
/// \class AlapanyagTarolo
/// \brief Alapanyagok tárolására szolgáló osztály.
///
/// Annyiban különböző a recept osztálytól, hogy
/// a receptkönyv összes alapanyagából tárol egyet-egyet.
///
class AlapanyagTarolo{
    private:
        Alapanyag** pData;      /**< Ősosztály pointerek tömbje */
        size_t meret;           /**< Tömb mérete */
    public:
///
/// \brief AlapanyagTarolo konstruktor
///
        AlapanyagTarolo(): pData(NULL), meret(0) {};
        void hozzaad(Alapanyag* alapanyag);
        void kiir(std::ostream& os) const;
///
/// \brief Méret getter
/// \return Alapanyagtároló mérete
///
        size_t size() const { return meret; };
///
/// \brief Indexelő operátor
/// \param idx - Index
/// \return Pointer az index-edik alapanyagra
        Alapanyag* operator[](const size_t& idx) const { return pData[idx]; };
        ~AlapanyagTarolo() ;
};

#endif // TAROLOK_H
