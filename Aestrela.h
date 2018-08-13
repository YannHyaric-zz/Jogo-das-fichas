//----------------------------------------------------- Aestrela.h
#ifndef AESTRELA_H_INCLUDED
#define AESTRELA_H_INCLUDED

#include <iostream>
#include "Movimento.h"
#include "Heuristica.h"
#include "Lista.h"

class Aestrela{
    private:
      Lista* fechados;
      Lista* abertos;
      Heuristica* custo;
      Movimento* mov;
      int size_N;
      void explora();
      bool verifica();
      void copia(int* a, int* b);
    public:
        Aestrela(int* estados, int tam);
        void resolve();
        void caminho();

};
#endif // AESTRELA_H_INCLUDED
//--------------------------------------Aestrela.cpp--------------------------------------
#include"Aestrela.h"

Aestrela::Aestrela(int* estados, int tam){
    fechados = new Lista();
    abertos = new Lista();
    custo = new Heuristica();
    size_N=tam;
    mov = new Movimento(size_N);
    abertos->adiciona(NULL,estados,tam);
}

bool Aestrela::verifica(){
    int val = custo->pecasFora(fechados->get_ultimo()->get_estado(),size_N);
    return (val == 0);
}

void Aestrela::copia(int* a, int* b){
    for(int i = 0; i<(2*size_N)+1; i++)
        a[i] = b[i];
}

void Aestrela::explora(){
    int* estad = new int[(2*size_N)+1];
    copia(estad, fechados->get_ultimo()->get_estado());
    for(int i = 1; i < 5; i++){
        int *aux = new int[2*size_N+1];
        copia(aux,estad);
        if(mov->movimenta(i,aux))
            abertos->adiciona(fechados->get_ultimo(),aux,size_N);
    }
}

void Aestrela::caminho(){
    int* x = fechados->get_ultimo()->get_estado();
    No_Lista *atual = fechados->get_ultimo();
    while(true){
        for(int i = 0;i<2*size_N+1;i++)
        {
            std::cout<< x[i]<< " , ";
        }
        std::cout<<";"<<endl;
        if(atual->get_est_ant()==NULL)
            return;
        atual=atual->get_est_ant();
        x=atual->get_estado();

    }
}

void Aestrela::resolve(){
    int fn;
    No_Lista *atual;
    No_Lista *menor;
    while(true){
        atual = abertos->get_raiz();
        menor = atual;
        fn = custo->pecasFora(atual->get_estado(),size_N) + atual->get_profundidade();
        while(atual != NULL){
            if(fn > (custo->pecasFora(atual->get_estado(),size_N)+atual->get_profundidade())){
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
    }
}
