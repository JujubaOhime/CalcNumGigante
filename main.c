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
        pega_elemento(l1, file);
        printf("O primeiro número é ");
        imprime(l1);
        lista *l2 = inicializa();
        pega_elemento(l2, file);
        printf("O segundo número é ");
        imprime(l2);
        lista *l3;
        printf("Escreva \e[33;1m+\e[m para somar, \e[33;1m-\e[m para diminuir e \e[31;1ms\e[m para sair.\n");
        char op;
        scanf(" %c", &op);
        if (op=='+'){
            l3 = inicia_soma(l1, l2);
            printf("O resultado é: ");
            imprime(l3); 
            free(l3);
        }
        else if(op == '-'){
            l3 = inicia_subtracao(l1, l2);
            printf("O resultado é: ");
            imprime(l3); 
            free(l3);
        }
        else if(op=='S' || op=='s'){
            calculadora = 0;
        }
        else{
            printf("Operação inválida \n");
        }
        printf("\n");
        fclose(file);
    }
    printf("Volte sempre :) \n");
    return 0;
}
