/* 
   Autor: Ismael Felipe Ferreira dos Santos
          Instituto de Fisica,
          Universidade Federal de Alagoas
   E-mail: ismaellxd@gmail.com
   Copyright © 2019 MIT LICENCE
   GIT: https://github.com/ismaeldamiao/ismael-damiao-repo
   Objetivo: Resolver o oscilador hamonico simples pelo metodo de Euler (cf. 
             Moyses Vol2 p42)
   Escrito em: 02 de agosto de 2019
*/
#include<stdio.h>
#include<math.h>

int main(void){
   int count = 0, countMax;
   double k, massa, posicao, velocidade, tempo, dt, omega2, aux[2];
   FILE *fPosicao = fopen("Posicao.dat", "w");

   /* Condicoes de contorno */
   massa = 1.0; /* Massa oscilante*/
   k = 1.0; /* Constante da mola*/
   omega2 = k / massa; /* Frenquenca angular */

   dt = 1.0e-6; /* Discreticaao dos pontos */
   posicao = 10.0; /* Posicao inicial da massa oscilante */
   velocidade = 0.0; /* Velocidade inicial da massa oscilante */

   countMax = (int)(0.1/dt); /* Serve para o arquivo nao ficar muito 'pesado'*/

   for(tempo = 0.0; tempo <= 30.0; tempo += dt){
      aux[0] = - omega2 * posicao;
      aux[1] = velocidade;
      /* Calculo para a velocidade em funcao do tempo */
      velocidade += aux[0] * dt;
      /* Calculo para  a posicao em funcao do tempo */
      posicao += aux[1] * dt;

      ++count;
      if(count > countMax){
         fprintf(fPosicao, "%g %g\n", tempo, posicao);
         count = 0;
      }
   }
   fclose(fPosicao);
   return 0;
}