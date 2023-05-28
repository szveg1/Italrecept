///
/// \file tesztek.cpp
/// \brief Ez a fájl tartalmazza a teszteket.
///
/// A tesztek a gtest_lite.h segítségével készültek.
///
#include "gtest_lite.h"
#include "string.h"
#include "alapanyag.h"
#include "tarolok.h"
#include "receptkonyv.h"
#include "memtrace.h"

void test(){

    TEST(Alapanyagok, tagfuggvenyek){
//  tagváltozók ellenőrzése
        Alapanyag *a = new Alkoholos("Abszint", "dl", 70);
        EXPECT_STREQ("Abszint", a->getNev().c_str());
        EXPECT_STREQ("dl", a->getMertekegyseg().c_str());
        Alapanyag *m = new Alkoholmentes("Szodaviz", "dl", "udito");
        EXPECT_STREQ("Szodaviz", m->getNev().c_str());
        EXPECT_STREQ("dl", m->getMertekegyseg().c_str());
        Alapanyag *d = new Diszites("Citrom", "db");
        EXPECT_STREQ("Citrom", d->getNev().c_str());
        EXPECT_STREQ("db", d->getMertekegyseg().c_str());
//  kiírás ellenőrzése
        std::stringstream ss;
        a->alapanyagKiir(ss);
        EXPECT_STREQ("Abszint (alkohol 70%) ", ss.str().c_str());
        ss.str("");
        m->alapanyagKiir(ss);
        EXPECT_STREQ("Szodaviz (udito) ", ss.str().c_str());
        ss.str("");
        d->alapanyagKiir(ss);
        EXPECT_STREQ("Citrom (diszites) ", ss.str().c_str());
        ss.str("");
//  klónozás ellenőrzése
        Alapanyag *ac = a->clone();
        EXPECT_STREQ("Abszint", ac->getNev().c_str());
        EXPECT_STREQ("dl", ac->getMertekegyseg().c_str());
        Alapanyag *mc = m->clone();
        EXPECT_STREQ("Szodaviz", mc->getNev().c_str());
        EXPECT_STREQ("dl", mc->getMertekegyseg().c_str());
        Alapanyag *dc = d->clone();
        EXPECT_STREQ("Citrom", dc->getNev().c_str());
        EXPECT_STREQ("db", dc->getMertekegyseg().c_str());

        delete a;
        delete ac;
        delete m;
        delete mc;
        delete d;
        delete dc;
    }END;

    TEST(Recept, tagfuggvenyek){
        Recept r;
//  default komstruktor ellenőrzése
        EXPECT_STREQ("", r.getNev().c_str());
        EXPECT_EQ(0, (int)r.size());
//  nev setter ellenorzese
        r.setNev("Teszt");
        EXPECT_STREQ("Teszt", r.getNev().c_str());
//  hozzaad ellenorzese
        Alapanyag *a = new Alkoholos("Abszint", "dl", 70);
        Alapanyag *m = new Alkoholmentes("Szodaviz", "dl", "udito");
        Alapanyag *d = new Diszites("Citrom", "db");
        Alapanyag *ac = a->clone();
        r.hozzaad(a, 2);
        r.hozzaad(m, 3);
        r.hozzaad(d, 4);
        EXPECT_EQ(3, (int)r.size());
//  hozzaad ellenorzese, ha mar szerepel azonos nevu alapanyag a receptben
        EXPECT_THROW(r.hozzaad(ac, 2), const char*);
//  kiir ellenorzese
        std::stringstream ss;
        r.kiir(ss);
        EXPECT_STREQ("\nTeszt\n-----\nAbszint (alkohol 70%)  2dl\n"
                    "Szodaviz (udito)  3dl\nCitrom (diszites)  4db\n",
                    ss.str().c_str());
        ss.str("");        
//  indexelő operátor ellenorzese
        Alapanyag *idx = r[0];
        EXPECT_STREQ("Abszint", idx->getNev().c_str());
        EXPECT_STREQ("dl", idx->getMertekegyseg().c_str());
//  mennyisegek getter ellenorzese
        double *mennyisegek = r.getMennyisegek();
        EXPECT_DOUBLE_EQ(2.0, mennyisegek[0]);
        EXPECT_DOUBLE_EQ(3.0, mennyisegek[1]);
        EXPECT_DOUBLE_EQ(4.0, mennyisegek[2]);
//  clear ellenorzese
        r.clear();
        EXPECT_EQ(0, (int)r.size());
    }END;

    TEST(ReceptTarolo, tagfuggvenyek){
        ReceptTarolo rt;
//  default konstruktor ellenorzese
        EXPECT_EQ(0, (int)rt.size());
//  hozzaad ellenorzese
        Recept *r = new Recept("Teszt");
        Alapanyag *a = new Alkoholos("Abszint", "dl", 70);
        Alapanyag *m = new Alkoholmentes("Szodaviz", "dl", "udito");
        Alapanyag *d = new Diszites("Citrom", "db");
        r->hozzaad(a, 2);
        r->hozzaad(m, 3);
        r->hozzaad(d, 4);
        rt.hozzaad(r);
        EXPECT_EQ(1, (int)rt.size());
        Recept *rc = new Recept("Teszt");
        EXPECT_THROW(rt.hozzaad(rc), const char*);
//  indexelő operátor ellenorzese
        Recept *idx = rt[0];
        EXPECT_STREQ("Teszt", idx->getNev().c_str());
//  kiírás ellenorzese
        std::stringstream ss;
        rt.kiir(ss);
        EXPECT_STREQ("\nTeszt\n-----\nAbszint (alkohol 70%)  2dl\n"
                    "Szodaviz (udito)  3dl\nCitrom (diszites)  4db\n\n", 
                    ss.str().c_str());

        rt.torol(0);
        EXPECT_EQ(0, (int)rt.size());
    }END;

    TEST(Receptkonyv, helyes formatum){
        Receptkonyv rk;
        std::stringstream be, ki;
        rk.fajlbolOlvas("teszt1.dat",ki);
        be.str("1");
//      receptek kiírása
        rk.receptekKiir(be, ki);
        EXPECT_STREQ(   "1 db recept beolvasva.\n"
                        "\nReceptek:\n"
                        "---------\n"
                        "[1] Tequila Sunrise\n"
                        "[2] Vissza\n"
                        "\n"
                        "Valasszon receptet: \n"
                        "Tequila Sunrise\n"
                        "---------------\n"
                        "Tequila (alkohol 37.5%)  4.5cl\n"
                        "Grenadine (szirup)  1.5cl\n"
                        "Narancsle (gyumolcsle)  9cl\n",
                     ki.str().c_str());
        ki.str("");
//      alapanyagok kiírása
        rk.alapanyagokKiir(ki);
        EXPECT_STREQ(   "\nAlapanyagok:\n"
                        "------------\n"
                        "[0] Tequila (alkohol 37.5%) (cl)\n"
                        "[1] Grenadine (szirup) (cl)\n"
                        "[2] Narancsle (gyumolcsle) (cl)\n"
                        "\n",
                     ki.str().c_str());
        ki.str("");

        
    }END;

    TEST(Receptkonyv, helytelen formatum){
        Receptkonyv rk;
        EXPECT_THROW(rk.fajlbolOlvas("teszt2.dat"), const char*);
    }END;

    TEST(Receptkonyv, nem letezo fajl){
        Receptkonyv rk;
        EXPECT_THROW(rk.fajlbolOlvas("teszt3.dat"), std::ifstream::failure& f);
    }END;

    TEST(Receptkonyv, bemenet kezeles){
        std::stringstream ki;
        std::stringstream be;
        int valasz;
        be.putback(-1);
//      EOF-re throwolnia kell
        EXPECT_THROW(bemenetKezel(be, ki, "Teszt: ", valasz), const char*);
    }END;
}
