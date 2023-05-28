#ifndef ALAPANYAG_H
#define ALAPANYAG_H
///
/// \file alapanyag.h
/// \brief Alapanyag osztályok deklarációi, inline függvényei.
///
#include "string.h"
#include "memtrace.h"
///
/// \class Alapanyag
/// \brief Alapanyag ősosztály
///
/// Alapanyag ősosztály, melynek leszármazottai az alkoholos,
/// alkoholmentes és diszítő alapanyagok.
///
class Alapanyag{
    private:
        String nev;             /**< Alapanyag neve */
        String mertekegyseg;    /**< Alapanyag mértékegysége */
    public:
///
/// \brief Alapanyag konstruktor
/// \param nev - Alapanyag neve
/// \param mertekegyseg - Alapanyag mértékegysége
///
        Alapanyag(const String& nev, const String& mertekegyseg) : nev(nev), mertekegyseg(mertekegyseg){};
///
/// \brief Név getter
/// \return Alapanyag neve
        String getNev() const { return nev; };
///
/// \brief Mértékegység getter
/// \return Alapanyag mértékegysége
///
        String getMertekegyseg() const { return mertekegyseg; };
///
/// \brief Név setter
/// \param nev - Alapanyag neve
///
        void setNev(const String& nev) { this->nev = nev; };
///
/// \brief Mértékegység setter
/// \param mertekegyseg - Alapanyag mértékegysége
///
        void setMertekegyseg(const String& mertekegyseg) { this->mertekegyseg = mertekegyseg; };
///
/// \brief Alapanyag kiírása
/// \param os - Output stream
///
        virtual void alapanyagKiir(std::ostream& os) const = 0;
///
/// \brief Alapanyag kiírása fájlba
/// \param ofs - Output filestream
///
        virtual void fajlbaIr(std::ofstream& ofs) const = 0;
///
/// \brief Mélymásolatot készít az alapanyagról
/// \return Alapanyag másolata
///
        virtual Alapanyag* clone() const = 0;
///
/// \brief Destruktor
///
        virtual ~Alapanyag() {};
};
///
/// \class Alkoholos
/// \brief Alkoholtartalmú alapanyag
class Alkoholos : public Alapanyag{
    private:
        double alkoholTartalom; /**< Alkoholtartalom százalékban */
    public:
///
/// \brief Alkoholos alapanyag konstruktor
/// \param nev - Alapanyag neve
/// \param mertekegyseg - Alapanyag mértékegysége
/// \param alkoholTartalom - Alkoholtartalom százalékban
///
        Alkoholos(const String& nev, const String& mertekegyseg, double alkoholTartalom):
            Alapanyag(nev, mertekegyseg), alkoholTartalom(alkoholTartalom) {};
///
/// \brief Alkoholtartalom getter
/// \return Alkoholtartalom százalékban
///
        double getAlkoholTartalom() const { return alkoholTartalom; }
///
/// \brief Alkoholtartalom setter
/// \param alkoholTartalom - Alkoholtartalom százalékban
///
        void setAlkoholTartalom(const double& alkoholTartalom) { this->alkoholTartalom = alkoholTartalom; }
///
        void alapanyagKiir(std::ostream& os) const;
///
        void fajlbaIr(std::ofstream& ofs) const;
///
/// \brief Mélymásolatot készít az alkoholos alapanyagról
/// \return Alkoholos alapanyag másolata
///
        Alapanyag* clone() const;
///
/// \brief Destruktor
///
        ~Alkoholos() {};
};
///
/// \class Alkoholmentes
/// \brief Alkoholmentes alapanyag
///
class Alkoholmentes : public Alapanyag{
    private:
        String tipus;           /**< Alkoholmentes alapanyag típusa */
    public:
///
/// \brief Alkoholmentes alapanyag konstruktor
/// \param nev - Alapanyag neve
/// \param mertekegyseg - Alapanyag mértékegysége
/// \param tipus - Alkoholmentes alapanyag típusa
        Alkoholmentes(const String& nev, const String& mertekegyseg, const String& tipus):
            Alapanyag(nev, mertekegyseg), tipus(tipus) {};
///
/// \brief Típus getter
/// \return Alkoholmentes alapanyag típusa
///
        String getTipus() const { return tipus; }
///
/// \brief Típus setter
/// \param tipus - Alkoholmentes alapanyag típusa
///
        void setTipus(const String& tipus) { this->tipus = tipus; };
///
        void alapanyagKiir(std::ostream& os) const;
///
        void fajlbaIr(std::ofstream& ofs) const;
///
/// \brief Mélymásolatot készít az alkoholmentes alapanyagról
/// \return Alkoholmentes alapanyag másolata
///
        Alapanyag* clone() const;
///
/// \brief Destruktor
///
        ~Alkoholmentes() {};
};

///
/// \class Diszites
/// \brief Diszítő alapanyag (pl. citromkarika, jégkocka)
///
class Diszites : public Alapanyag{
    public:
///
/// \brief Diszítő alapanyag konstruktor
/// \param nev - Alapanyag neve
/// \param mertekegyseg - Alapanyag mértékegysége
///
        Diszites(const String& nev, const String& mertekegyseg):
            Alapanyag(nev, mertekegyseg){};
///
        void alapanyagKiir(std::ostream& os) const;
///
        void fajlbaIr(std::ofstream& ofs) const;
///
/// \brief Mélymásolatot készít a diszítő alapanyagról
/// \return Diszítő alapanyag másolata
///
        Alapanyag* clone() const;
///
/// \brief Destruktor
///
        ~Diszites() {};
};
#endif // ALAPANYAG_H
