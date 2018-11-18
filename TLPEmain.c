#include "TLPE.h"


int main(void){

    int calculadora = 1;
    FILE *file;
    while (calculadora){
        file = fopen("leitura.txt", "r");
        if (file == NULL){
            printf("Arquivo não pode ser aberto \n");
        return 0;
        }
        lista *l1 = inicializa();
        pega_elementos(l1, file);
        imprime(l1);
        lista *l2 = inicializa();
        pega_elementos(l2, file);
        imprime(l2);
        lista *l3;
        printf("Escreva + para somar, - para diminuir e s para sair\n");
        char op;
        scanf(" %c", &op);
        if (op=='+'){
            l3 = soma(l2, l1); 
            free(l3);
        }
        else if(op == '-'){
            l3 = subtracao(l2, l1); 
            free(l3);
        }
        else if(op=='S' || op=='s'){
            calculadora = 0;
        }
        else{
            printf("Operação inválida \n");
        }
        printf("\n");
    }
    fclose(file);
    printf("Volte sempre :) \n");
    return 0;
}
