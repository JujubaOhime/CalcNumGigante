#include <stdio.h>

void pega_elementos(FILE *file){
    char ch;
    ch = getc(file);
     while (ch != '\n')
     {
        printf("%c",ch);
        ch = getc(file);
     }

}
int main()
{
   char ch;
   FILE *fp;
   if (fp = fopen("leitura.txt", "r"))
   {
    pega_elementos(fp);
     printf("\n saiu \n");
     pega_elementos(fp);
     fclose(fp);
     return 0;
   }
   return 1;
}