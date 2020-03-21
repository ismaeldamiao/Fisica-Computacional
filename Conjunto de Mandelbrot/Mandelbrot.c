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

#include<stdio.h>
#include<math.h>
#include<complex.h>

int main(){
   double _Complex PontoC = -2. + -1. * I, sequencia = 0. + 0. * I;
   double Inclemento = 1.e-3, i, j;
   int k, pertence = 1;
   FILE * PontosConjunto;

   PontosConjunto = fopen("PontosConjuntoMandelbrot.dat", "w");

   for(i = -2.; i <= 1.; i += Inclemento){
      for(j = -1.; j <= 1.; j += Inclemento){
         /* Testar se nos primeiros 5000 termos da sequencia ela indica se ira 
         divergir*/
         for(k = 1; k <= 5000; ++k){
            sequencia = cpow(sequencia, 2.) + PontoC;
            if(cabs(sequencia) > 2.){
               pertence = 0;/*A sequencia divergiu*/
               break;
            }
         }
         /*Caso nao tenha divergido, escreva o ponto no arquivo*/
         if(pertence == 1){
            fprintf(PontosConjunto, "%f %f\n", creal(PontoC), cimag(PontoC));
         }
         PontoC += Inclemento * I;/*Teste com outro ponto*/
         sequencia = 0. + 0. * I;/*Zere a sequencia*/
         pertence = 1;/*A sequencia ainda nao divergiu*/
      }
      PontoC = PontoC + Inclemento -2. * cimag(PontoC) * I;/*Teste com outro 
      ponto*/
   }
}