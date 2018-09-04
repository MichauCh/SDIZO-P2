#include "Najkrotsza_Sciezka.h"
#define MIN(a,b) (a<b)?a:b
Najkrotsza_Sciezka::Najkrotsza_Sciezka() {}
Najkrotsza_Sciezka::~Najkrotsza_Sciezka() {
    delete [] d;            //usuwamy wszystko
    delete [] p;
    delete [] QS;
    delete [] S;
    delete [] kopiec;
    delete [] pozycjaKopca;
}
//----------------------------------------------------------------------------------------------------------------------
//zapelnianie reprezentacji listowej
void Najkrotsza_Sciezka::zapelnij_Liste() {
    V = getV();
    E = getE();
    lista = get_listaSasiedztwa();
    d = new int[V];             //tablica kosztow dojscia
    p = new int[V];             //tab poprzednikow
    QS = new bool[V];
    S = new int[V];
    kopiec=  new int [V];
    pozycjaKopca = new int[V];
    sptr = 0;
}
//----------------------------------------------------------------------------------------------------------------------
//zapelnianie reprezentacji macierzowej
void Najkrotsza_Sciezka::zapelnij_Macierz() {
    V = getV();
    E = getE();
    lista = get_listaSasiedztwa();
    d = new int[V];             //tablica kosztow dojscia
    p = new int[V];             //tab poprzednikow
    QS = new bool[V];
    S = new int[V];
    kopiec=  new int [V];
    pozycjaKopca = new int[V];
    sptr = 0;

}
//----------------------------------------------------------------------------------------------------------------------
//algorytm Dijkstry na liscie
void Najkrotsza_Sciezka::DijkstraLista() {
    if(this->vStartowy >= 0 && vStartowy <V && vKoncowy >=0 && vKoncowy <V) {
        int *koszt, *poprzednicy;
        bool *odwiedzone;
        int *h;
        int *hPos;
        koszt = new int[V];
        poprzednicy = new int[V];
        odwiedzone = new bool[V];
        h = new int[V];
        hPos = new int[V];
        int korzen;
        int wezel;
        int lChild, rChild, childMin, minCostt;
        int parnet;
        for (int i = 0; i < V; i++) {
            koszt[i] = MAXINT;
            poprzednicy[i] = -1;
            odwiedzone[i] = false;
            h[i] = hPos[i] = i;
        }
        int heapLength = V;
        int x;
        koszt[vStartowy] = 0;
        wezel = h[0];
        h[0] = h[vStartowy];
        h[vStartowy] = wezel;
        hPos[vStartowy] = 0;
        hPos[0] = vStartowy;
        int child;
        for (int i = 0; i < V; i++) {
            korzen = h[0];

            h[0] = h[--heapLength];
            hPos[h[0]] = parnet = 0;
            while (true) {
                lChild = parnet + parnet + 1;
                rChild = lChild + 1;
                if (lChild >= heapLength) break;
                minCostt = koszt[h[lChild]];
                childMin = lChild;
                if ((rChild < heapLength) && (minCostt > koszt[h[rChild]])) {
                    minCostt = koszt[h[rChild]];
                    childMin = rChild;
                }
                if (koszt[h[parnet]] <= minCostt)
                    break;
                wezel = h[parnet];
                h[parnet] = h[childMin];
                h[childMin] = wezel;
                hPos[h[parnet]] = parnet;
                hPos[h[childMin]] = childMin;
                parnet = childMin;
            }
            odwiedzone[korzen] = true;
            Memb *e1;
            if (lista[korzen] != NULL)
                for (e1 = lista[korzen]; e1; e1 = e1->next)
                    if (!odwiedzone[e1->v] && (koszt[e1->v] > koszt[korzen] + e1->waga)) {
                        koszt[e1->v] = koszt[korzen] + e1->waga;
                        poprzednicy[e1->v] = korzen;

                        for (child = hPos[e1->v]; child; child = parnet) {
                            parnet = child / 2;
                            if (koszt[h[parnet]] <= koszt[h[child]])
                                break;
                            wezel = h[parnet];
                            h[parnet] = h[child];
                            h[child] = wezel;
                            hPos[h[parnet]] = parnet;
                            hPos[h[child]] = child;
                        }
                    }
        }
        int minCost = 0;
        for (int i = 0; i < V; i++) {
            std::cout << i << ": ";
            if (i == vKoncowy) {
                minCost = koszt[i];
            }
            if (koszt[i] == MAXINT || koszt[i] < 0) {
                std::cout << i << ": ";
                std::cout << "Brak sciezki\n";
            } else {
                // Ścieżkę przechodzimy od końca ku początkowi,
                // Zapisując na stosie kolejne wierzchołki

                for (int j = i; j > -1; j = poprzednicy[j]) S[sptr++] = j;

                // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

                while (sptr) std::cout << S[--sptr] << " ";

                // Na końcu ścieżki wypisujemy jej koszt

                std::cout << "Koszt: " << koszt[i] << "\n";
            }
        }
        std::cout << "\n";
        if (minCost != MAXINT && minCost >= 0) {
            std::cout << "Minimalny koszt dojscia z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " wynosi: "
                      << minCost << "\n\n";
        } else {
            std::cout << "Przejscie z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " jest niemozliwe \n";
        }
    } else {
        std::cout << "Nie ma takiego/takich wierzcholkow\n";
    }
}
//----------------------------------------------------------------------------------------------------------------------
//wyswietlanie listy sasiedztwa na ekranie
void Najkrotsza_Sciezka::wyswietl_NSLista() {

    int minCost = 0;
    for(int i = 0; i < V; i++)
    {
        std::cout << i << ": ";
        if(i == vKoncowy){
            minCost = d[i];
        }
        // Ścieżkę przechodzimy od końca ku początkowi,
        // Zapisując na stosie kolejne wierzchołki

        for(int j = i; j > -1; j = p[j]) S[sptr++] = j;

        // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

        while(sptr) std::cout << S[--sptr] << " ";

        // Na końcu ścieżki wypisujemy jej koszt

        std::cout << "Koszt: " << d[i] << "\n";
    }
    std::cout << "\n";
    std::cout << "Minimalny koszt dojscia z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " wynosi: " << minCost << "\n\n";
}
//----------------------------------------------------------------------------------------------------------------------
//algorytm Dijkstry na macierzy
void Najkrotsza_Sciezka::DijkstraMacierz() {
	if (this->vStartowy >= 0 && vStartowy < V && vKoncowy >= 0 && vKoncowy < V) {

		spMacierz = get_macierzIncydencji();
		bool wagi_ujemne = false;
		int *koszt, *poprzednicy;
		bool *odwiedzone;
		int *h;
		int *hPos;
		koszt = new int[V];
		poprzednicy = new int[V];
		odwiedzone = new bool[V];
		h = new int[V];
		hPos = new int[V];
		int korzen;
		int wezel;
		int lChild, rChild, childMin, minCostt;
		int parnet;
		for (int i = 0; i < V; i++) {
			koszt[i] = MAXINT;
			poprzednicy[i] = -1;
			odwiedzone[i] = false;
			h[i] = hPos[i] = i;
		}
		int heapLength = V;
		int x;
		koszt[vStartowy] = 0;
		wezel = h[0];
		h[0] = h[vStartowy];
		h[vStartowy] = wezel;
		hPos[vStartowy] = 0;
		hPos[0] = vStartowy;
		int child;
		edges = get_Krawedzie();
		
		for (int i = 0; i < V; i++) {
			korzen = h[0];
			h[0] = h[--heapLength];
			hPos[h[0]] = parnet = 0;
			while (true) {
				lChild = parnet + parnet + 1;
				rChild = lChild + 1;
				if (lChild >= heapLength) break;
				minCostt = koszt[h[lChild]];
				childMin = lChild;
				if ((rChild < heapLength) && (minCostt > koszt[h[rChild]])) {
					minCostt = koszt[h[rChild]];
					childMin = rChild;
				}
				if (koszt[h[parnet]] <= minCostt)
					break;
				wezel = h[parnet];
				h[parnet] = h[childMin];
				h[childMin] = wezel;
				hPos[h[parnet]] = parnet;
				hPos[h[childMin]] = childMin;
				parnet = childMin;
			}
			odwiedzone[korzen] = true;
			for (int l = 0; l < V; l++) {
				if (spMacierz[korzen][l] != 0)
					for (int j = 0; j < V; j++)
						if (spMacierz[korzen][j] != 0 && !odwiedzone[j] && (koszt[j] > koszt[korzen] + spMacierz[korzen][j])) {
							if (spMacierz[korzen][j] < 0) wagi_ujemne = true;
							koszt[j] = koszt[korzen] + spMacierz[korzen][j];
							poprzednicy[j] = korzen;

							for (child = hPos[j]; child; child = parnet) {
								parnet = child / 2;
								if (koszt[h[parnet]] <= koszt[h[child]])
									break;
								wezel = h[parnet];
								h[parnet] = h[child];
								h[child] = wezel;
								hPos[h[parnet]] = parnet;
								hPos[h[child]] = child;
							}
						}
			}
		}
			int minCost = 0;
			for (int i = 0; i < V; i++) {
				std::cout << i << ": ";
				if (i == vKoncowy) {
					minCost = koszt[i];
				}
				if (koszt[i] == MAXINT) {
					std::cout << i << ": ";
					std::cout << "Brak sciezki\n";
				}
				else {
					// Ścieżkę przechodzimy od końca ku początkowi,
					// Zapisując na stosie kolejne wierzchołki
					for (int j = i; j > -1; j = poprzednicy[j]) S[sptr++] = j;
					// Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

					while (sptr) std::cout << S[--sptr] << " ";
					// Na końcu ścieżki wypisujemy jej koszt
					std::cout << "Koszt: " << koszt[i] << "\n";
				}
			}
			std::cout << "\n";
			if (minCost != MAXINT && minCost >= 0) {
				std::cout << "Minimalny koszt dojscia z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " wynosi: "
					<< minCost << "\n\n";
			}
			else {
				std::cout << "Przejscie z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " jest niemozliwe \n";
			}
			if (wagi_ujemne) std::cout << "wykryto ujemne wagi w grafie, algorytm moze dzialac niepoprawnie \n";
		}
		else {
			std::cout << "Nie ma takiego/takich wierzcholkow\n";
		}
}
//----------------------------------------------------------------------------------------------------------------------
//wyswietlanie macierzy incydencji na ekranie
void Najkrotsza_Sciezka::wyswietl_NSMacierz() {
    std::cout << "\n";
    int minCost = 0;
    std::cout << "Najkrotsza droga z wierzcholka nr " << vStartowy << " do wierzcholka nr: " << "\n\n";
    for (int i = 0; i < V; i++)
    {
        std::cout << i << ": ";
        if(i==vKoncowy){
            minCost = d[i];
        }
        if (d[i] == MAXINT || d[i]<0)
            std::cout << "Sciezka nie istnieje \n";
        else
        {
            for (int j = i; j > -1; j = p[j])
            {
                S[sptr++]=j;
            }
            while (sptr)
            {
                std::cout << S[--sptr] << " ";
            }
            std::cout << "Koszt: " << d[i] << "\n";
        }
    }
    std::cout <<"\n\n";
    if (minCost != MAXINT && minCost>=0) {
        std::cout << "Minimalny koszt dojscia z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " wynosi: " << minCost <<"\n\n";
    } else {
        std::cout << "Przejscie z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " jest niemozliwe!" <<"\n\n";
    }
}
//----------------------------------------------------------------------------------------------------------------------
//algorytm Bellmana-Forda dla reprezentacji listy
void Najkrotsza_Sciezka::BellmanFordLista() {
    if(this->vStartowy >= 0 && vStartowy <V && vKoncowy >=0 && vKoncowy <V) {
        D = new long long[V];
        p = new int[V];
        for (int i = 0; i < V; i++) {
            D[i] = MAXINT;
            p[i] = -1;
        }
        int minCost = 0;
        if (cykleUjemne(vStartowy)) { //sprawdzenie czy istnieja ujemne cykle
            S = new int[V];
            sptr = 0;

            for (int i = 0; i < V; i++) {
                if (i == vKoncowy) {
                    minCost = D[i];
                }
                if (D[i] == MAXINT) {
                    std::cout << i << ": ";
                    std::cout << "Brak sciezki\n";
                } else {
                    std::cout << i << ": ";
                    for (int x = i; x != -1; x = p[x]) {
                        S[sptr++] = x;                  //ustawiamy wierzcholki na stosie od odsatniego do pierwszego
                    }
                    while (sptr) {
                        std::cout << S[--sptr] << " ";      //wypisujemy wierzcholki od pierwszego do ostatniego
                    }
                    std::cout << "Koszt: " << D[i] << "\n";
                }
            }
        } else {
            std::cout << "Znaleziono cykle ujemne \n";
        }
        if (minCost != MAXINT) {
            std::cout << "Minimalny koszt dojscia z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " wynosi: "
                      << minCost << "\n\n";
        } else {
            std::cout << "Przejscie z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " jest niemozliwe \n\n";
        }
    } else {
        std::cout << "Blad! Nie ma takiego(takich) wierzcholkow\n";
    }
}
//----------------------------------------------------------------------------------------------------------------------
//funkcja do sprawdzania czy w reprezentacji listowej znajduja sie ujemne sciezki
bool Najkrotsza_Sciezka::cykleUjemne(int v) {
    bool test;
    Memb * pv;
    D[v] = 0;
    lista = get_listaSasiedztwa();
    for(int i =0;i<V;i++){      //relaksacja
        test = true;            // oznacza ze algorytm nie wprowadzil zmian do d i p
        for(int x =0; x<V;x++)
            for(pv = lista[x];pv;pv = pv->next)
                if (D[pv->v] > D[x] + pv->waga) {// sprawdzenie warunku relaksacji
                    test = false;                   // wykryto zmiane w d i p
                    D[pv->v] = D[x] + pv->waga;    // relaksacja z x do jego sąsiada
                    p[pv->v] = x;           // Poprzednikiem sąsiada będzie x

                }
            if(test) return true;         //jezeli nie bylo zmian to konczymy
    }
    for(int x = 0; x < V; x++)
                for(pv = lista[x];pv;pv = pv->next)
                    if(D[pv->v] > D[x] + pv->waga) return false; // ujemny cykl

            return true;
}
//----------------------------------------------------------------------------------------------------------------------
//algorytm Bellmana-Forda na macierzy
void Najkrotsza_Sciezka::BellmanFordMacierz() {
		if (vStartowy >= 0 && vStartowy <V && vKoncowy >= 0 && vKoncowy <V) {
			spMacierz = get_macierzIncydencji();
			D = new long long[V];
			p = new int[V];
			for (int i = 0; i < V; i++) {
				D[i] = MAXINT;
				p[i] = -1;
			}

			D[vStartowy] = 0;

			for(int i=1; i<V; i++)
				for(int l=0; l<V; l++)
				for(int j=0; j<V; j++)
					if (j!=vStartowy && spMacierz[l][j] != 0 && (D[j] > D[l] + spMacierz[l][j])) {
						std::cout << "sciezka z " << l << " do " << j << " ma wage " << spMacierz[l][j] << std::endl;
						D[j] = D[l] + spMacierz[l][j];
						p[j] = l;
					}

			bool jestCyklUjemny = false;

			for (int l = 0; l < V; l++)			//dodatkowy przebieg
				for (int j = 0; j < V; j++)
					if (j != vStartowy && spMacierz[l][j] != 0 && (D[j] > D[l] + spMacierz[l][j])) jestCyklUjemny = true;

			int minCost = 0;
			if (!jestCyklUjemny) {
				S = new int[V];
				sptr = 0;
				for (int i = 0; i<V; i++) {
					if (i == vKoncowy) {
						minCost = D[i];
					}
					if (D[i] == MAXINT) {
						std::cout << i << ": ";
						std::cout << "Brak sciezki" << "\n";
					}
					else {
						std::cout << i << ": ";
						for (int x = i; x != -1; x = p[x]) {

							S[sptr++] = x;                  //ustawiamy wierzcholki na stosie od ostatniego do pierwszego
						}
						while (sptr) {
							std::cout << S[--sptr] << " ";      //wypisywanie wierzcholkow
						}
						std::cout << "Koszt: " << D[i] << "\n";
					}
				}
			}
			else {
				std::cout << "Znaleziono cykle ujemne! \n";
			}

			if (minCost != MAXINT) {
				std::cout << "Minimalny koszt dojscia z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " wynosi: " << minCost << "\n\n";
			}
			else {
				std::cout << "Przejscie z krawedzi " << vStartowy << " do krawedzi " << vKoncowy << " jest niemozliwe!" << "\n\n";
			}
		}
		else {
			std::cout << "nie ma takiego/takich wierzcholkow \n";
		}
}


