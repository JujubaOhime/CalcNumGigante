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
  long unsigned int i;
  int resultado, temp=0;
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
  long unsigned int i;
  int temp=0, resultado;
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
  if (respCmp == -1){
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
  if (respCmp == -1){
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

lista *inicia_multiplicacao_ineficiente(lista *base_soma, lista *qtd_somas){
  lista *aux, *resp = inicializa();
  conserta_dif_de_tam(base_soma, qtd_somas);
  int respCmp = verifica_maior(base_soma, qtd_somas);
  if (respCmp == -1){
    aux = base_soma;
    base_soma = qtd_somas;
    qtd_somas = aux;
  }
  //imprime(qtd_somas);
  elemento *p2 = qtd_somas->prim;
  while(p2->info == 0){
    retira(qtd_somas, 0);
    p2 = p2->prox;
  }
  lista *decremento = inicializa();
  insere_ini(decremento, 1);
  lista *soma_parcial, *aux_decremento;
  while (1){
    soma_parcial = copia_e_remove_elementos_original(resp);
    conserta_dif_de_tam(base_soma, soma_parcial);
    soma(base_soma, soma_parcial, resp);
    libera(soma_parcial);

    aux_decremento = copia_e_remove_elementos_original(qtd_somas);
    conserta_dif_de_tam(decremento, aux_decremento);
    subtrai(aux_decremento, decremento, qtd_somas);
    libera(aux_decremento);
    
    while (qtd_somas->prim->info == 0){ //condição de parada (se l2 for igual a 0 e tam sai da função)
      if(qtd_somas->tam == 1){
      if (base_soma->sinal != qtd_somas->sinal) resp->sinal = -1;
      else resp->sinal = 1;
      libera(decremento);
      retira(qtd_somas, 0);
      return resp;
      }
    }
  }
}

void conserta_dif_de_tam(lista *l1, lista *l2){
  long unsigned int diferenca_de_tam = abs(l1->tam - l2->tam); //pegando a diferença de tamanho entre os numeros para igualar o numero de casas
  long unsigned int i;
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

void retira_zeros_esquerda(lista *numero){
  elemento *p = numero->prim;
  while(!p->info){
    if (numero->tam == 1) return;
    retira(numero, 0);
    p = p->prox;
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
  if (l1->tam < l2->tam) return -1;
  if (l1->tam > l2->tam) return 1;
  for (p1=l1->prim, p2=l2->prim; p1 != NULL; p1=p1->prox, p2=p2->prox){
    if (p1->info < p2->info){
      return -1;
    }
    if (p1->info > p2->info){
      return 1;
    }
  }
  return 0;
}

lista* copia_e_remove_elementos_original(lista *l){
  lista *resp = inicializa();
  elemento *aux = l->prim;
  long unsigned int i;
  long unsigned int tam_total = l->tam;
  for(i=0; i<tam_total; i++){ // aqui retira os elementos de resp e passa pra tempresp
      insere_fin(resp, aux->info);
      retira(l, aux->info);
      aux = aux->prox;
  }
  return resp;
  free(aux);
}

lista *inicia_multiplicacao(lista *l1, lista *l2){
  lista *aux, *soma_total = inicializa();
  long unsigned int i, j, k;
  conserta_dif_de_tam(l1, l2);
  int respCmp = verifica_maior(l1, l2);
  if (respCmp == -1){
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

lista *inicia_divisao(lista *dividendo, lista *divisor){
  lista *quociente = inicializa();
  long unsigned int i;
  int respCmp = verifica_maior(dividendo, divisor); //se divisor for maior o quociente é 0 e acaba aqui
  if (respCmp == -1){
    insere_fin(quociente, 0);
    return quociente;
  }
  elemento* elementoDividendo = dividendo->prim;
  lista *auxDividendo = inicializa(); 
  for(i=0; i<divisor->tam; i++){ // pega o auxdividendo de tamanho igual do divisor;
    insere_fin(auxDividendo, elementoDividendo->info);
    elementoDividendo = elementoDividendo->prox;
  }
  respCmp = verifica_maior(divisor, auxDividendo); // se ainda assim o auxdividendo for menor que o divisor inserir o próximo numero de dividendo nele
  if(respCmp == 1){
    insere_fin(auxDividendo, elementoDividendo->info);
    elementoDividendo = elementoDividendo->prox;
  }
  int proxDigitoQuociente;
  long unsigned int tamDoDivisor = divisor->tam;
  if(dividendo->sinal != divisor->sinal) quociente->sinal = -1; // da o sinal do quociente
  else quociente->sinal = 1;
  while(dividendo->tam >= tamDoDivisor){ 
    proxDigitoQuociente = 0;
    respCmp = verifica_maior(auxDividendo, divisor);
    while(respCmp != -1){ //enquanto o auxiliar divisor for maior ou igual ao divisor...
      lista* auxDividendoTemp = inicializa(); //auxDividendotemp vai carregar o que auxDividendo faz
      auxDividendoTemp = copia_e_remove_elementos_original(auxDividendo);
      conserta_dif_de_tam(auxDividendoTemp, divisor); //para subtrair divisor de auxDividendotemp deve-se igualar seus tamanhos
      subtrai(auxDividendoTemp, divisor, auxDividendo);
      retira_zeros_esquerda(divisor);
      libera(auxDividendoTemp);//auxdividendoTemp já carregou a informação de dividendotemp e subtraiu portanto podemos já retira-lo
      retira_zeros_esquerda(auxDividendo);
      respCmp = verifica_maior(auxDividendo, divisor); //compara se ainda o auxiliar é maior ou igual ao divisor
      proxDigitoQuociente++; 
    }
    insere_fin(quociente, proxDigitoQuociente);
    tamDoDivisor++;
    if (elementoDividendo){
      insere_fin(auxDividendo, elementoDividendo->info);
      elementoDividendo = elementoDividendo->prox;
    }
  }
  return quociente;
}
