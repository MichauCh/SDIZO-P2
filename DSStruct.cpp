#include "DSStruct.h"

DSStruct::DSStruct(int n) {
    Z = new DSNode [n];                 //Tworzymy tablice dla elementow zbiorow
}

DSStruct::~DSStruct() {
    delete [] Z;
}

//tworzymy wpis z tablicy Z
void DSStruct::MakeSet(int v) {
    Z[v].up = v;
    Z[v].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w którym jest wierzchołek v
int DSStruct::FindSet(int v) {
    if(Z[v].up != v){
        Z[v].up = FindSet(Z[v].up);
    }
    return Z[v].up;
}

// Łączy ze sobą zbiory z v i u
void DSStruct::UnionSets(Krawedz e) {
    int ru, rv;
    ru = FindSet(e.v1);                     //wyznaczamy korzen drzewa z wezlem u
    rv = FindSet(e.v2);                     //wyznaczamy korzen drzewa z wezlem v

    if(ru!=rv){
        if(Z[ru].rank > Z[rv].rank){        // Porównujemy rangi drzew
            Z[rv].up = ru;                  // ru większe, dołączamy rv
        } else {
            Z[ru].up = rv;                  // równe lub rv większe, dołączamy ru
            if(Z[ru].rank == Z[rv].rank){
                Z[rv].rank++;
            }
        }
    }
}
