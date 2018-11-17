#include "TLPE.h"

int main(void){
  int n;
  printf("Escreva o tamanho do vetor \n");
  scanf("%d", &n);
  if(n <= 0) return 0;

  lista* teste = inicializa();
  int i;
  for (i=0; i<n; i++){
      printf("Escreva o elemento que deseja ser inserido \n");
      int elem;
      scanf(" %d", &elem);
      insere_fin(teste, elem);
  }
  imprime(teste);
  libera(teste);
  return 0;
}
