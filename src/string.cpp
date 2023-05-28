/********************************************//**
 *
 * \file string.cpp
 *
 * Ötödik laboron elkészített string osztály
 *
 ***********************************************/
#ifdef _MSC_VER
// MSC ne adjon figyelmeztetõ üzenetet a C sztringkezelõ függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringmûveletekhez

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string.h"


/// Konstruktorok: egy char karakterbõl (createString)
///                egy nullával lezárt char sorozatból (createString)

    String::String(char c){
        len = 1;
        pData = new char[len + 1];
        pData[0] = c;
        pData[1] = '\0';
    }

    String::String(const char* c){
        len = strlen(c);
        pData = new char[len + 1];
        strcpy(pData, c);
        pData[len] = '\0';
    }
/// Másoló konstruktor: String-bõl készít (createString)
    String::String(const String& s){
        len = s.size();
        pData = new char[len + 1];
        strcpy(pData, s.c_str());
    }
/// Destruktor (disposeString)
    String::~String(){
        delete[] pData;
    }

/// operator=
    String& String::operator=(const String& rhs){
        if(pData == rhs.pData)
            return *this;
        delete[] pData;

        len = rhs.size();
        pData = new char[len + 1];
        for(size_t i = 0; i < len ; i++){
            pData[i] = rhs.pData[i];
        }
        pData[len] = '\0';
        return *this;
    }
/// [] operátorok: egy megadott indexû elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!
        char& String::operator[](size_t i) const{
            if(i >= len)
                throw "QUMFKD";
            return pData[i];
        }

/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
///                 String-hez String-et ad (addString)
    String String::operator+(const char c) const{
        char *tmp = new char[this->len + 2];
        strcpy(tmp, this->pData);
        String s0(c);
        strcat(tmp, s0.pData);
        String s(tmp);
        delete[] tmp;
        return s;
    }
    String String::operator+(const String& rhs) const{
        char *tmp = new char[this->size() + rhs.size() + 1];
        strcpy(tmp, this->pData);
        strcat(tmp, rhs.pData);
        String s(tmp);
        delete[] tmp;
        return s;
    }

    String operator+(const char c, const String& rhs) {
        char *tmp = new char[rhs.size() + 2];
        String s0(c);
        strcpy(tmp, s0.c_str());
        strcat(tmp, rhs.c_str());
        String s(tmp);
        delete[] tmp;
        return s;
    }

/********************************************//**
 * \brief Egyenlőség operátor
 *
 * \param[in] rhs
 * \return Megegyezik-e a két string tartalma
 *
 ***********************************************/
    bool String::operator==(const String& rhs) const{
        if(strcasecmp(this->pData, rhs.pData) == 0)
            return true;
        return false;
    }

/********************************************//**
 * \brief Nem-egyenlőség operátor
 *
 * \param[in] rhs
 * \return Különböző-e a két string tartalma
 *
 ***********************************************/
    bool String::operator!=(const String& rhs) const{
        if(strcasecmp(this->pData, rhs.pData) != 0)
            return true;
        return false;
    }

/********************************************//**
 * \brief Karakter kereső logikai függvény
 *
 * \param[in] c - keresett karakter
 * \return Tartalmazza-e a megadott karaktert
 *
 ***********************************************/
    bool String::contains(const char& c) const{
        for(size_t i = 0; i < this->size(); i++){
            if(pData[i] == c)
                return true;
        }
        return false;
    }

/********************************************//**
 * \brief Megadott karaktereket eltávolító függvény
 *
 * \param[in] c - eltávolítani kívánt karakter
 * \return Új string a nemkívánatos karakterek nélkül
 *
 ***********************************************/
    String String::remove(const char& c){
        if(!this->contains(c))
            return *this;
        String uj;
        for(size_t i = 0; i < this->size(); i++){
            if(this->pData[i] != c)
                uj = uj + pData[i];
        }
        return uj;
    }


/********************************************//**
 * \brief String tokenesítő függvény
 *
 *  strtok implementáció saját string osztályra
 *
 * \param[in] hatar - határoló karakter
 * \return új string ami a határig tart
 *
 ***********************************************/
    String String::split(const char& hatar){
//  uj-ba a határoló karakter utáni, eredmeny-be
//  pedig az előtte levő tartalom kerül
        String uj, eredmeny;
        size_t i = 0;
//  megnézzük nem üres-e a string
        if(*this != "")
            uj = *this;
//  lezáró nulláig megyünk
        while(this->pData[i] != '\0'){
//  ha nem a határoló karaktert értük el,
//  akkor az éppen vizsgált karaktert hozzáadjuk az új stringhez
            if(this->pData[i] != hatar)
                eredmeny = eredmeny + this->pData[i];
//  this-be átkerül a határoló karakter utáni tartalom
            else{
                uj = this->pData + i + 1;
                *this = uj;
                return eredmeny;
            }
//  ciklusszámlálót növeljük
            i++;
        }

        return uj;
    }

/// << operator, ami kiír az ostream-re
    std::ostream& operator<<(std::ostream& os, const String& s){
        return os << s.c_str();
    }

/// >> operátor, ami beolvas az istream-rõl egy sort
    std::istream& operator>>(std::istream& is, String& s){
        char ch;
        s = String("");            // üres string, ehhez fûzünk hozzá
        std::ios_base::fmtflags fl = is.flags(); // eltesszük a régi flag-eket
        is.setf(std::ios_base::skipws);			// az elején eldobjuk a ws-t
        while (is >> ch) {
            is.unsetf(std::ios_base::skipws);	// utána pedig már nem
            if (ch == '\n') {
                is.putback(ch);             // na ezt nem kérjük
                break;
            } else {
                s = s + ch;               // végére fûzzük a karaktert
        }
        }
        is.setf(fl);						// visszaállítjuk a flag-eket
        return is;
    }
