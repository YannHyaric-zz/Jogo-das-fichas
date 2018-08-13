//-----------------------------------------Movimento.h
#ifndef MOVIMENTO_H_INCLUDED
#define MOVIMENTO_H_INCLUDED

class Movimento
{
    private:
        int encontraVazio(int* estado);
        int size_N;
    public:
        Movimento(int tam){size_N = tam;};
        bool moveR1(int* estado);
        bool moveR2(int* estado);
        bool moveR3(int* estado);
        bool moveR4(int* estado);
        bool movimenta(int mov, int* estado);
};
#endif // MOVIMENTO_H_INCLUDED
//-----------------------------------------Movimento.cpp

#include "Movimento.h"
#include <iostream>
int Movimento::encontraVazio(int* estado)
{
    int i;
    for(i = 0; estado[i] != 0; i++);
    return i;
}

bool Movimento::moveR1(int* estado)
{
    int i = encontraVazio(estado);
    if(i-1 >= 0)
        if(estado[i-1] > 0)
            {
                std::swap(estado[i], estado[i-1]);
                return true;
            }
    return false;
}
bool Movimento::moveR2(int* estado)
{
//    cout << "\nmovimento 2" << endl;
    int i = encontraVazio(estado);
    if(i-2 >= 0)
        if(estado[i-2] > 0)
            {
                std::swap(estado[i], estado[i-2]);
                return true;
            }
    return false;
}
bool Movimento::moveR3(int* estado)
{
    int i = encontraVazio(estado);
    if(i+1 < (2*size_N+1))
        if(estado[i+1] < 0)
            {
                std::swap(estado[i], estado[i+1]);
                return true;
            }
    return false;
}
bool Movimento::moveR4(int* estado)
{
    int i = encontraVazio(estado);
    if(i+2 < (2*size_N+1))
        if(estado[i+2] < 0)
            {
                std::swap(estado[i], estado[i+2]);
                return true;
            }
    return false;
}

bool Movimento::movimenta(int mov, int* estado){
    if (mov == 1)
        return moveR1(estado);
    if (mov == 2)
        return moveR2(estado);
    if (mov == 3)
        return moveR3(estado);
    if (mov == 4)
        return moveR4(estado);
    return false;
}
