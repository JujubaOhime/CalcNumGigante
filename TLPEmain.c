#include "TLPE.h"

int main(void){
  int n;
  printf("Escreva o tamanho do vetor \n");
  scanf("%d", &n);
  if(n <= 0) return 0;

  lista* teste = inicializa();
  insere_ini(teste, 1);
  printf("O ultimo elemento é: %d\n", teste->ultimo->info);
  insere_ini(teste, 3);
  printf("Antes da ordenacao...\n");
  imprime(teste);
  printf("O primeiro elemento é: %d\n", teste->prim->info);
  printf("O próximo elemento do primeiro é: %d\n", teste->prim->prox->info);
  printf("O elemento anterior do segundo elemento é: %d\n", teste->prim->prox->ant->info);
  printf("O ultimo elemento é: %d\n", teste->ultimo->info);
  //printf("O próximo próximo elemento do primeiro é: %d\n", teste->prim->prox->prox->info);
  insere_ini(teste, 2);
  printf("entrou");
  printf("O primeiro elemento é: %d", teste->prim->info);
  printf("O próximo elemento do primeiro é: %d", teste->prim->prox->info);
  retira(teste, 1);
  printf("Depois da ordenacao...\n");
  imprime(teste);
  libera(teste);
  return 0;
}
