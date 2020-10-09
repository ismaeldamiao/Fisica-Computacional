/* ***
wget https://raw.githubusercontent.com/ismaeldamiao/avulsos/master/c/rotinas/exemplo_ran1.c
clang exemplo_ran1.c -o exemplo_ran1.o && ./exemplo_ran1.o
*** */
#include<stdio.h>

double ran1(long int*);

int main(void){
   long int semente = -9;
   FILE *f = fopen("aleatorios.txt", "w");

   for(int i = 0; i < 1999; ++i)
   fprintf(f, "%1.3g", ran1(&semente));

   return 0;
}

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran1(long int *idum){
   static long int iy=0, iv[NTAB];
   long int j, k;
   double temp;
   if(*idum <= 0 || !iy){ /* Inicialise */
      if (-(*idum) < 1) *idum = 1; /* Garantir que idum != 0 */
      else *idum = -(*idum);
      for(j = NTAB + 7; j >= 0; j--){
         k = (*idum) / IQ;
         *idum = IA * (*idum - k * IQ) - IR * k;
         if(*idum < 0) *idum += IM;
         if(j < NTAB) iv[j] = *idum;
      }
      iy = iv[0];
   }
   k = (*idum) / IQ; /* Comece aqui quando nao inicializado */
   *idum = IA * (*idum - k * IQ) - IR * k;
   if(*idum < 0) *idum += IM;
   j = iy / NDIV;
   iy = iv[j];
   iv[j] = *idum;
   if((temp=AM*iy) > RNMX) return RNMX;
   else return temp;
}
