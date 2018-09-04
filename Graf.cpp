#include <iomanip>
#include <cstdlib>
#include "Graf.h"

bool Graf::wczytaj_z_pliku_skierowany(std::string filename) {
    //otwieranie pliku
    file.open(filename);
    if(file.is_open()){
        file >> E;              //wczytujemy krawedzie i wierzcholki
        file >> V;
        file >> vStartowy;
        file >> vKoncowy;
        krawedzie = new Krawedz[E];                                     //tablica krawedzi
        macierzIndcydencji = new signed int * [V];                    //tworzymy tablice wskaznikow
        for(int i = 0;i<V;i++){
            macierzIndcydencji[i] = new signed int[E];                //tworzymy wiersze
        }
        for(int i = 0; i < V; i++){
            for(int j = 0; j < E; j++) {
                macierzIndcydencji[i][j] = 0;
            }
        }
        lista = new Memb * [V];                       //tworzymy pusta tablice list sasiedztwa
        for(int i =0;i<V;i++){
            lista[i] = NULL;
        }
        Krawedz tmpEdge;
        int index=0;
        for(int i = 0;i<E;i++){
            file >> tmpEdge.v1 >> tmpEdge.v2 >> tmpEdge.waga;      // Wierzchołek startowy i końcowy krawędzi i waga
            krawedzie[index] = tmpEdge;
            macierzIndcydencji[tmpEdge.v1][tmpEdge.v2] = tmpEdge.waga;    // Wierzchołek startowy
            tempMemb = new Memb;
            tempMemb->v = tmpEdge.v2;
            tempMemb->next = lista[tmpEdge.v1];
            tempMemb->waga = tmpEdge.waga;
            lista[tmpEdge.v1] = tempMemb;
            index++;
        }
		file.close();
        return true;
    } else {
        return false;
    }
}
bool Graf::wczytaj_z_pliku_nieskierowany(std::string filename) {
	//otwieranie pliku
	file.open(filename);
	if (file.is_open()) {
		file >> E;              //wczytujemy krawedzie i wierzcholki
		file >> V;
		file >> vStartowy;
		file >> vKoncowy;
		krawedzie = new Krawedz[E];                                     //tablica krawedzi
		macierzIndcydencji = new signed int *[V];                    //tworzymy tablice wskaznikow
		for (int i = 0; i<V; i++) {
			macierzIndcydencji[i] = new signed int[E];                //tworzymy wiersze
		}
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < E; j++) {
				macierzIndcydencji[i][j] = 0;
			}
		}
		lista = new Memb *[V];                       //tworzymy pusta tablice list sasiedztwa
		for (int i = 0; i<V; i++) {
			lista[i] = NULL;
		}
		Krawedz tmpEdge;
		int index = 0;
		for (int i = 0; i<E; i++) {
			file >> tmpEdge.v1 >> tmpEdge.v2 >> tmpEdge.waga;      // Wierzchołek startowy i końcowy krawędzi i waga
			krawedzie[index] = tmpEdge;
			macierzIndcydencji[tmpEdge.v1][tmpEdge.v2] = tmpEdge.waga;    // Wierzchołek startowy
			macierzIndcydencji[tmpEdge.v2][tmpEdge.v1] = tmpEdge.waga;    // ...
			tempMemb = new Memb;
			tempMemb->v = tmpEdge.v2;
			tempMemb->next = lista[tmpEdge.v1];
			tempMemb->waga = tmpEdge.waga;
			lista[tmpEdge.v1] = tempMemb;
			index++;
		}
		file.close();
		return true;
	}
	else {
		return false;
	}
}
Graf::Graf() {}
Graf::~Graf() {
    for(int i = 0; i < V; i++) {
        delete[] macierzIndcydencji[i];
    }
    delete [] macierzIndcydencji;

    for(int i = 0; i < V; i++)
    {
        Memb * tmpTmpListElement;
        tempMemb = lista[i];
        while(tempMemb)
        {
            tmpTmpListElement = tempMemb;
            tempMemb = tempMemb->next;
            delete tmpTmpListElement;
        }
    }
    delete [] lista;

}
void Graf::wyswietl_Macierz_Incydencji() {
    if(V==0 || E==0)
        std::cout<<"pusta macierz\n";
    else {
        std::cout << "\n";
        std::cout << "   ";
        for (int i = 0; i < V; i++) std::cout << std::setw(3) << i;
        std::cout << "\n\n";
        for (int i = 0; i < V; i++) {
            std::cout << std::setw(3) << i;
            for (int j = 0; j < V; j++) {
                std::cout << std::setw(3) << (int) macierzIndcydencji[i][j];
            }
            std::cout << "\n";
        }
    }
}
void Graf::wyswietl_Liste_Sasiedztwa() {
    if(V==0 || E==0)
        std::cout<<"pusta lista\n";
    else {
        std::cout << "\n";
        for (int i = 0; i < V; i++) {
            std::cout << "Wierzcholek[" << i << "] =";
            tempMemb = lista[i];
            while (tempMemb) {
                std::cout << std::setw(3) << tempMemb->v << " W: " << tempMemb->waga;
                tempMemb = tempMemb->next;
            }
            std::cout << "\n";
        }
    }
}
// d (gestosc) = 2*E / (V(V-1))
// (d(V(V-1)))/2 = E (liczba krawedzi)
bool Graf::graf_Losowy(int wierzcholki, float gestosc) {
    V = wierzcholki;
    E = floor((gestosc*(wierzcholki*(wierzcholki-1)))/2);
    maxK = V*(V-1);
    minG = ceil((((double)V-1)*100)/(double)maxK);
    std::cout << "Krawedzie: " << E << "\n";
    krawedzie = new Krawedz[E];
    macierzIndcydencji = new signed int * [V];                    //tworzymy tablice wskaznikow
    for(int i = 0;i<V;i++){
        macierzIndcydencji[i] = new signed int[E];                //tworzymy wiersze
    }
    if(E<V-1){
        return false;
    } else {
        for(int i = 0; i < V; i++){
            for(int j = 0; j < E; j++) {
                macierzIndcydencji[i][j] = 0;
            }
        }
        lista = new Memb * [V];                       //tworzymy tablice list sasiedztwa
        for(int i =0;i<V;i++){
            lista[i] = NULL;
        }
        srand(time(NULL));
        Krawedz tmpEdge;
        int index = 0;
        tempMemb = new Memb;
        if(E>0) {
            macierzIndcydencji[0][0] = 1;//tablica[0][0] = -1;
        }

        for (int i = 0; i < (V-1); i++) {       // podstawowe krawedzie
            macierzIndcydencji[i + 1][i] = -1;//tablica[i + 1][i] = i + 1;
            if (i > 0) {
                int tmp2 = rand() % (i+1);
                macierzIndcydencji[tmp2][i] = i+1;//tablica[tmp2][i] = -1;
            }
        }
        for (int i = V - 1; i < E; i++) { //nadprogramowe krawedzie
            int tmp = rand() % V;
            macierzIndcydencji[tmp][i] = (i + 1);
            int tmp1 = rand() % V;
            while (tmp1 == tmp) {
                tmp1 = rand() % V;
            }
            macierzIndcydencji[tmp1][i] = -1;
        }
        for(int i =0;i<E;i++){
            for(int j =0;j<V;j++){
                if(macierzIndcydencji[j][i] > 0){
                    for(int k =0;k<V;k++){
                        if(macierzIndcydencji[k][i] == -1){
                            tmpEdge.v1 = j;
                            tmpEdge.v2 = k;
                            tmpEdge.waga = macierzIndcydencji[j][i];
                            krawedzie[i] = tmpEdge;
                            break;
                        }
                    }
                }
            }
        }
        for(int i =0;i<E;i++){
            Memb * tmp = new Memb;
            tmp->v = krawedzie[i].v2;
            tmp->next = lista[krawedzie[i].v1];
            tmp->waga = krawedzie[i].waga;
            lista[krawedzie[i].v1] = tmp;
        }
        return true;
    }
}
Memb **Graf::get_listaSasiedztwa() {    //getter do listy sasiedztwa
    return lista;
}

signed int **Graf::get_macierzIncydencji() { //getter do macierzy incydencji
    return macierzIndcydencji;
}

int Graf::getV() { //getter do liczby wierzcholkow
    return V;
}

int Graf::getE() { //getter do liczby krawedzi
    return E;
}

Krawedz *Graf::get_Krawedzie() {    //getter do krawedzi
    return krawedzie;
}


