#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lde{
  int info;
  struct lde *ant, *prox;
} elementos;

typedef struct ldes{
  elementos *prim;
  int tam;
  elementos *ultimo;
  int sinal;
  int maior;
} lista;

lista* inicializa(void);
lista* inicia_soma(lista *l1, lista *l2);
lista* inicia_subtracao(lista *l1, lista *l2);
void insere_ini(lista *l, int elem);
void insere_fin(lista *l, int elem);
void imprime(lista *l);
void libera(lista *l);
void retira(lista *l, int elem);
elementos* busca(lista *l, int elem);
void conserta_dif_de_tam(lista *l1, lista *l2);
void pega_elementos(lista *l,FILE *file);
void verifica_maior(lista *l1, lista *l2);
void subtrai(lista *l1, lista *l2, lista *l3);
void soma(lista *l1, lista *l2, lista *l3);