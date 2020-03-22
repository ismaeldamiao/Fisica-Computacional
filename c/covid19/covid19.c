/* 
   Autor: 
      Ismael Felipe Ferreira dos Santos
      Instituto de Fisica,
      Universidade Federal de Alagoas
   E-mail: ismaellxd@gmail.com
   Copyright © 2020 MIT LICENCE
   GIT: https://ismaeldamiao.blogspot.com/fisicacomputacional
   Objetivo:
      Simular o desenvolvimento da COVID-19 apartir do modelo SIR
   Dada: 20 de marco de 2020
*/
/* Bibliotecas -------------------------------------------------------------- */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<stdarg.h> /* va_list va_start() */
#include<stdlib.h> /* system() */
/* Variaveis globais -------------------------------------------------------- */
FILE *gnutmp;
/* Funcoes ------------------------------------------------------------------ */
void gnuplotPrintf(const char *format, ...){
   va_list arg;
   va_start(arg, format);
   vfprintf (gnutmp, format, arg);
   fprintf(gnutmp, "\n");
   va_end(arg);
   return;
}
void gnuplotOpen(const char out[], ...){
   int font = 18;
   va_list arg;
   va_start(arg, out);
   gnutmp = fopen("tmp.gnuplotOpen.gnuplot", "w");
   /* Configuracoes padrao */
   gnuplotPrintf("#!/usr/bin/env gnuplot");
   gnuplotPrintf("set terminal png size 1280, 720 font ',%d'", font);
   fprintf(gnutmp, "set output '");
   vfprintf (gnutmp, out, arg);
   gnuplotPrintf("'");
   gnuplotPrintf("set encoding utf8");
   gnuplotPrintf("set key box right center font ',%d'", font);
   return;
}
void gnuplotClose(void){
   gnuplotPrintf("exit");
   fclose(gnutmp);
   system("gnuplot tmp.gnuplotOpen.gnuplot");
   remove("tmp.gnuplotOpen.gnuplot");
   return;
}
/* Funcao prinpipal --------------------------------------------------------- */
int main(void){
   double
      gamma, /* taxa de recuperacao */
      beta, /* taxa de infeccao */
      mu, /* taxa de mortes */
      S = 1.0, /* Sucetiveis */
      I, /* Infectados */
      R = 0.0, /* Recuperados (Curados + Mortos) */
      C, /* Curados */
      M, /* Mortos */
      N, /* Populacao total */
      R0, /* Ritmo basico de reproducao */
      dt = 1.0e-2, /* Discretizacao para iteracao com euler */
      t, /* Evolucao temporal */
      Tmax, /* Periodo obsevado */
      pico = 0.0,
      aux[4]
   ;
   int count = 0, lim;
   char NS[200], NI[200], NC[200], NM[200], sitio[15], plotSetS[200],
      plotSetI[200], plotSetC[200], plotSetM[200], cmd[30];
   FILE *fS,*fI, *fC, *fM;

   /* --------------------------------------------------------------------------
   Valores comumente referentes ah pandemia de COVID-19 ao redor do mundo
   -------------------------------------------------------------------------- */
   gamma = 0.04;
   mu = 1.0e-8; // Na Italia: mu = 0.04;
   /* --------------------------------------------------------------------------
   Valores locais, isto eh, do lugar de onde se deseja fazer a simulacao
   -------------------------------------------------------------------------- */
   sprintf(sitio, "Maceio");
   N = 1012382.0; // Populacao local em numeros absolutos
   I = 7.0;// Eh preciso informar a populacao infectada no inicio da iteracao
   R0 = 5.2; // Informe o Ritmo basico de reproducao
   Tmax = 150.0; // Observar ate 150 dias
   beta = R0 * gamma;
   //beta = 0.38;
   I = I/N;
   /* ----------------------------------------------------------------------- */
   lim = (int)(1.0e-4/dt);
   sprintf(plotSetS, "with linespoints lc rgb 'blue' pt 7 ps .3 title 'suscetíveis'");
   sprintf(plotSetI, "with linespoints lc rgb 'black' pt 7 ps .3 title 'Infectados'");
   sprintf(plotSetC, "with linespoints lc rgb 'brown' pt 7 ps .3 title 'Curados'");
   sprintf(plotSetM, "with linespoints lc rgb 'red' pt 7 ps .3 title 'Mortos'");

   sprintf(NS, "S.dat");
   fS = fopen(NS, "w");
   sprintf(NI, "I.dat");
   fI = fopen(NI, "w");
   sprintf(NC, "R.dat");
   fC = fopen(NC, "w");
   sprintf(NM, "M.dat");
   fM = fopen(NM, "w");

   for(t = dt; t <= Tmax; t += dt){
      aux[0] = -beta * I * S;
      aux[1] = beta * I * S - gamma * I;
      aux[2] = gamma * I;

      S += aux[0] * dt;
      I += aux[1] * dt;
      R += aux[2] * dt;

      C = (1 - mu) * R;
      M = mu * R;

      if(I > pico) pico = I;

      ++count;
      if(count > lim){
         //fprintf(fS, "%g %g\n", t, S * 100.0);
         //fprintf(fI, "%g %g\n", t, I * 100.0);
         //fprintf(fC, "%g %g\n", t, C * 100.0);
         //fprintf(fM, "%g %g\n", t, M * 100.0);
         //fprintf(fS, "%g %g\n", t, S * N);
         fprintf(fI, "%g %g\n", t, I * N);
         //fprintf(fC, "%g %g\n", t, C * N);
         //fprintf(fM, "%g %g\n", t, M * N);
         count = 0;
      }
      //if(fabs(t - 60.0) <= 1.5) gamma = droga;
   }
   fclose(fS);
   fclose(fI);
   fclose(fC);
   fclose(fM);
   //gnuplotOpen("%s_gamma%g_beta%g.png", sitio, gamma, beta);
   gnuplotOpen("%s.png", sitio);
   gnuplotPrintf("set xlabel 'Tempo (dias)'");
   gnuplotPrintf("set ylabel 'População (%%)'");
   gnuplotPrintf("set title '%s,  γ=%g, β=%g'", sitio, gamma, beta);
   //gnuplotPrintf("plot '%s' %s, '%s' %s, '%s' %s, '%s' %s",
   //   NS, plotSetS, NI, plotSetI, NC, plotSetC, NM, plotSetM);
   //gnuplotPrintf("plot '%s' %s, 'confirmados.dat' with linespoints lc rgb 'red' pt 7 ps .3 title 'Confirmados'", NI, plotSetI);
   gnuplotPrintf("plot '%s' %s", NI, plotSetI);
   gnuplotClose();
   sprintf(cmd, "rm %s %s %s %s", NS, NI, NC, NM);
   //system(cmd);

   printf("Taxa de infecção β: %2.2lf\n", beta);
   printf("Porcentagem de pessoas que evitaram a infecção: %2.0lf%%\n", S * 100.0);
   printf("Porcentagem de pessoas infectadas: %2.0lf%%\n", I * 100.0);
   printf("Porcentagem de pessoas removidas: %2.0lf%%\n\n", R * 100.0);
   printf("Porcentagem de pessoas infectadas no pico da doença: %2.0lf%%\n", pico * 100.0);
   printf("Total de pessoas mortas: %d\n", (int)(N * M));
}
