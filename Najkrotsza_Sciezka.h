#ifndef NAJKROTSZA_SCIEZKA_H
#define NAJKROTSZA_SCIEZKA_H
#include "Graf.h"
#include "Kolejka.h"
class Najkrotsza_Sciezka : public Graf{
private:
    const int MAXINT = 2147483647;  //tak wyglada nieskonczonosc
    bool * QS;                          //zbiory Q i S
    Memb ** lista;                  //tablica list sasiedztwa
    int * d;                            //tablica kosztow dojscia
    long long * D;
    int * p;                            //tablica poprzednikow
    int V,E;                            //liczba wierzcholkow i krawedzi
    int * S;                            //stos
    int * kopiec;                            //kopiec
    int * pozycjaKopca;                           //pozycja w kopcu
    int sptr = 0;                       //stack pointer
    signed int ** spMacierz;
    Krawedz * edges;
public:
    Najkrotsza_Sciezka();
    ~Najkrotsza_Sciezka();
    void zapelnij_Liste();
    void zapelnij_Macierz();
    void DijkstraLista();
    void DijkstraMacierz();
    void wyswietl_NSLista();
    void wyswietl_NSMacierz();
    void BellmanFordLista();
    void BellmanFordMacierz();
    bool cykleUjemne(int v);
    bool cykleUjemneMacierz(int v);
};
#endif
