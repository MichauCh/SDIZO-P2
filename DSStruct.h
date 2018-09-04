#ifndef DSSTRUCT_H
#define DSSTRUCT_H
#include "Krawedz.h"
//definicja obiektu struktury zbiorow rozlacznych
class DSStruct{
private:
    struct DSNode {
        int up, rank;
    };
    DSNode * Z;
public:
    DSStruct(int n);
    ~DSStruct();
    void MakeSet(int v);
    int FindSet(int v);
    void UnionSets(Krawedz e);
};
#endif
