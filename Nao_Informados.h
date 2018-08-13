//---------------------------------Nao_Informados.h
#ifndef NAO_INFORMADO_H_INCLUDED
#define NAO_INFORMADO_H_INCLUDED

#include "Lista.h"
#include "Movimento.h"
#include <math.h>

class Nao_informados{
    private:
        int *jogo;
        int *temp;
        int val_ord();
        int tam_list;
        int N_pecas;

        Movimento *movimento;
        bool verifica_fim();
        bool bt_retorna();
        Lista *lista;

    public:
        Nao_informados(int n_pecas);
        ~Nao_informados();
        int get_tam_lista(){return tam_list;}
        void mostrar_jogo();
        bool backtracking();
        bool largura();
        bool profundidade();
        bool ordenada();
};
#endif // NAO_INFORMADO_H_INCLUDED
//---------------------------------Nao_Informados.cpp
#include "Nao_informados.h"

Nao_informados::Nao_informados(int n_pecas){

    // cria o estado inicial do jogo
    N_pecas = n_pecas;
    temp = new int[2*N_pecas+1];
    jogo = new int[2*N_pecas+1];
    for(int i = 0; i < 2*N_pecas+1; i++){
        if(i < N_pecas) jogo[i] = 1;
        else if(i == N_pecas) jogo[i] = 0;
        else jogo[i] = -1;
    }

    // adiciona estado inical na lista
    lista = new Lista();

    tam_list = 1;
    lista->adicionar_ord(NULL, jogo, (2*N_pecas+1), val_ord());

    // cria movimentos
    movimento = new Movimento(N_pecas);

}

Nao_informados::~Nao_informados(){
    delete lista;
    delete movimento;
    delete[] jogo;
    delete[] temp;
}

bool Nao_informados::verifica_fim(){
    for(int i = 0; i <= N_pecas; i++){
        if(i < N_pecas && jogo[i] != -1) return false;
        if(i == N_pecas && jogo[i] != 0) return false;
    }
    return true;
}

bool Nao_informados::bt_retorna(){

    // verifica jogo impossivel
    if(lista->get_ultimo()->get_ID() == lista->get_raiz()->get_ID()){
        return false;
    }

    // apaga ultimo no da lista
    lista->apagar(lista->get_ultimo()->get_ID());
    tam_list--;
    for(int i = 0; i < 2*N_pecas+1; i++) jogo[i] = lista->get_ultimo()->get_estado()[i];
    return true;
}

void Nao_informados::mostrar_jogo(){
    cout << endl;
    for(int i = 0; i < 2*N_pecas+1; i++){
        cout << jogo[i] << "\t";
    }
}

bool Nao_informados::backtracking(){

    if(verifica_fim()) return true;

    for(int m = 1; m <= 4; m++){
        if(movimento->movimenta(m, jogo)){
            lista->adiciona(lista->get_ultimo(), jogo, (2*N_pecas+1));
            tam_list++;
            backtracking();
            if(verifica_fim()){
                lista->adiciona(lista->get_ultimo(), jogo, (2*N_pecas+1));
                tam_list++;
                return true;
            }
        }
    }

    if(!bt_retorna()) return false;

    return false;
}

bool Nao_informados::largura(){

    for(int k = 0; k < (2*N_pecas+1); k++) temp[k] = jogo[k];

    for(int m = 1; m <= 4; m++){
        if(movimento->movimenta(m, jogo)){
            lista->adiciona(lista->get_ultimo(), jogo, (2*N_pecas+1));
            tam_list++;
            for(int k = 0; k < (2*N_pecas+1); k++) jogo[k] = temp[k];
        }
    }

    if(verifica_fim()) return true;

    // remove raiz
    if(lista->get_tamanho() == 0) return false;
    lista->apagar(lista->get_raiz()->get_ID());

    // jogo vira o estado da nova raiz
    for(int i = 0; i < 2*N_pecas+1; i++) jogo[i] = lista->get_raiz()->get_estado()[i];

    return largura();
}

bool Nao_informados::profundidade(){

    // remove ultimo
    if(lista->get_tamanho() == 0) return false;
    lista->apagar(lista->get_ultimo()->get_ID());

    for(int k = 0; k < (2*N_pecas+1); k++) temp[k] = jogo[k];

    for(int m = 1; m <= 4; m++){
        if(movimento->movimenta(m, jogo)){
            lista->adiciona(lista->get_ultimo(), jogo, (2*N_pecas+1));
            tam_list++;
            for(int k = 0; k < (2*N_pecas+1); k++) jogo[k] = temp[k];
        }
    }

    if(verifica_fim()) return true;

    // jogo vira o estado do ultimo
    for(int i = 0; i < 2*N_pecas+1; i++) jogo[i] = lista->get_ultimo()->get_estado()[i];

    return profundidade();
}

int Nao_informados::val_ord(){
    int val = 0;
    for(int i = 0; i < 2*N_pecas+1; i++)
        val += jogo[i]*(N_pecas-i);
    return val;
}

bool Nao_informados::ordenada(){

    // remove o ultimo
    if(lista->get_tamanho() == 0)
        return false;
    lista->apagar(lista->get_ultimo()->get_ID());

    for(int k = 0; k < (2*N_pecas+1); k++) temp[k] = jogo[k];

    for(int m = 1; m <= 4; m++){
        if(movimento->movimenta(m, jogo)){
            lista->adicionar_ord(lista->get_ultimo(), jogo, (2*N_pecas+1), val_ord());
            tam_list++;
            for(int k = 0; k < (2*N_pecas+1); k++) jogo[k] = temp[k];
        }
    }

    if(verifica_fim()) return true;

    // jogo vira estado do ultimo
    for(int i = 0; i < 2*N_pecas+1; i++)
        jogo[i] = lista->get_ultimo()->get_estado()[i];

    return ordenada();
}
