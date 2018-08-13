//------------------------------------------------Guloso.h
#ifndef GULOSO_H_INCLUDED
#define GULOSO_H_INCLUDED

#include <iostream>
#include "Movimento.h"
#include "Heuristica.h"
#include "Lista.h"

class Guloso{
    private:
      Lista* fechados;
      Lista* abertos;
      Movimento* mov;
      Heuristica* custo;
      int size_N;
      void melhor_mov();
      bool verifica();
      void copia(int* a,int* b);
    public:
        void resolve();
        void caminho();
        Guloso(int* estad, int tam);
};
#endif // GULOSO_H_INCLUDED
//--------------------------------------------------Guloso.cpp 
#include "Guloso.h"

Guloso::Guloso(int* estad, int tam){
    size_N=tam;
    custo = new Heuristica();
    mov = new Movimento(size_N);
    abertos = new Lista();
    fechados = new Lista();
    abertos->adiciona(NULL,estad,tam);
}

void Guloso::resolve(){
    int i = 0;
    while(true){
        i++;
        if(abertos->get_ultimo() == NULL)
            return;
        fechados->adiciona(
            abertos->get_ultimo()->get_est_ant(),
            abertos->get_ultimo()->get_estado(),
            size_N);
        if (verifica()){
            std::cout<<"Numero de nos expandidos: "<<abertos->get_tamanho()+fechados->get_tamanho()<<std::endl;
            return;
        }
        abertos->apagar(abertos->get_ultimo()->get_ID());
        melhor_mov();
    }
}

void Guloso::copia(int* a,int* b){
    for(int i = 0; i<(2*size_N)+1;i++)
        a[i] = b[i];
}

void  Guloso::melhor_mov(){
    int *aux = new int[2*size_N+1];
    int *estad = new int[2*size_N+1];
    copia(estad,fechados->get_ultimo()->get_estado());
    copia(aux,estad);
    int a=-1,
        b=-1,
        c=-1,
        d=-1;
    if(mov->moveR1(aux)){
        a=custo->pecasFora(aux,size_N);
        copia(aux, estad);
    }

    if(mov->moveR2(aux)){
        b=custo->pecasFora(aux,size_N);
        copia(aux,estad);
    }

    if(mov->moveR3(aux)){
        c=custo->pecasFora(aux,size_N);
        copia(aux,estad);
    }

    if(mov->moveR4(aux)){
        d=custo->pecasFora(aux,size_N);
        copia(aux,estad);
    }

    while(true){
        if(a == -1 &&
           b == -1 &&
           c == -1 &&
           d == -1){
            return;
        }
        else if(a >= b &&
                a >= c &&
                a >= d&&
                a != -1){
            if(mov->moveR1(aux)){
                int *aux2=new int[2*size_N+1];
                copia(aux2,aux);
                abertos->adiciona(fechados->get_ultimo(),aux2,size_N);
            }
            a = -1;
            copia(aux,estad);
        }else if(b >= c &&
                 b >= d &&
                 b != -1) {
            if(mov->moveR2(aux)){
                int *aux2 = new int[2*size_N+1];
                copia(aux2, aux);
                abertos->adiciona(fechados->get_ultimo(), aux2, size_N);
            }
            b = -1;
            copia(aux, estad);
        }else if(c >= d && c != -1){
            if(mov->moveR3(aux)){
                int *aux2 = new int[2*size_N+1];
                copia(aux2, aux);
                abertos->adiciona(fechados->get_ultimo(), aux2,size_N);
            }
            c = -1;
            copia(aux, estad);
        }else if(d != -1){
            if(mov->moveR4(aux)){
                int *aux2 = new int[2*size_N + 1];
                copia(aux2, aux);
                abertos->adiciona(fechados->get_ultimo(), aux2,size_N);
            }
            d = -1;
            copia(aux, estad);
        }
    }
}

bool Guloso::verifica(){
    int val = custo->pecasFora(fechados->get_ultimo()->get_estado(),size_N);
    return (val == 0);
}

void Guloso::caminho(){
    int* x=fechados->get_ultimo()->get_estado();
    No_Lista *atual = fechados->get_ultimo();
    while(true){
        for(int i = 0;i<2*size_N+1;i++)
        {
            std::cout<< x[i]<< " , ";
        }
        std::cout<<";"<<endl;
        if(atual->get_est_ant() == NULL)
            return;
        atual = atual->get_est_ant();
        x = atual->get_estado();
    }
}
