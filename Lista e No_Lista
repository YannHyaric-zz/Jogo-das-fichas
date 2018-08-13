//-----------------------------Lista.h
#ifndef LISTA_H
#define LISTA_H
#include"include/No_Lista.h"
class Lista{
    private:
        No_Lista* ultimo;
        No_Lista* raiz;
        int tamanho;
        int cont_id;

    public:
        Lista(){raiz = NULL; ultimo = NULL; tamanho = 0; cont_id = 0;}
        ~Lista(){ while(ultimo != NULL) apagar(ultimo->get_ID()); }
        No_Lista* get_ultimo(){return ultimo;}
        No_Lista* get_raiz(){return raiz;}
        int get_tamanho(){return tamanho;}
        void adiciona(No_Lista* no_est_ant, int* estad, int size_N);
        void adicionar_ord(No_Lista* no_est_ant, int* estad, int size_N, int objetivo);
        void apagar(int novo_ID);
        void imprime();
};
#endif // LISTA_H
//-----------------------------Lista.cpp
#include "Lista.h"

void Lista::imprime(){
    No_Lista* temp = raiz;
    while(temp != NULL){
        cout << temp->get_ID() << "-\t";
        for(int i = 0; i < (2*temp->get_N()+1); i++){
            cout << temp->get_estado()[i] << "\t";
        }cout << "\n";
        temp = temp->get_filho();
    }
}

void Lista::adiciona(No_Lista* no_est_ant, int* estad, int size_N){
    if(tamanho == 0){
        No_Lista* no = new No_Lista(ultimo, no_est_ant, 0, size_N, estad, 0);
        raiz = ultimo = no;
        tamanho++;
        return;
    }

    No_Lista* no = new No_Lista(ultimo, no_est_ant, (no_est_ant->get_profundidade()+1), size_N, estad, (ultimo->get_ID()+1));
    ultimo->set_filho(no);
    ultimo = no;
    tamanho++;
    cont_id++;
}

void Lista::adicionar_ord(No_Lista* no_est_ant, int* estad, int size_N, int objetivo){
    if(tamanho == 0){
        No_Lista* no = new No_Lista(ultimo, no_est_ant, objetivo, size_N, estad, cont_id);
        raiz = ultimo = no;
        tamanho++;
        cont_id++;
        return;
    }

    No_Lista* no = new No_Lista(ultimo, no_est_ant, objetivo, size_N, estad, cont_id);
    if(raiz->get_profundidade() <= objetivo){
        // raiz

        no->set_pai(NULL);
        no->set_filho(raiz);
        no->get_filho()->set_pai(no);
        raiz = no;

    }else if(ultimo->get_profundidade() >= objetivo){
        // ultimo

        no->set_filho(NULL);
        no->set_pai(ultimo);
        no->get_pai()->set_filho(no);
        ultimo = no;

    }else{
        // meio
        No_Lista *temp = raiz;
        while(temp->get_profundidade() > objetivo) temp = temp->get_filho();

        no->set_pai(temp->get_pai());
        no->set_filho(temp);
        no->get_filho()->set_pai(no);
        no->get_pai()->set_filho(no);

    }

    tamanho++;
    cont_id++;
}

void Lista::apagar(int novo_ID){
    if(tamanho == 0) return;

    No_Lista *temp = raiz;
    while(temp->get_ID() != novo_ID) temp = temp->get_filho();

    if(temp->get_pai() != NULL) temp->get_pai()->set_filho(temp->get_filho());
    else raiz = temp->get_filho();

    if(temp->get_filho() != NULL) temp->get_filho()->set_pai(temp->get_pai());
    else ultimo = temp->get_pai();

    delete temp;
    tamanho--;
}
//--------------------------No_Lista
#ifndef NO_LISTA_H
#define NO_LISTA_H
class No_Lista{
    private:
        No_Lista* pai;
        No_Lista* filho;       
        No_Lista* est_ant;
        int profundidade;
        int ID;
        int* estado;
        int tam_N;
    public:
        No_Lista(No_Lista* no_pai, No_Lista* no_est_ant, int prof, int tamN, int* estad, int I_D);
        ~No_Lista(){delete[] estado;}
        int get_ID(){return ID;}
        int get_profundidade(){return profundidade;}
        int get_N(){return tam_N;}
        int* get_estado(){return estado;}
        No_Lista* get_pai(){return pai;}
        No_Lista* get_filho(){return filho;}
        No_Lista* get_est_ant(){return est_ant;}
        void set_filho(No_Lista* no){filho = no;}
        void set_pai(No_Lista* no){pai = no;}
};
#endif // NO_LISTA_H
//-------------------------------------No_Lista.cpp

No_Lista::No_Lista(No_Lista* no_pai, No_Lista* no_est_ant, int prof, int tamN, int* estad, int I_D){
    estado = new int[tamN];
    for(int i = 0; i < tamN; i++) estado[i] = estad[i];
    ID = I_D;
    pai = no_pai;
    est_ant = no_est_ant;
    profundidade = prof;
    tam_N = tamN;
    filho = NULL;
}

