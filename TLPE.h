#include <stdio.h>
#include <stdlib.h>

typedef struct lde{
  int info;
  struct lde *ant, *prox;
} TLDE;

TLDE* insere(TLDE *l, int elem);
void imprime(TLDE *l);
void libera(TLDE *l);
TLDE* retira(TLDE *l, int elem);
TLDE* busca(TLDE *l, int elem);

