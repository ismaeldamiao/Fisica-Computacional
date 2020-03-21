/* 
   Autor: Ismael Felipe Ferreira dos Santos
          Instituto de Fisica,
          Universidade Federal de Alagoas
   E-mail: ismaellxd@gmail.com
   Copyright © 2019 MIT LICENCE
   GIT: https://ismaeldamiao.blogspot.com/fisicacomputacional
   Objetivo: Programa para calcular todos los numeros primos hasta p segun el 
             crivo de Eratostenes
*/
#include<stdio.h>

int main(){
// Declaraciones
   int i, j, p;
// Comandos ejecutables
   printf("¡Bienvenido al programa crivo!\nPorfavor digite el mayor numero de");
   printf(" la lista donde seran bucados los numeros primos: ");
   scanf("%d", &p);
   int v[p];
   for(i = 0; i < p; i++){ /* Escribe todos los numeros de 1 hasta p en el
                                                                        vetor */
      v[i] = i + 1;
   }
   printf("Los numero primos hasta %d son \n", p);
   for(i = 2; i <= p; i++){
      if(v[i-1] != 0){
         printf("%d ", v[i-1]); // Escribe el numero no quitado de la lista
         for(j = i; j <= p; j=j+i){ // Quita los multiplos de este de la lista
            v[j-1]=0;
         }
      }
   }
   printf("\n");
   return 0;
}