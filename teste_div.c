#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    int dividendo, divisor, dividendoLength, divisorLength, quociente, auxDiv, i, debug;
    scanf("%i", &dividendo);
    scanf("%i", &divisor);
    printf("%i\n", dividendo);
    printf("%i\n", divisor);
    dividendoLength = floor(log10(abs(dividendo))) + 1;
    printf("tamanho do dividendo: %i\n", dividendoLength);
    divisorLength = floor(log10(abs(divisor))) + 1;
    printf("tamanho do divisor: %i\n", divisorLength);
    auxDiv = floor(dividendo/10^(dividendoLength - divisorLength))+1;
    printf("valor do auxiliar da divisão: %i\n", auxDiv);
    quociente = 0;
    while (dividendoLength >= divisorLength)
    {
        i = 0;
        printf("calculando %i dígito do quociente\n", divisorLength);
        while (auxDiv > divisor)
        {
            auxDiv = auxDiv - divisor;
            printf("auxDiv dentro do euclidiano: %d\n", auxDiv);
            i= i + 1;
            printf("i : %i\n", i);
            scanf("%i\n", &debug);
        }
        quociente = quociente * 10 + i;
        divisorLength= i + 1;
        //auxDiv = auxDiv * 10 + floor(dividendo/10^(dividendoLength - divisorLength)) - floor(dividendo/10^(dividendoLength - divisorLength + 1))*10;
    printf("valor atual do quociente: %i\n", quociente);
    }
    printf("Quociente final: %d\n", quociente);
}