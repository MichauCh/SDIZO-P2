#include <iomanip>
#include "MST.h"
MST::MST(int n) { //inicjalizacja pustych list sasiedztwa
    listaSasiedztwa = new Memb * [n];
    for(int i = 0;i<n;i++){
        listaSasiedztwa[i] = NULL;
    }
    dlugoscListy = n-1;
    waga = 0;
    V = n;
    E = (V-1);
}
MST::MST(){
    waga = 0;
}
MST::~MST() {
    int i;
    Memb *p,*r;
    for(i = 0; i <= dlugoscListy; i++)
    {
        p = listaSasiedztwa[i];
        while(p)
        {
            r = p;
            p = p->next;                // przechodzenie po kolejnych elementach
            delete r;                   // i usuwanie kolejnych elementow
        }
    }
    delete [] listaSasiedztwa;                    // usuwamy wszystkie tablice
    delete [] visited;
    delete [] macierzMST;
    delete [] macierzIncydencji;

}
//----------------------------------------------------------------------------------------------------------------------
//dodawanie krawedzi
void MST::dodajKrawedz(Krawedz e) {
    Memb * p;
    waga += e.waga;                 //do wagi drzewa dodajemy wage krawedzi
    p = new Memb;                //tworzymy nowy wezel
    p->v = e.v2;                        //wierzcholek koncowy
    p->waga = e.waga;               //waga krawedzi
    p->next = listaSasiedztwa[e.v1];   //dodajemy p do listy wierzcholka v1
    listaSasiedztwa[e.v1] = p;
    p = new Memb;                // To samo dla krawędzi odwrotnej
    p->v = e.v1;                        // Wierzchołek końcowy
    p->waga = e.waga;               //waga krawedzi
    p->next = listaSasiedztwa[e.v2];   //dodajemy p do listy wierzcholka v2
    listaSasiedztwa[e.v2] = p;
}
//----------------------------------------------------------------------------------------------------------------------
//dodawanie krawedzi do grafu w postaci macierzy
void MST::dodajKrawedzMacierz(Krawedz e) {
    waga += e.waga;
    macierzMST[e.v1][tmpCounter] = e.waga;
    macierzMST[e.v2][tmpCounter] = -1;
    tmpCounter++;
}
//----------------------------------------------------------------------------------------------------------------------
//Zapelnianie listy
void MST::zapelnij_Liste() {
    this->waga = 0;
    dlugoscListy = getV() - 1;
    V = getV();
    E = getE();
    edges = get_Krawedzie();
    listaSasiedztwa = new Memb * [V];
    for(int i = 0;i<V;i++){
        listaSasiedztwa[i] = NULL;
    }
}
//----------------------------------------------------------------------------------------------------------------------
//zapelnianie macierzy
void MST::zapelnij_Macierz() {
    tmpCounter=0;
    waga = 0;
    this->macierzIncydencji = get_macierzIncydencji();
    V = getV();
    E = getE();
    edges = get_Krawedzie();
    macierzMST = new signed int * [V];                    //tworzymy wierzcholki
    for(int i = 0;i<V;i++){
        macierzMST[i] = new signed int[V-1];                //tworzymy krawedzie (liczba wierzcholkow-1)
    }
    for(int i =0;i<V;i++){
        for(int j =0;j<V-1;j++){
            macierzMST[i][j]=0;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
//wyswietlanie listy
void MST::wyswietl_MSTListe() { //wyswietla drzewo w formie lsity
    if(dlugoscListy == 0)
        std::cout<<"pusta lista\n";
    else {
        Memb *p;
        std::cout << "\n";
        for (int i = 0; i <= dlugoscListy; i++) {
            std::cout << "Wierzcholek: " << i << " - ";
            for (p = listaSasiedztwa[i]; p; p = p->next) {
                std::cout << "do wierzcholka: " << p->v << " z waga: " << p->waga << "; ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n" << "Waga minimalnego drzewa spinajacego = " << waga << "\n\n";
    }
}
//----------------------------------------------------------------------------------------------------------------------
//Kruskal na reprezentacji listowej
void MST::Kruskal_Lista() {
    dlugoscListy = V-1;
    DSStruct Z(V);                       // struktura zbiorow rozlacznych
    Kolejka Q(E);                          // kolejka priorytetowa na kopcu maksymalnym
    for(int i =0;i<V;i++){
        Z.MakeSet(i);                    // wszystkie wierzcholki maja wlasne zbiory
    }
    for(int i =0;i<E;i++){
        Q.push(edges[i]);                   // bierzemy kolejne krawedzie grafu i umieszczamy je w kolejce
    }
    Krawedz e;
    for(int i = 1;i<V;i++){                 //n-1 razy
        do{
            e = Q.front();                  // wyciagamy pierwsza krawedz z kolejki i usuwamy
            Q.pop();
        } while(Z.FindSet(e.v1) == Z.FindSet(e.v2));
        dodajKrawedz(e);                   // dodawanie krawedzi do drzewa wynikowego
        Z.UnionSets(e);                     // laczenie zbiorow
    }
}
//----------------------------------------------------------------------------------------------------------------------
//Kruskal na reprezentacji macierzowej
void MST::Kruskal_Macierz() {

    DSStruct Z(V);                       // zbiory rozlaczne
    Kolejka Q(E);                          //kolejka oparta na kopcu
    for(int i =0;i<V;i++){
        Z.MakeSet(i);                    //kazdy wierzcholek ma wlasny zbior
    }
    for(int i =0;i<E;i++){

        Q.push(edges[i]);                   // krawedzie -> kolejka
    }

    Krawedz e;
    for(int i = 1;i<V;i++){                 //n-1 razy
        do{
            e = Q.front();                  //wyciagamy pierwsza krawedz z kolejki i usuwamy
            Q.pop();
        } while(Z.FindSet(e.v1) == Z.FindSet(e.v2));
        dodajKrawedzMacierz(e);                   // dodawanie krwaedzi do drzewa wynikowego
        Z.UnionSets(e);                     // laczenie zbiorow
    }
}
//----------------------------------------------------------------------------------------------------------------------
//wyswietlanie macierzy
void MST::wyswietl_MSTMacierz() {
    if(!macierzMST)
        std::cout<<"pusta macierz\n";
    else {
        //wyswietlenie wczytanego grafu
        for (int i = 0; i < V - 1; i++) std::cout << std::setw(3) << i;
        std::cout << "\n\n";
        for (int i = 0; i < V; i++) {
            std::cout << std::setw(3) << i;
            for (int j = 0; j < V - 1; j++) {
                std::cout << std::setw(3) << (int) macierzMST[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "Waga minimalnego drzewa rozpinajacego: " << waga << "\n";
    }
}
//----------------------------------------------------------------------------------------------------------------------
//Prim na reprezentacji listowej
void MST::Prim_Lista() {
    Krawedz tmpE;
    Memb *p;
    Kolejka * Q = new Kolejka(E);      //kolejka priorytetowa oparta na kopcu
    visited = new bool[V];

    for(int i =0;i<V;i++){
        visited[i] = false;
    }
    G = new MST(V);                       //graf
    for(int i =0;i<E;i++){
        G->dodajKrawedz(this->edges[i]);
    }
    int v = 0;                      //wierzcholek startowy
    visited[v]=true;
    for(int i =1;i<V;i++){
        for(p=G->listaSasiedztwa[v];p;p=p->next){
            if (!visited[p->v]) {
                tmpE.v1 = v;
                tmpE.v2 = p->v;
                tmpE.waga = p->waga;
                Q->push(tmpE);
            }
        }
            do{
                tmpE = Q->front();          //pobieramy krawedz z kolejki priorytetowej
                Q->pop();
            } while(visited[tmpE.v2]);
        dodajKrawedz(tmpE);
            visited[tmpE.v2] = true;
            v = tmpE.v2;
    }
    delete [] visited;
    delete Q;
}
//----------------------------------------------------------------------------------------------------------------------
//Prim na reprezentacji macierzowej
void MST::Prim_Macierz() {
    Krawedz tmpE;
    Kolejka * Q = new Kolejka(E);
    visited = new bool[V];
    for(int i =0;i<V;i++){
        visited[i] = false;
    }
    int v = 0;                      //wierzcholek startowy
    visited[v]=true;
    for (int i = 1; i < V; i++)
    {
       for (int j = 0; j < V; j++)
           if (macierzIncydencji[j][v] != 0 && !visited[j])
                    {
                        tmpE.v1 = v;
                        tmpE.v2 = j;
                        tmpE.waga = macierzIncydencji[j][v];
                        Q->push(tmpE);
                    }
        do
        {
            tmpE = Q->front();
            Q -> pop();
        } while (visited[tmpE.v2]);
        dodajKrawedzMacierz(tmpE);
        visited[tmpE.v2] = true;
        v = tmpE.v2;
    }
    delete Q;
    delete [] visited;
}
