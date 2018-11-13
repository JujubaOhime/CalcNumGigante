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
void insere_ini(TLD *l, int elem);
void insere_fin(TLD *l, int elem);
void imprime(TLD *l);
void libera(TLD *l);
void retira(TLD *l, int elem);
TLDE* busca(TLDE *l, int elem);
