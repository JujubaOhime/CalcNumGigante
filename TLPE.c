#include "TLDE.h"

void insere(TLD *l, int elem){
  TLDE *novo = (TLDE *) malloc(sizeof(TLDE));
  novo->ant = NULL;
  novo->info = elem;
  novo->prox = l->prim;
  l->tamanho = l->tamanho + 1
  if (l->prim == NULL) l->ultimo = novo;
  l->prim = novo;
//  if(l) l->ant = novo;
} 

void imprime(TLD *l){
  TLDE *p = l->prim;
  while(p){
    printf("% d ", p->info);
    p = p->prox;
  } 
}

void libera(TLDE *l){
  TLDE *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}

TLDE* retira(TLDE *l, int elem){
  TLDE *p = busca(l, elem);
  if(!p) return l;
  if(p == l) l = l->prox;
  else p->ant->prox = p->prox;
  if(p->prox) p->prox->ant = p->ant;
  free(p);
  return l;
}

TLDE* busca(TLDE *l, int elem){
  TLDE *p = l;
  while(p){
    if(p->info == elem) return p;
    p = p->prox;
  } 
  return NULL;
}

TLD* inicializa(){
  TLDE *novo = (TLSE*)malloc(sizeof(TLSED));
  novo->prim = NULL;
  novo->ultimo = NULL;
  novo->tam = 0;
  return novo;
}

