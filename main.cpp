#include <iostream>
#include "MST.h"
#include "Najkrotsza_Sciezka.h"
#include <windows.h>
using namespace std;

void wyborAlgorytmow(int algorytmy);
void menu_mst();
void menu_NS();
void czasStart();
void pobierzCzas();
MST * wynik_mst;
Najkrotsza_Sciezka * sciezka;
double PCFreq = 0.0;
__int64 licznik = 0;

int main() {
    char option;
    do{
        cout << "\n1. Wyznaczanie minimalnego drzewa rozpinajacego (MST) \n";
        cout << "2. Wyznaczanie najkrotszej sciezki w grafie \n";
        cout << "0. Wyjscie \n";
        cout << "Wybierz co chcesz zrobic: ";
        cin >> option;
        cout << "\n";
        switch (option){
            case '1':
                menu_mst();
                break;
            case '2':
                menu_NS();
                break;
            case '3':
                break;
            case '4':
                break;
        }

    } while (option != '0');
    return 0;
}
void wyborAlgorytmow(int algorytmy){
    if(algorytmy == 1){
        cout << "Minimalne drzewo rozpinajace (MST) \n";
        cout << "1. Wczytaj graf z pliku \n ";
        cout << "2. Wygeneruj graf losowo \n ";
        cout << "3. Wyswietl graf \n ";
        cout << "4. Algorytm Prima na macierzy \n";
        cout << "5. Algorytm Prima na liscie \n";
        cout << "6. Algorytm Kruskala na macierzy \n";
        cout << "7. Algorytm Kruskala na liscie \n";
        cout << "0. Wroc \n";
        cout << "Wybierz co chcesz zrobic: ";

    } else if(algorytmy == 2){
        cout << "Wyznaczanie najkrotszej sciezki \n";
        cout << "1. Wczytaj graf z pliku \n";
        cout << "2. Wygeneruj graf losowo \n";
        cout << "3. Wyswietl reprezentacje listowa i macierzowa \n";
        cout << "4. Algorytm Dijkstry na macierzy \n";
        cout << "5. Algorytm Dijkstry na liscie \n";
        cout << "6. Algorytm Bellmana-Forda na macierzy \n";
        cout << "7. Algorytm Bellmana-Forda na liscie \n";
        cout << "0. Wroc \n";
        cout << "Wybierz co chcesz zrobic: ";
    } else if(algorytmy == 3){
    }
}
void menu_mst(){
    char opt;
    do{
        wyborAlgorytmow(1);
        cin >> opt;
        cout << "\n";
        switch( opt ){
            case '1':{
                wynik_mst = new MST();
                cout << "Podaj nazwe pliku z rozszerzeniem: ";
                string filename;
                cin >> filename;
                wynik_mst->wczytaj_z_pliku_nieskierowany(filename);
                wynik_mst->wyswietl_Macierz_Incydencji();
                wynik_mst->wyswietl_Liste_Sasiedztwa();
            }break;
            case '2':{
                wynik_mst = new MST();
                cout << "Podaj ilosc wierzcholkow grafu: ";
                int v;
                cin >> v;
                cout << "Podaj gestoc grafu jako ulamek (0-1): ";
                double d;
                cin >> d;
                if(d >= 0 && d <=1){
                    wynik_mst->graf_Losowy(v, d);
                } else {
                    cout << "bledna wartosc \n";
                }
            }break;
            case '3':{
                wynik_mst->wyswietl_Liste_Sasiedztwa();
                wynik_mst->wyswietl_Macierz_Incydencji();
            }break;
            case '4':{
                wynik_mst->zapelnij_Macierz();
                czasStart();
                wynik_mst->Prim_Macierz();
                pobierzCzas();
                wynik_mst->wyswietl_MSTMacierz();
            }break;
            case '5': {
                wynik_mst->zapelnij_Liste();
                czasStart();
                wynik_mst->Prim_Lista();
                pobierzCzas();
                wynik_mst->wyswietl_MSTListe();
            } break;
            case '6': {
                wynik_mst->zapelnij_Macierz();
                czasStart();
                wynik_mst->Kruskal_Macierz();
                pobierzCzas();
                wynik_mst->wyswietl_MSTMacierz();
            } break;
            case '7': {
                wynik_mst->zapelnij_Liste();
                czasStart();
                wynik_mst->Kruskal_Lista();
                pobierzCzas();
                wynik_mst->wyswietl_MSTListe();
            } break;
        }
    } while (opt!='0');
}
void menu_NS(){
    char opt;
    do{
        wyborAlgorytmow(2);
        cin >> opt;
        cout << "\n";
        switch( opt ){
            case '1':{
                sciezka = new Najkrotsza_Sciezka();
                cout << "Podaj nazwe pliku z rozszerzeniem: ";
                string filename;
                cin >> filename;
                sciezka->wczytaj_z_pliku_skierowany(filename);
                sciezka->wyswietl_Macierz_Incydencji();
                sciezka->wyswietl_Liste_Sasiedztwa();
            }break;
            case '2':{
                sciezka = new Najkrotsza_Sciezka();
                cout << "Podaj ilosc wierzcholkow grafu: ";
                int v;
                cin >> v;
                cout << "Podaj gestoc grafu jako ulamek (0-1): ";
                double d;
                cin >> d;
                if(d >= 0 && d <=1){
                    sciezka->graf_Losowy(v, d);
                } else {
                    cout << "bledna wartosc \n";
                }
            }break;
            case '3':{
                sciezka->wyswietl_Macierz_Incydencji();
                sciezka->wyswietl_Liste_Sasiedztwa();
            }break;
            case '4':{
                cout << "Algorytm Dijkstry na reprezentacji macierzowej \n";
                sciezka->zapelnij_Macierz();
                czasStart();
                sciezka->DijkstraMacierz();
                pobierzCzas();
            }break;
            case '5': {
                cout << "Algorytm Dijkstry na reprezentacji listowej \n";
                sciezka->zapelnij_Liste();
                czasStart();
                sciezka->DijkstraLista();
                pobierzCzas();
            } break;
            case '6': {
                cout << "Algorytm Bellmana Forda na reprezentacji macierzowej \n";
                sciezka->zapelnij_Liste();
                czasStart();
                sciezka->BellmanFordMacierz();
                pobierzCzas();
            } break;
            case '7': {
                cout << "Algorytm Bellmana Forda na reprezentacji listowej \n";
                sciezka->zapelnij_Liste();
                sciezka->BellmanFordLista();
                pobierzCzas();
            } break;
        }
    } while (opt!='0');
}
void czasStart() { //kod z http://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "Blad pomiaru czasu \n";

    PCFreq = double(li.QuadPart)/ 1000.0; //milisekundy

    QueryPerformanceCounter(&li);
    licznik = li.QuadPart;
}
void pobierzCzas() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    std::cout << "Czas operacji : " << (li.QuadPart - licznik) / PCFreq << " milisekund \n";

}