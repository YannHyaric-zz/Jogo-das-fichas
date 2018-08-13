#include <iostream>
#include <math.h>
#include "Lista.h"
#include "Heuristica.h"
#include "Guloso.h"
#include "Movimento.h"
#include "nao_informados.h"
#include "Aestrela.h"
#include "IDA.h"
#include <fstream>
#include <time.h>

using namespace std;

int main(){
    clock_t start, end;
    for(int n=2;n<10;n++){
      int* estad = new int[(2*n)+1];
      int i = 0;
      for(; i<n ; i++){
          estad[i]=1;
      }
      estad[i]=0;
      i++;
      for(; i<(2*n)+1 ; i++){
          estad[i]=-1;
      }
      
      start = clock();
      Guloso* metodo1 = new Guloso(estad,n);
      metodo1->resolve();//metodo->caminho();
      cout <<"Guloso: N="<<n << " tempo: " << ((double)(clock() - start)*1000)/CLOCKS_PER_SEC << endl;
      
      start=clock();
      Aestrela* metodo2 = new Aestrela(estad,n);
      metodo2->resolve();//metodo->caminho();
      cout <<"A* : N="<<n << " tempo: " << ((double)(clock() - start)*1000)/CLOCKS_PER_SEC << endl;
      
      start=clock();
      IDA* metodo3 = new IDA(estad,n);
      metodo3->resolve();//metodo->caminho();
      cout <<"IDA*: N="<<n << " tempo: " << ((double)(clock() - start)*1000)/CLOCKS_PER_SEC << endl;
      
    }
    
    /// TESTE DE TEMPO: NAO INFORMADOS
/// INSTANCIAS SAO GERADAS AUTOMATICAMENTE NO CONSTRUTOR, SEGUINDO A FORMA [1,1,0,-1,-1]

    int n_pecas;
    Nao_informados *n_inf;
    ofstream arq;
    //string nomeArq = "busca-ordenada.txt";
    //string nomeArq = "busca-profundidade.txt";
    //string nomeArq = "busca-backtracking.txt";
    string nomeArq = "busca-largura.txt";
    clock_t tInicio, tFim;
    arq.open(nomeArq.c_str(), ofstream::app);
    for(int i = 1; i <= 10; i++){
        n_pecas = i;
        arq <<"numero de pecas: "<< n_pecas<<endl;
        n_inf = new Nao_informados(n_pecas);
        tInicio = clock();
        //if(n_inf->ordenada())
        //if(n_inf->profundidade())
        //if(n_inf->backtracking())
        if(n_inf->largura())
            cout<<"n pecas: " <<n_pecas<< " concluido em ";
        else
            cout << endl<<endl<<"Nao foi possivel resolver"<<endl<<endl;
        tFim = clock();
        tempo_total = 1000*(((double)(tFim - tInicio)) / ((double)CLOCKS_PER_SEC));
        cout<< 1000*(((double)(tFim - tInicio)) / ((double)CLOCKS_PER_SEC))<<endl;
        arq <<"\t tempo: "<< 1000*(((double)(tFim - tInicio)) / ((double)CLOCKS_PER_SEC))<<endl;

    }
    delete(n_inf);
    arq.close();
}


/*
/// TESTE DE MEMÓRIA DOS NÃO INFORMADOS
int main(){
    int n_pecas;
    Nao_informados *n_inf;
    ofstream arq;
    //string nomeArq = "ordenada_memoria.txt";
    //string nomeArq = "profundidade_memoria.txt";
    //string nomeArq = "largura_memoria.txt";
    string nomeArq = "backtracking_memoria.txt";
    arq.open(nomeArq.c_str(), ofstream::app);
    for(int i = 1; i <= 10; i++){
        n_pecas = i;
        arq << n_pecas;
        n_inf = new Nao_informados(n_pecas);
        //if(n_inf->ordenada())
        //if(n_inf->profundidade())
        //if(n_inf->largura())
        if(n_inf->backtracking())
            cout << i << endl;
        else cout << endl<<"Nao foi possivel resolver"<< endl;
        arq << "\t nos: " << n_inf->get_tam_lista();
        delete n_inf;
        arq << endl;
    }
    arq.close();
}*/
    return 0;
}
