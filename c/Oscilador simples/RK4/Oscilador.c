/* 
   Autor: Ismael Felipe Ferreira dos Santos
          Instituto de Fisica,
          Universidade Federal de Alagoas
   E-mail: ismaellxd@gmail.com
   Copyright © 2020 MIT LICENCE
   GIT: https://github.com/ismaeldamiao/ismael-damiao-repo
   Objetivo: Resolver o oscilador hamonico simples pelo metodo de Euler (cf. 
             Moyses Vol2 p42)
   Escrito em: 28 de marco de 2020
*/
#include<stdio.h>
#include<math.h>
int main(void){
   int count = 0, countMax;
   double k, massa, posicao, velocidade, tempo, dt, dt2, dt6, kx[4], kv[4],
      omega2;
   FILE *fPosicao = fopen("Posicao.dat", "w");

   /* Condicoes de contorno */
   massa = 1.0; /* Massa oscilante*/
   k = 1.0; /* Constante da mola*/
   omega2 = k / massa; /* Frenquenca angular */

   dt = 1.0e-6; /* Discreticaao dos pontos */
   dt2 = dt * 0.5;
   dt6 = dt / 6.0;
   posicao = 10.0; /* Posicao inicial da massa oscilante */
   velocidade = 0.0; /* Velocidade inicial da massa oscilante */

   countMax = (int)(0.1/dt); /* Serve para o arquivo nao ficar muito 'pesado'*/

   for(tempo = 0.0; tempo <= 30.0; tempo += dt){
      kv[0] = -omega2 * posicao;
      kx[0] = velocidade;

      kv[1] = kv[0] + kv[0] * dt2;
      kx[1] = velocidade + kx[0] * dt2;

      kv[2] = kv[0] + kv[1] * dt2;
      kx[2] = velocidade + kx[1] * dt2;

      kv[3] = kv[0] + kv[2] * dt2;
      kx[3] = velocidade + kx[2] * dt;
      /* Calculo para a velocidade em funcao do tempo */
      velocidade += (kv[0] + 2.0 * kv[1] + 2.0 * kv[2] + kv[3]) * dt6;
      /* Calculo para  a posicao em funcao do tempo */
      posicao += (kx[0] + 2.0 * kx[1] + 2.0 * kx[2] + kx[3]) * dt6;

      ++count;
      if(count > countMax){
         fprintf(fPosicao, "%g %g\n", tempo, posicao);
         count = 0;
      }
   }
   fclose(fPosicao);
   return 0;
}
