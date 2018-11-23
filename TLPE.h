#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lde{
  int info;
  struct lde *ant, *prox;
} elemento;

typedef struct ldes{
  elemento *prim;
  int tam;
  elemento *ultimo;
  int sinal;
  int maior;
} lista;

// Funções disponíveis para uso.
lista* inicializa(void);
lista* inicia_soma(lista *l1, lista *l2);
lista* inicia_subtracao(lista *l1, lista *l2);
void insere_ini(lista *l, int elem);
void insere_fin(lista *l, int elem);
void imprime(lista *l);
void libera(lista *l);
void retira(lista *l, int elem);
elemento* busca(lista *l, int elem);
void pega_elemento(lista *l,FILE *file);

// Funções utitlizadas dentro do código fonte.
void conserta_dif_de_tam(lista *l1, lista *l2);
void verifica_maior(lista *l1, lista *l2);
void subtrai(lista *l1, lista *l2, lista *l3);
void soma(lista *l1, lista *l2, lista *l3);