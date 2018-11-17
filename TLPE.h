#include <stdio.h>
#include <stdlib.h>

typedef struct lde{
  int info;
  struct lde *ant, *prox;
} elementos;

typedef struct ldes{
  elementos *prim;
  int tam;
  elementos *ultimo;
} lista;

lista* inicializa(void);
void insere_ini(lista *l, int elem);
void insere_fin(lista *l, int elem);
void imprime(lista *l);
void libera(lista *l);
void retira(lista *l, int elem);
elementos* busca(lista *l, int elem);
