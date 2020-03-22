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
      S, /* Sucetiveis */
      I, /* Infectados */
      R, /* Removidos (Curados + Mortos) */
      N, /* Populacao total */
      R0, /* Ritmo basico de reproducao */
      dt = 1.0e-2, /* Discretizacao para iteracao com euler */
      t, /* Evolucao temporal */
      Tmax, /* Periodo obsevado */
      pico = 0.0,
      aux[4]
   ;
   int count = 0, lim;
   char NS[200], NI[200], NR[200], sitio[15], plotSetS[200],
      plotSetI[200], plotSetR[200], cmd[30];
   FILE *fS,*fI, *fR;

   /* --------------------------------------------------------------------------
   Valores comumente referentes ah pandemia de COVID-19 ao redor do mundo
   -------------------------------------------------------------------------- */
   gamma = 0.04;
   /* --------------------------------------------------------------------------
   Valores locais, isto eh, do lugar de onde se deseja fazer a simulacao
   -------------------------------------------------------------------------- */
   sprintf(sitio, "Maceio");
   N = 1012382.0; // Populacao local em numeros absolutos
   I = 7.0;// Eh preciso informar a populacao infectada no inicio da iteracao
   R0 = 5.2; // Informe o Ritmo basico de reproducao
   R = 0.0; // Populacao removida no inicio da iteracao
   Tmax = 160.0; // Observar ate 160 dias
   beta = R0 * gamma;
   S = N - I - R;
   /* ----------------------------------------------------------------------- */
   lim = (int)(1.0e-4/dt);
   sprintf(plotSetS, "with linespoints lc rgb 'blue' pt 7 ps .3 title 'suscetíveis'");
   sprintf(plotSetI, "with linespoints lc rgb 'black' pt 7 ps .3 title 'Infectados'");
   sprintf(plotSetR, "with linespoints lc rgb 'brown' pt 7 ps .3 title 'Removidos'");

   //sprintf(NS, "S.dat");
   //fS = fopen(NS, "w");
   sprintf(NI, "I.dat");
   fI = fopen(NI, "w");
   //sprintf(NR, "R.dat");
   //fR = fopen(NR, "w");

   for(t = dt; t <= Tmax; t += dt){
      aux[0] = -beta * I * S / N;
      aux[2] = gamma * I;
      aux[1] = -aux[0] - aux[2];

      S += aux[0] * dt;
      I += aux[1] * dt;
      R += aux[2] * dt;

      if(I > pico) pico = I;

      ++count;
      if(count > lim){
         //fprintf(fS, "%g %g\n", t, S);
         fprintf(fI, "%g %g\n", t, I);
         //fprintf(fR, "%g %g\n", t, R);
         count = 0;
      }
   }
   //fclose(fS);
   fclose(fI);
   //fclose(fR);
   /* Abrir o GNUPlot, sendo o arquimento o nome do arquivo de saida */
   //gnuplotOpen("%s_gamma%g_beta%g.png", sitio, gamma, beta);
   gnuplotOpen("%s.png", sitio);
   /* Comando do GNUPlot */
   gnuplotPrintf("set xlabel 'Tempo (dias)'");
   gnuplotPrintf("set ylabel 'População (%%)'");
   gnuplotPrintf("set title '%s,  γ=%g, β=%g'", sitio, gamma, beta);
   //gnuplotPrintf("plot '%s' %s, '%s' %s, '%s' %s",
   //   NS, plotSetS, NI, plotSetI, NR, plotSetR);
   gnuplotPrintf("plot '%s' %s", NI, plotSetI);
   gnuplotClose();
   //sprintf(cmd, "rm %s %s %s", NS, NI, NR);
   //system(cmd);

   printf("Taxa de infecção β: %2.2lf\n", beta);
   printf("Pessoas que evitaram a infecção: %d\n", (int)S);
   printf("Pessoas infectadas: %d\n", (int)I);
   printf("Pessoas removidas: %d\n", (int)R);
   printf("Pessoas infectadas no pico da doença: %d\n", (int)pico);
}
