#include "TLPE.h"

void insere_ini(lista *l, int elem){
  elemento *novo = (elemento *) malloc(sizeof(elemento));
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
  elemento *novo = (elemento *) malloc(sizeof(elemento));
  novo->ant = l->ultimo;
  novo->prox = NULL;
  novo->info = elem;
  l->ultimo->prox = novo;
  l->ultimo = novo;
  l->tam++;
}

void imprime(lista *l){
  printf("\e[1m");
  if (l->sinal == -1) printf("-");
  if (l->sinal == 1) printf("+");
  elemento *p = l->prim;
  while(p){
    printf("%d", p->info);
    p = p->prox;
  }
  printf("\e[m\n");
}

void libera(lista *l){
  elemento *p = l->prim, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
  free(l);
}

void retira(lista *l, int elem){
  elemento *p = l->prim;
  if (l->tam == 1 && p->info == elem){
    l->prim = NULL;
    l->ultimo = NULL;
    l->tam = 0;
    return;
  }
  while((p)&&(p->info!=elem)){
    p = p->prox;
  }
  if (!p) return; // se p não existe não vai retornar nada
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
  l->tam = l->tam - 1;
}

elemento* busca(lista *l, int elem){
  elemento *p = l->prim;
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
  return novo;
}


void subtrai(lista *l1, lista *l2, lista *l3){
  int i, resultado, temp=0;
  elemento *p1 = l1->ultimo;
  elemento *p2 = l2->ultimo;
  for (i=0; i<l1->tam; i++){
    resultado = p1->info - p2->info - temp;
    if (resultado < 0) {
      temp = 1;
      resultado = 10-abs(resultado);
    }
    else temp=0;
    p1 = p1->ant;
    p2 = p2->ant;
    insere_ini(l3, resultado);
  }
}

void soma(lista *l1, lista *l2, lista *l3){
  int i, temp=0, resultado;
  elemento *p1 = l1->ultimo;
  elemento *p2 = l2->ultimo;
  for (i=0; i<l1->tam; i++){
    resultado = p1->info + p2->info + temp;
    if (resultado >= 10) {
      temp = 1;
      resultado = resultado%10;
    }
    else temp=0;
    p1 = p1->ant;
    p2 = p2->ant;
    insere_ini(l3, resultado);
    }
  if (temp==1) insere_ini(l3, 1);
}


lista* inicia_soma(lista *l1, lista *l2){
  lista *aux, *resp = inicializa();
  conserta_dif_de_tam(l1, l2);
  int respCmp = verifica_maior(l1, l2);
  if (respCmp == 1){
    resp->sinal = l2->sinal;
    aux = l1;
    l1 = l2;
    l2 = aux;
  }
  else{
    resp->sinal = l1->sinal;
  }
  if (l1->sinal == l2->sinal) { 
    soma(l1, l2, resp);
  }
  else{
    subtrai(l1, l2, resp);
  }
  return resp;
}

lista* inicia_subtracao(lista *l1, lista *l2){
  lista *aux, *resp = inicializa();
  if (l2->sinal==-1) l2->sinal = 1;
  else l2->sinal = -1;
  conserta_dif_de_tam(l1, l2);
  int respCmp = verifica_maior(l1, l2);
  if (respCmp == 1){
    resp->sinal = l2->sinal;
    aux = l1;
    l1 = l2;
    l2 = aux;
  }
  else{
    resp->sinal = l1->sinal;
  }
  if (l1->sinal != l2->sinal){
    subtrai(l1, l2, resp);
  }  
  else{
    soma(l1, l2, resp);
  }
  return resp;
}

lista *inicia_multiplicacao_ineficiente(lista *l1, lista *l2){
  lista *aux, *resp = inicializa();
  conserta_dif_de_tam(l1, l2);
  int respCmp = verifica_maior(l1, l2);
  if (respCmp == 1){
    aux = l1;
    l1 = l2;
    l2 = aux;
  }
  //imprime(l2);
  lista *auxl2 = l2;
  elemento *p2 = l2->prim;
  while(p2->info == 0){
    retira(auxl2, 0);
    p2 = p2->prox;
  }
  lista *contem1 = inicializa();
  insere_ini(contem1, 1);
  while (1){
    lista *tempresp = copia_e_remove_elementos_original(resp);
    conserta_dif_de_tam(l1, tempresp);
    soma(l1, tempresp, resp);
    libera(tempresp);
    lista *templ2 = copia_e_remove_elementos_original(auxl2);
    conserta_dif_de_tam(contem1, templ2);
    subtrai(templ2, contem1, auxl2);
    libera(templ2);
    while (auxl2->prim->info == 0){ //condição de parada (se l2 for igual a 0 e tam sai da função)
      if(auxl2->tam == 1){
      if (l1->sinal != auxl2->sinal) resp->sinal = -1;
      else resp->sinal = 1;
      libera(contem1);
      retira(auxl2, 0);
      return resp;
      }
    }
  }
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

void pega_elemento(lista *l, FILE *file){
  char str;
  str = getc(file);
  if (str == '+') l->sinal = 1;
  else l->sinal = -1;
  str = getc(file);
  while (str != '\n')
  {
      int temp = str - '0';
      insere_fin(l, temp);
      str = getc(file);
  }
}

int verifica_maior(lista *l1, lista *l2){
  elemento *p1, *p2;
  for (p1=l1->prim, p2=l2->prim; p1->prox != NULL; p1=p1->prox, p2=p2->prox){
    if (p1->info > p2->info){
      return -1;
    }
    if (p1->info < p2->info){
      return 1;
    }
  }
  return 0;
}

lista* copia_e_remove_elementos_original(lista *l){
  lista *resp = inicializa();
  elemento *aux = l->prim;
  int i;
  long int tam_total = l->tam;
  for(i=0; i<tam_total; i++){ // aqui retira os elementos de resp e passa pra tempresp
      insere_fin(resp, aux->info);
      retira(l, aux->info);
      aux = aux->prox;
  }
  return resp;
}

lista *inicia_multiplicacao(lista *l1, lista *l2){
  lista *aux, *soma_total = inicializa();
  long int i, j, k;
  conserta_dif_de_tam(l1, l2);
  int respCmp = verifica_maior(l1, l2);
  if (respCmp == 1){
    aux = l1;
    l1 = l2;
    l2 = aux;
  }
  elemento *p2 = l2->prim;
  while(p2->info == 0){ //retira os zeros a esquerda do menor
    if (l2->tam == 1 && p2->info == 0){
      insere_fin(soma_total, 0);
      return soma_total;
    }
    retira(l2, 0);
    p2 = p2->prox;
  }
  p2 = l2->ultimo;
  for (i=0; i<l2->tam; i++){
    lista *pivo = inicializa();
    lista *mult = inicializa();
    lista *tempresp = inicializa();
    insere_ini(pivo, p2->info);
    if(p2->info == 0)
      insere_ini(mult, 0);
    else if(p2->info == 1){
      elemento *p1 = l1->ultimo;
      for(k=0; k<l1->tam; k++){
        insere_ini(mult, p1->info);
        p1 = p1->ant;
      }
    }
    else mult = inicia_multiplicacao_ineficiente(l1, pivo);
    for (j=0; j<i; j++){
      insere_fin(mult, 0);
    }
    tempresp = copia_e_remove_elementos_original(soma_total);
    conserta_dif_de_tam(mult, tempresp);
    soma(mult, tempresp, soma_total);
    libera(pivo);
    libera(mult);
    libera(tempresp);
    p2 = p2->ant;
  }
  if (l1->sinal != l2->sinal) soma_total->sinal = -1;
  else soma_total->sinal = 1;
  return soma_total;
}