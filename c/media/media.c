/* 
   Autor: Ismael Felipe Ferreira dos Santos
          Instituto de Fisica,
          Universidade Federal de Alagoas
   E-mail: ismaellxd@gmail.com
   Copyright © 2019 MIT LICENCE
   GIT: https://ismaeldamiao.blogspot.com/fisicacomputacional
   Objetivo: Calcular a Media de dados de outros programas...
   Escrito em: 16 de novembro de 2019
   Midificacoes: 14 de marco de 2020, para funcionar com qualquer quantidade de
      colunas.
*/
/* Bibliotecas -------------------------------------------------------------- */
#include<stdio.h>
#include<stdlib.h>
/* Definicoes --------------------------------------------------------------- */
#define TRUE 1
#define FALSE 0
#define MAX 1000
/* Funcoes ------------------------------------------------------------------ */
int ContarLinhas(char NArquivo[]);
int ContarColunas(char NArquivo[]);
int fileExists(char NArquivo[]);
/* Funcao principal --------------------------------------------------------- */
int main(){
   int QuantidadeArquivos, QuantidadeColunas, arq, col, fim = FALSE;
   char NomeArquivoNomes[100], NomeResultado[100], command[2][100], 
      NomeArquivoMedia[MAX][100];
   double soma[MAX], valor;
   FILE *ArquivoNomes, *resultado, *ArquivoMedia[MAX];

   /* Cria um arquivo contendo os nomes de todos os arquivos de onde vamos tirar
   a media */
   printf("Qual o padrao do nome dos arquivo para fazer a media (*)? ");
   scanf("%s", command[1]);

   sprintf(NomeArquivoNomes, "tmp.main.txt");
   sprintf(NomeResultado, "%s.dat", command[1]);

   if(fileExists(NomeResultado)) remove(NomeResultado);

   sprintf(command[0], "ls -1 %s >> %s", command[1], NomeArquivoNomes);
   system(command[0]);

   resultado = fopen(NomeResultado, "w");

   /* Conta quantas linhas tem no arquivo, ou seja, quantos arquivos tem para
   tirar a media */
   QuantidadeArquivos = ContarLinhas(NomeArquivoNomes);
   if(QuantidadeArquivos > MAX){
      printf("Há demasiados arquivos.\nSaindo...\n");
      return 0;
   }
   /* Salva o nome de todos os arquivos para tirar a media */
   ArquivoNomes = fopen(NomeArquivoNomes, "r");
   for(arq = 0; arq < QuantidadeArquivos; ++arq)
      fscanf(ArquivoNomes, "%s", NomeArquivoMedia[arq]);
   fclose(ArquivoNomes);
   remove("tmp.main.txt");

   QuantidadeColunas = ContarColunas(NomeArquivoMedia[0]);

   /* Abre todos os arquivos para tirar a media */
   for(arq = 0; arq < QuantidadeArquivos; ++arq)
      ArquivoMedia[arq] = fopen(NomeArquivoMedia[arq], "r");

   for(;;){
      for(col = 0; col < QuantidadeColunas; ++col) soma[col] = 0;
      /* Guarda no vetor soma a soma, coluna a coluna, da n-esima linha de cada
      um dos arquivos */
      for(arq = 0; arq < QuantidadeArquivos; ++arq){
         for(col = 0; col < QuantidadeColunas; ++col){
            if( fscanf(ArquivoMedia[arq], "%lf", &valor) != EOF){
               soma[col] += valor;
            }else{
               fim = TRUE; 
               break;
            }
            if(fim) break;
         }
      }
      if(fim) break;
      for(col = 0; col < QuantidadeColunas; ++col)
         fprintf(resultado, "%18.8g ", soma[col]/QuantidadeArquivos);
      fprintf(resultado, "\n");
   }
   printf("Pronto!\n");
   return 0;
}

int ContarLinhas(char NArquivo[]){
   char ch;
   int QuantidadeLinhas = 0;
   FILE *Arquivo = fopen(NArquivo, "r");
   for(;(ch=fgetc(Arquivo)) != EOF;) if(ch == '\n') ++QuantidadeLinhas;
   fclose(Arquivo);
   return QuantidadeLinhas;
}
int ContarColunas(char NArquivo[]){
   char ch;
   int QuantidadeColunas = 0, Contar = TRUE;
   FILE *Arquivo = fopen(NArquivo, "r");
   for( ch=fgetc(Arquivo); ch != '\n'; ch=fgetc(Arquivo)){
      if(ch != ' ' && Contar){
         ++QuantidadeColunas;
         Contar = FALSE;
      }
      if(ch == ' ') Contar = TRUE;
   }
   fclose(Arquivo);
   return QuantidadeColunas;
}
int fileExists(char NArquivo[]){
   FILE *test = fopen(NArquivo, "r");
   if(test){
      fclose(test);
      return 1; /* existe */
   }else{
      return 0; /* nao existe */
   }
}