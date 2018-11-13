#include "TLDE.h"

void insere_ini(TLD *l, int elem){
  TLDE *novo = (TLDE *) malloc(sizeof(TLDE));
  novo->ant = NULL;
  novo->info = elem;
  novo->prox = l->prim;
  l->tamanho++;
  if (l->prim == NULL) l->ultimo = novo;
  l->prim = novo;
//  if(l) l->ant = novo;
} 

void insere_fin(TLD *l, int elem){
  TLDE *novo = (TLDE *) malloc(sizeof(TLDE));

}

void imprime(TLD *l){
  TLDE *p = l->prim;
  while(p){
    printf("% d ", p->info);
    p = p->prox;
  } 
}

void libera(TLD *l){
  TLDE *p = l->prim, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
  free(l);
}

void retira(TLD *l, int elem){
  TLDE *p = busca(l, elem);
  if(!p) return l;
  if(p == l){ 
    l = l->prim;
  }
  if (p == l->ultimo) l->ultimo = p;
  else p->ant->prox = p->prox;
  if(p->prox) p->prox->ant = p->ant;
  free(p);
}

TLDE* busca(TLD *l, int elem){
  TLDE *p = l->prim;
  while(p && p->info != elem){
    if(p->info == elem) return p;
    p = p->prox;
  } 
  return p;
}

TLD* inicializa(){
  TLDE *novo = (TLSE*)malloc(sizeof(TLSED));
  novo->prim = NULL;
  novo->ultimo = NULL;
  novo->tam = 0;
  return novo;
}

