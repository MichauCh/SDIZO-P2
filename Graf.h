#ifndef GRAF_H
#define GRAF_H
#include <string>
#include <fstream>
#include <iostream>
#include "Krawedz.h"
#include <cmath>
class Graf{
private:
    std::ifstream file;
    int V,E;                //wierzcholki i krawedzie
    signed int ** macierzIndcydencji;
    Krawedz * krawedzie;
    Memb ** lista;
    Memb * tempMemb;
    Graf * graf;
    int maxK;
    double minG;
public:
    int vStartowy, vKoncowy;  //wierzcholek poczatkowy i koncowy do wyszukiwania sciezki
    Graf();
    virtual ~Graf();
    bool wczytaj_z_pliku_skierowany(std::string filename);
	bool wczytaj_z_pliku_nieskierowany(std::string filename);
    void wyswietl_Macierz_Incydencji();
    void wyswietl_Liste_Sasiedztwa();
    bool graf_Losowy(int wierzcholki, float gestosc);
//gettery
    int getV();
    int getE();
    Krawedz * get_Krawedzie();
    Memb ** get_listaSasiedztwa();
    signed int ** get_macierzIncydencji();
};
#endif
