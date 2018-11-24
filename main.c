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
        lista *l2 = inicializa();
        lista *l3 = inicializa();
        pega_elemento(l1, file);
        pega_elemento(l2, file);
        //conserta_dif_de_tam(l1, l2);
        //soma(l1, l2, l3);
        //imprime(l3);
/*        int i;
        elemento *p1 = l1->prim;
        printf("o tamanhode l1 é %d \n", l1->tam);
        imprime(l1);
        long int a = l1->tam;
        for(i=0; i<a; i++){
            printf("o i é %d \n", i);
            printf("p1->info é %d \n", p1->info);
            retira(l1, p1->info);
            imprime(l1);
            p1 = p1->prox;
        }
        */

        printf("O primeiro número é ");
        imprime(l1);
        printf("O segundo número é ");
        imprime(l2);
        printf("Escreva \e[33;1m+\e[m para somar, \e[33;1m-\e[m para diminuir, * para multiplicar, m para multiplicar e \e[31;1ms\e[m para sair: ");
        char op;
        scanf(" %c", &op);
        printf("\ec");
        if (op == '+'){
            l3 = inicia_soma(l1, l2);
            printf("O resultado é: ");
            imprime(l3); 
        }
        else if(op == '-'){
            l3 = inicia_subtracao(l1, l2);
            printf("O resultado é: ");
            imprime(l3); 
        }
        else if(op == '*'){
            l3 = inicia_multiplicacao_ineficiente(l1, l2);
            printf("O resultado é: ");
            imprime(l3);
        }
        else if(op == 'm'){
            l3 = inicia_multiplicacao(l1, l2);
            printf("O resultado é: ");
            imprime(l3);
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
