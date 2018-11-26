#include "TLPE.h"


int main(void){

    int calculadora = 1;
    FILE *file;
    while (calculadora){
        printf("\e[34;1;2mBem-vindo à Calculadora de Números IN FI NI TOS!\e[m\n\n");

        file = fopen("leitura.txt", "r");
        if (file == NULL){
            printf("Arquivo não pode ser aberto \n");
            return 0;
        }
        lista *l1 = inicializa();
        lista *l2 = inicializa();
        lista *l3 = inicializa();
        pega_elemento(l1, file);
        pega_elemento(l2, file);
        printf("O primeiro número é ");
        imprime(l1);
        printf("O segundo número é ");
        imprime(l2);
        printf("\nEscreva \e[33;1m+\e[m para somar, \e[33;1m-\e[m para diminuir, \e[33;1m*\e[m para multiplicar, \e[33;1m/\e[m para dividir e \e[31;1ms\e[m para sair: ");
        char op;
        scanf(" %c", &op);
        printf("\ec");
        if (op == '+'){
            l3 = inicia_soma(l1, l2);
            printf("\nO resultado é: ");
            imprime(l3); 
        }
        else if(op == '-'){
            l3 = inicia_subtracao(l1, l2);
            printf("\nO resultado é: ");
            imprime(l3); 
        }
        else if(op == '*'){
            l3 = inicia_multiplicacao(l1, l2);
            printf("\nO resultado é: ");
            imprime(l3);
        }
        else if(op == '/'){
            if(l2->tam == 1 && l2->prim->info == 0){
                printf("\nesta divisão não pode ser realizada \n");
            }else{
            l3 = inicia_divisao(l1, l2);
            printf("\nO resultado é: ");
            imprime(l3);
            }
        }
        else if(op=='S' || op=='s'){
            calculadora = 0;
        }
        else{
            printf("Operação inválida \n");
        }
        printf("\n");
        libera(l1);
        libera(l2);
        libera(l3);
        fclose(file);
    }
    printf("Volte sempre :) \n");
    return 0;
}
