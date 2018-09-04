#include "Kolejka.h"
//----------------------------------------------------------------------------------------------------------------------
//kolejka maksymalna
Kolejka::Kolejka(int n) {
    Kopiec = new Krawedz[n];         //tablicowa implementacja kopca
    pozycja = 0;                   //pozycja w kopcu
}
Kolejka::~Kolejka() {}

Krawedz Kolejka::front() { //zwraca korzen
    return Kopiec[0];
}
void Kolejka::push(Krawedz e) { //dodawanie krawedzi i przywracanie wlasnosci kopca
    int i,j;
    i = pozycja++;                 //dolaczamy na koniec
    j = (i-1) >> 1;             //znajdowanie pozycji rodzica
    while(i && (Kopiec[j].waga > e.waga)){
        Kopiec[i] = Kopiec[j];
        i=j;
        j=(i-1) >> 1;
    }
    Kopiec[i] = e;                //dolaczenie e do kopca
}
void Kolejka::pop() { //usuwanie korzenia z kopca
    int i,j;
    Krawedz e;
    if(pozycja){
        e = Kopiec[--pozycja];
        i=0;
        j=1;
        while(j<pozycja){
            if((j+1 < pozycja) && (Kopiec[j + 1].waga < Kopiec[j].waga)){
                j++;
            }
            if(e.waga <= Kopiec[j].waga){
                break;
            }
            Kopiec[i] = Kopiec[j];
            i = j;
            j=(j<<1) + 1;
        }
        Kopiec[i] = e;
    }
}
Krawedz *Kolejka::get_Kolejka() { //getter do wskaznika na tablice z krawedziami
    return Kopiec;
}
