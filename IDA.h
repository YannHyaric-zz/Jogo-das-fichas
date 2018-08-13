//-----------------------------------IDA.h
#ifndef IDA_H_INCLUDED
#define IDA_H_INCLUDED
#include <iostream>
#include "Movimento.h"
#include "Heuristica.h"
#include "Lista.h"
class IDA{
    private:
        Movimento* mov;
        Heuristica* custo;
        Lista* fechados;
        Lista* abertos;
        Lista* descartados;
        int size_N;
        int patamar;
        int *estadoInicial;
        bool verifica();
        void explora();
        void copia(int* a,int* b);
        void reseta();
    public:
        IDA(int* estad, int tam);
        void caminho();
        void resolve();

};
#endif // IDA_H_INCLUDED
//-----------------------------------IDA.cpp
#include "IDA.h"


IDA::IDA(int* estad, int tam){
    size_N=tam;
    mov = new Movimento(size_N);
    custo = new Heuristica();
    descartados = new Lista();
    fechados = new Lista();
    abertos = new Lista();
    estadoInicial = new int[(2*tam)+1];
    copia(estadoInicial, estad);

    abertos->adiciona(NULL,estadoInicial,size_N);
    patamar = custo->pecasFora(abertos->get_raiz()->get_estado(),tam);
}

bool IDA::verifica(){
    int val = custo->pecasFora(fechados->get_ultimo()->get_estado(), size_N);
    return val == 0;
}

void IDA::copia(int* a,int* b){
    for(int i = 0; i < (2*size_N)+1; i++)
        a[i] = b[i];
}

void IDA::explora(){
    int* estad = new int[(2*size_N)+1];
    copia(estad, fechados->get_ultimo()->get_estado());
    for(int i = 1; i<5 ; i++){
        int *aux = new int[2*size_N+1];
        copia(aux, estad);
        if(mov->movimenta(i, aux)){
            if((fechados->get_ultimo()->get_profundidade() + custo->pecasFora(aux,size_N) + 1) <= patamar)
                abertos->adiciona(fechados->get_ultimo(),aux, size_N);
            else
                descartados->adiciona(fechados->get_ultimo(), aux, size_N);
        }
    }
}

void IDA::caminho(){
    int* x = fechados->get_ultimo()->get_estado();
    No_Lista *atual = fechados->get_ultimo();
    while(1){
        for(int i = 0; i < 2*size_N+1; i++)
        {
            std::cout<< x[i]<< " , ";
        }
        std::cout<<";"<<endl;
        if(atual->get_est_ant()==NULL)
            return;
        atual = atual->get_est_ant();
        x=atual->get_estado();
    }
}

void IDA::resolve(){
    int fn;
    No_Lista *menor;
    No_Lista *atual;
    while(true){
        menor = atual;
        atual = abertos->get_raiz();
        fn = custo->pecasFora(atual->get_estado(),size_N)+atual->get_profundidade();
        while(atual != NULL){
            if(fn>(custo->pecasFora(atual->get_estado(),size_N)+atual->get_profundidade())){
                fn = custo->pecasFora(atual->get_estado(),size_N)+atual->get_profundidade();
                menor = atual;
            }
            atual=atual->get_filho();
       }
       fechados->adiciona(menor->get_est_ant(),menor->get_estado(),size_N);
       abertos->apagar(menor->get_ID());
       if (verifica()){
            std::cout<<"Numero de nos expandidos: "<<abertos->get_tamanho() + fechados->get_tamanho()<<std::endl;
            return;
       }
       explora();
       if(abertos->get_raiz()==NULL){
         reseta();
       }
    }
}

void IDA::reseta(){
    int novoPatamar=custo->pecasFora(descartados->get_raiz()->get_estado(),size_N)+descartados->get_raiz()->get_profundidade();
    while(descartados->get_ultimo()!=NULL){
        if(custo->pecasFora(descartados->get_ultimo()->get_estado(),size_N)+descartados->get_ultimo()->get_profundidade()<novoPatamar)
            novoPatamar=custo->pecasFora(descartados->get_ultimo()->get_estado(),size_N) + descartados->get_ultimo()->get_profundidade();
        descartados->apagar(descartados->get_ultimo()->get_ID());
    }
    patamar=novoPatamar;
    std::cout<<"patamar: "<<patamar<<endl;
    abertos->adiciona(NULL,estadoInicial,size_N);
    while(fechados->get_ultimo()!=NULL){
        fechados->apagar(fechados->get_ultimo()->get_ID());
    }
}


