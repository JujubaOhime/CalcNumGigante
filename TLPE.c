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
  if (l->sinal == 1) printf("-");
  else printf("+");
  elementos *p = l->prim;
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



lista* inicializa(){
  lista *novo = (lista*) malloc(sizeof(lista));
  novo->prim = NULL;
  novo->ultimo = NULL;
  novo->tam = 0;
  novo->maior = 0;
  return novo;
}

lista* soma(lista *l1, lista *l2){
  if (l1->sinal != l2->sinal){ // se l1 tiver sinal diferente de l2 isso vai ser uma subtração
    if (l2->sinal == 1) l2->sinal = 0; // a troca de sinal aqui é porque quando vai pra subtração troca o sinal 
    else l2->sinal = 1; // e para deixar intocado deve trocar aqui
    return subtracao(l1, l2);
  }
  conserta_dif_de_tam(l1, l2);
  int temp=0, i;
  lista *l3 = inicializa();
  conserta_dif_de_tam(l1, l2);
  verifica_maior(l1, l2);
  lista *aux;
  if (l2->maior == 1){
    aux = l1;
    l1 = l2;
    l2 = aux;
  }
  printf("entrou em soma \n");
  printf("l1->sinal: %d", l1->sinal);
  printf("l2->sinal: %d", l2->sinal);
  verifica_maior(l1, l2);
  l3->sinal = l1->sinal; // l3 vai ter osinal do maior na operação que é o l1 sempre já que verificamos
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
  printf("O resultado é: ");
  imprime(l3);
  libera(l1);
  libera(l2);
  return l3;
}

lista* subtracao(lista *l1, lista *l2){
  if (l2->sinal == 1) l2->sinal = 0;
  else l2->sinal = 1; 
  if (l1->sinal == l2->sinal){// se ambos tiverem mesmo sinal isso vai ser uma soma logo retornar soma
    return soma(l1, l2);
  }
  conserta_dif_de_tam(l1, l2);
  verifica_maior(l1, l2);
  lista *aux;
  int temp=0, i;
  printf("l1->sinal: %d", l1->sinal);
  printf("l2->sinal: %d", l2->sinal);
  lista *l3 = inicializa(); 
  l3->sinal = l1->sinal; // l3 vai ter osinal do maior na operação que é o l1 sempre já que verificamos
  for (i=0; i<l1->tam; i++){
      int resultado = l1->ultimo->info - l2->ultimo->info - temp;
      if (resultado < 0) {
        temp = 1;
        resultado = 10-abs(resultado);
      }
      else temp=0;
      l1->ultimo = l1->ultimo->ant;
      l2->ultimo = l2->ultimo->ant;
      insere_ini(l3, resultado);
  }
  printf("O resultado é: ");
  imprime(l3);
  libera(l1);
  libera(l2);
  return l3;
  }


void conserta_dif_de_tam(lista *l1, lista *l2){
  int diferenca_de_tam = abs(l1->tam - l2->tam); //pegando a diferença de tamanho entre os numeros para igualar o numero de casas
  int i;
  if (l1->tam > l2->tam){ // igualando aqui o numero de casas dos números
    for (i=0;i<diferenca_de_tam; i++){
      insere_ini(l2, 0);
    }
  }
  if (l2->tam > l1->tam){ // igualando aqui o numero de casas dos números
    for (i=0;i<diferenca_de_tam; i++){
      insere_ini(l1, 0);
    }
  }

}

void pega_elementos(lista *l, FILE *file){
  char str;
  str = getc(file);
  if (str == '+') l->sinal = 0;
  else l->sinal = 1;
  str = getc(file);
  while (str != '\n')
  {
      int temp = str - '0';
      insere_fin(l, temp);
      str = getc(file);
  }
}

void verifica_maior(lista *l1, lista *l2){
  int temp = 0;
  conserta_dif_de_tam(l1, l2);
  int i;
  elementos *p1 = l1->prim;
  elementos *p2 = l2->prim;
  for (i=0; i<l1->tam; i++){
    if (p1->info > p2->info){
      l1->maior = 1;
      break;
    }
    if (p1->info < p2->info){
      l2->maior = 1;
      break;
    }
    p1 = p1->prox;
    p2 = p2->prox;
  }
}