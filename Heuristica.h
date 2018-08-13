//----------------------------------Heuristica.h
#ifndef HEURISTICA_H_INCLUDED
#define HEURISTICA_H_INCLUDED

class Heuristica{
    private:
    public:
        Heuristica(){};
        int pecasFora(int* estado, int size_N);
};
#endif // HEURISTICA_H_INCLUDED
//----------------------------------------Heuristica.cpp
#include "Heuristica.h"

int Heuristica::pecasFora(int* estado, int size_N){
    int quant = 0;
    int i = 0;
    for(; i<size_N ; i++){
        if(estado[i]>0)
            quant++;
    }
    i++;
    for(; i<(2*size_N)+1 ; i++){
        if(estado[i]<0)
            quant++;
    }
    return quant;
}
