/* ***
wget https://raw.githubusercontent.com/ismaeldamiao/avulsos/master/c/rotinas/exemplo_ran1.c

wget -qO ran1.c https://github.com/ismaeldamiao/avulsos/raw/master/c/rotinas/ran1.c
clang exemplo_ran1.c -o exemplo_ran1.o && ./exemplo_ran1.o
*** */
#include <stdio.h>
#include "ran1.c"

int main(void){
   long int semente = -9L;
   FILE *f = fopen("exemplo_ran1.txt", "w");

   for(int i = 0; i < 1999; ++i)
   fprintf(f, "%1.3g", ran1(&semente));

   return 0;
}
