#ifndef KOLEJKA_H
#define KOLEJKA_H
#include "Krawedz.h"
class Kolejka {                   //kolejka priorytetowa w formie kopca w formie tablicy
private:
    Krawedz * Kopiec;
    int pozycja;
public:
    Kolejka(int n);
    ~Kolejka();
    Krawedz front(); //korzen
    void push(Krawedz e); //dodawanie
    void pop(); //usuwanie
    Krawedz * get_Kolejka();
};
#endif
