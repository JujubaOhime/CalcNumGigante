#include <stdio.h>
#include <stdlib.h>

typedef struct lde{
  int info;
  struct lde *ant, *prox;
} TLDE;

typedef struct ldes{
  TLDE *prim;
  int tam;
  TLDE *ultimo;
} TLD;

TLD* inicializa(void);
void insere(TLD *l, int elem);
void imprime(TLD *l);
void libera(TLDE *l);
TLDE* retira(TLDE *l, int elem);
TLDE* busca(TLDE *l, int elem);
