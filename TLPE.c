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

lista* inicializa_e_insere(int num){
  lista *novo = (lista*) malloc(sizeof(lista));
  novo->prim = NULL;
  novo->ultimo = NULL;
  novo->tam = 0;
  int i;
  if (num<0) novo->sinal = 1; // se for numero negativo, o sinal vai ter valor 1
  else novo->sinal = 0; // se for numero positivo, o sinal vai ter 0
  int tamanho = tam_int(num);
  char str[tamanho+2];
  sprintf(str, "%d", abs(num));
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
  int num = abs(numero);
  while (abs(num/10) >= 1){
    tam++;
    num = num/10;
  }
  return tam;
}

lista* soma(int num1,int num2){
  if (abs(num2) > abs(num1)){
    int temp = num1;
    num1 = num2;
    num2 = temp;
  }
  lista *l1 = inicializa_e_insere(num1);
  lista *l2 = inicializa_e_insere(num2);
  if (l1->sinal != l2->sinal){ // se l1 tiver sinal diferente de l2 isso vai ser uma subtração!
    return subtracao(num1, num2);
  }
  conserta_dif_de_tam(l1, l2);
  int temp=0, i;
  lista *l3 = inicializa();
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
  printf("O resultado de é: ");
  if (l3->sinal == 1) printf("-");
  imprime(l3);
  libera(l1);
  libera(l2);
  return l3;
}

lista* subtracao(int num1, int num2){
  num2 = -num2; // como é uma subtração, o segundo elemento vai trocar o sinal
  if (abs(num2) > abs(num1)){
    int temp = num1;
    num1 = num2;
    num2 = temp;
  }
  lista *l1 = inicializa_e_insere(num1);
  lista *l2 = inicializa_e_insere(num2);
  conserta_dif_de_tam(l1, l2);
  if (l1->sinal == l2->sinal) return soma(num1, num2); // se ambos tiverem mesmo sinal isso vai ser uma soma logo retornar soma
  int temp=0, i;
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
  if (l3->sinal) printf("-");
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
