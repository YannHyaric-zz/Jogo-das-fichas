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
    return 0;
}
