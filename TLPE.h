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
  int sinal;
} lista;

lista* inicializa(void);
lista* inicializa_e_insere(int num);
lista* soma(int num1, int num2);
lista* subtracao(int num1, int num2);
int tam_int(int numero);
void insere_ini(lista *l, int elem);
void insere_fin(lista *l, int elem);
void imprime(lista *l);
void libera(lista *l);
void retira(lista *l, int elem);
elementos* busca(lista *l, int elem);
void conserta_dif_de_tam(lista *l1, lista *l2);
