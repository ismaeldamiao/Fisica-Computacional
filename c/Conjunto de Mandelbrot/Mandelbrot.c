/* 
   Autor: Ismael Felipe Ferreira dos Santos
          Instituto de Fisica,
          Universidade Federal de Alagoas
   E-mail: ismaellxd@gmail.com
   Copyright © 2019 MIT LICENCE
   GIT: https://ismaeldamiao.blogspot.com/fisicacomputacional
   Objetivo: Gerar os pontos no plano complexo que pertencem ao congunto de 
             Mandelbrot.
   Escrito em: 14 de agosto de 2019
*/
/* Bibliotecas -------------------------------------------------------------- */
#include<stdio.h>
#include<math.h>
#include<complex.h>
/* Definicoes --------------------------------------------------------------- */
#define TRUE 1
#define FALSE 0
/* Funcao principal --------------------------------------------------------- */
int main(){
   double _Complex PontoC = -2.0 + -1.0 * I, sequencia = 0.0 + 0.0 * I;
   double Inclemento = 1.0e-3, i, j;
   int k, pertence;
   FILE *PontosConjunto;

   PontosConjunto = fopen("PontosConjuntoMandelbrot.dat", "w");

   for(i = -2.0; i <= 1.0; i += Inclemento){
      for(j = -1.0; j <= 1.0; j += Inclemento){
         /* Testar se nos primeiros 5000 termos da sequencia ela indica se ira 
         divergir*/
         PontoC = i + j * I; /* Teste com este ponto*/
         pertence = TRUE; /* Suponha que o ponto pertence ao conjunto */
         for(k = 1; k <= 5000; ++k){
            sequencia = cpow(sequencia, 2.0) + PontoC;
            if(cabs(sequencia) > 2.0){ /* Teste se ele de fato pertence */
               pertence = FALSE; /* Ele nao pertence :-( */
               break;
            }
         }
         /*Caso pertenca, escreva o ponto no arquivo*/
         if(pertence)
            fprintf(PontosConjunto, "%g %g\n", creal(PontoC), cimag(PontoC));
         sequencia = 0.0 + 0.0 * I;/*Zere a sequencia*/
      }
   }
}
