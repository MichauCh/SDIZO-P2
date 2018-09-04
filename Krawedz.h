#ifndef KRAWEDZ_H
#define KRAWEDZ_H
//Definicja obiektu kolejki priorytetowej
struct Krawedz{
    int v1,v2,waga;   //wierzcholki krawedzi, waga krawedzi
};
struct Memb{
    Memb * next;    //wskaznik na nastepny element
    int v,waga; //wartosc, waga
};
#endif
