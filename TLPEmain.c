#include "TLPE.h"
#include <string.h>

int main(void){
    int calculadora = 1;
    while (calculadora){
        printf("Escreva n1 \n");
        int n1;
        scanf("%d", &n1);
        printf("Escreva 1 para somar, 2 para diminuir e 3 para sair\n");
        int op;
        scanf("%d", &op);
        if (op==1){
            printf("Escreva n2 \n");
            int n2;
            scanf("%d", &n2);
            lista* lista3 = soma(n1,n2);
            free(lista3);
        }
        else if(op == 2){
            printf("Escreva n2 \n");
            int n2;
            scanf("%d", &n2);
            lista* lista3 = subtracao(n1,n2);
            free(lista3);
        }
        else if(op==3){
            calculadora = 0;
        }
        else{
            printf("Operação inválida \n");
        }
    }
    return 0;
}
