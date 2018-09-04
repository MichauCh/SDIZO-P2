#ifndef MST_H
#define MST_H
#include <string>
#include "Graf.h"
#include <iostream>
#include "Kolejka.h"
#include "DSStruct.h"

class MST : public Graf{
private:
    Memb ** listaSasiedztwa;           //tablica list sasiedztwa
    int dlugoscListy;             //liczba komorek w tablicy  v-1
    int waga;                             //waga calego drzewa (mst)
    int V, E;                                   //liczba wierzcholkow i krawedzi
    Krawedz * edges;                        //krawedzie
    signed int ** macierzIncydencji;
    signed int ** macierzMST;
    bool * visited;     //odwiedzone
    MST *G;
    int tmpCounter;
public:
    MST(int n);
    MST();
    ~MST();
    void dodajKrawedz(Krawedz e);
    void dodajKrawedzMacierz(Krawedz e);
    void zapelnij_Liste();
    void zapelnij_Macierz();
    void wyswietl_MSTListe();
    void wyswietl_MSTMacierz();
    void Kruskal_Lista();
    void Kruskal_Macierz();
    void Prim_Lista();
    void Prim_Macierz();
    //Memb * get_Lista_Sasiedztwa(int n);
};
#endif