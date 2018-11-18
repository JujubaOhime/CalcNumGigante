#include "TLPE.h"

void insere_ini(lista *l, int elem){
  elementos *novo = (elementos *) malloc(sizeof(elementos));
  novo->ant = NULL;
  novo->info = elem;
  novo->prox = l->prim;
  l->tam++;
  if (l->prim == NULL) l->ultimo = novo;
  if (l->tam >= 2) l->prim->ant = novo;
  l->prim = novo;
//  if(l) l->ant = novo;
} 

void insere_fin(lista *l, int elem){
  if (l->tam == 0){
    insere_ini(l, elem);
    return;
  }
  elementos *novo = (elementos *) malloc(sizeof(elementos));
  novo->ant = l->ultimo;
  novo->prox = NULL;
  novo->info = elem;
  l->ultimo->prox = novo;
  l->ultimo = novo;
  l->tam++;
}

void imprime(lista *l){
  elementos *p = l->prim;
  if (l) printf("imprimindo a lista \n");
  while(p){
    printf("%d ", p->info);
    p = p->prox;
  }
  printf("\n"); 
}

void libera(lista *l){
  elementos *p = l->prim, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
  free(l);
}

void retira(lista *l, int elem){
  if (l->tam == 1){
    libera(l);
    return;
  }
  elementos *p = l->prim;
  while((p)&&(p->info!=elem)){
    p = p->prox;
  }
  if (!p) return; // se p não existe não vai retornar nada
  l->tam = l->tam - 1;
  if (!(p->ant) && l->tam>=3){ //se o elemento que quer retirar for o primeiro e tiver mais de 2 elementos
    l->prim = l->prim->prox; 
    p->prox->ant = NULL;
    }
    else if (!(p->ant) && l->tam==2){ //se o elemento que quer retirar for o primeiro e tiver 2 elementos
      l->prim = l->prim->prox;
      l->ultimo = l->prim;
      p->prox->ant = NULL;
    }
    else {
      if (l->ultimo == p){ // se o elemento que quer retirar for o último
        l->ultimo = p->ant;
        p->ant->prox = NULL;
      }
      else { //se o elemento que quer retirar não for o primeiro nem o último
      p->prox->ant = p->ant;
      p->ant->prox = p->prox;
      }
    }
  free(p);
}

elementos* busca(lista *l, int elem){
  elementos *p = l->prim;
  while(p && p->info != elem){
    if(p->info == elem) return p;
    p = p->prox;
  } 
  return p;
}

lista* inicializa_e_insere(){
  lista *novo = (lista*) malloc(sizeof(lista));
  novo->prim = NULL;
  novo->ultimo = NULL;
  novo->tam = 0;
  printf("escreva o número \n");
  int num, i;
  scanf(" %d", &num);
  if (num<0) novo->sinal = 1; // se for numero negativo, o sinal vai ter valor 1
  else novo->sinal = 0; // se for numero positivo, o sinal vai ter 0
  int tamanho = tam_int(num);
  char str[tamanho+1];
  sprintf(str, "%d", num);
  for (i=0; i<tamanho; i++){
        int temp = str[i] - '0'; //converte a str[i] em inteiro
        insere_fin(novo, temp);
  }
  return novo;
}

lista* inicializa(){
  lista *novo = (lista*) malloc(sizeof(lista));
  novo->prim = NULL;
  novo->ultimo = NULL;
  novo->tam = 0;
  return novo;
}

int tam_int(int numero){
  int tam = 1;
  while (numero/10 > 1){
    tam++;
    numero = numero/10;
  }
  return tam;
}

lista* soma(lista *l1, lista *l2){
  int diferenca_de_tam = abs(l1->tam - l2->tam);
  int i;
  if (l1->tam > l2->tam){
    for (i=0;i<diferenca_de_tam; i++){
      insere_ini(l2, 0);
    }
  }
  if (l2->tam > l1->tam){
    for (i=0;i<diferenca_de_tam; i++){
      insere_ini(l1, 0);
    }
  }
  int temp=0;
  lista *l3 = inicializa();
  for (i=0; i<l1->tam; i++){
    int resultado = l1->ultimo->info + l2->ultimo->info + temp;
    if (resultado >= 10) {
      temp = 1;
      resultado = resultado%10;
    }
    else temp=0;
    l1->ultimo = l1->ultimo->ant;
    l2->ultimo = l2->ultimo->ant;
    insere_ini(l3, resultado);
  }
  if (temp==1) insere_ini(l3, 1);
  printf("O resultado de n1 + n2 é: ");
  imprime(l3);
  return l3;
}