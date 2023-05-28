#ifndef STRING_H
#define STRING_H
/********************************************//**
 * \file string.h
 *
 * Ez a f�jl tartalmazza a
 *   - String oszt�ly deklar�ci�j�t
 *   - az inline f�ggv�nyeket.
 *
 ***********************************************/
#include <iostream>
#include "memtrace.h"


/********************************************//**
 * A String oszt�ly.
 * A 'pData'-ban vannak a karakterek (a lez�r� null�val egy�tt), 'len' a hossza.
 * A hosszba nem sz�m�t bele a lez�r� nulla.
 *
 ***********************************************/

class String {
    char *pData;        ///< pointer az adatra
    size_t len;         ///< hossz lez�r� nulla n�lk�l
public:

    /// Param�ter n�lk�li konstruktor:
    String() :pData(0), len(0) {pData = new char[len + 1]; pData[0] = '\0';}
    /// Sztring hossz�t adja vissza.
    /// @return sztring t�nyleges hossza (lez�r� nulla n�lk�l).
    size_t size() const { return len; }

    /// C-sztringet ad vissza
    /// @return pointer a t�rolt, vagy azzal azonos tartalm� null�val lez�rt sztring-re.

    char* c_str() { return pData;}

    const char* c_str() const { return pData;}

    String(const char c);

    String(const char* c);

    String(const String& s);

    ~String();

    String& operator=(const String& rhs);

    String operator+(const char c) const;

    String operator+(const String& rhs) const;

    char& operator[](size_t i) const;

    bool operator==(const String& s) const;

    bool operator!=(const String& s) const;

    bool contains(const char& c) const;

    String remove(const char& c);

    String remove(const String& s);

    String split(const char& hatar);

};

/// Glob�lis oper�torok deklar�ci�i.

    String operator+(const char c, const String& rhs);

    std::ostream& operator<<(std::ostream& os, const String& s);

    std::istream& operator>>(std::istream& is, String& s0);



#endif
