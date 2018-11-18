#include "TLPE.h"
#include <string.h>

int main(void){
    lista* lista1 = inicializa_e_insere();
    imprime(lista1);
    lista* lista2 = inicializa_e_insere();
    imprime(lista2);
    lista* lista3 = soma(lista1, lista2);
    libera(lista1);
    libera(lista2);
    return 0;
}
