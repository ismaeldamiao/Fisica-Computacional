/* *****************************************************************************
   Programa para tirar a media de um conjunto de arquivos de dados.

   Se tens um conjunto com n arquivos de m colunas cada e queres a media
   das informacoes das j-esimas colunas dos arquivos (ex.: a primeira
   coluna de cada arquivo eh a velocidade e queres saber como as velocidades
   de todos os arquivos se comportaram na media) entao esse eh o programa
   para isso.

   *****************************************************************************
   Para baixar (download) use:
   wget https://github.com/ismaeldamiao/avulsos/raw/master/c/media/media.c

   Use um dos seguintes comandos para compilar e executar:
   clang media.c -o media.o && ./a.out
   gcc media.c -o media.o && ./a.out
   *****************************************************************************
   Escrito em: 16 de novembro de 2019
   Midificacoes:
      * 14 de marco de 2020, para funcionar com qualquer quantidade de colunas;
      * 20 de dezembro de 2020, correcoes formais.
   *****************************************************************************
   E-mail: ismaellxd@gmail.com
   Site: https://ismaeldamiao.github.io/
   *****************************************************************************
   Copyright © 2020 Ismael Damião

   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the “Software”), to 
   deal in the Software without restriction, including without limitation the 
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
   sell copies of the Software, and to permit persons to whom the Software is 
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in 
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
   IN THE SOFTWARE.
***************************************************************************** */
/* *****************************************************************************
   Bibliotecas
***************************************************************************** */
#include<stdio.h>
#include<stdlib.h>

/* *****************************************************************************
   Definicoes
***************************************************************************** */
#define TRUE 1
#define FALSE 0

#define MAX_FILES 1024
#define MAX_SIZE_STRING 3072

#define ERRO_LIMITE 1
#define ERRO_DADOS 2
#define SUCESSO 0

/* *****************************************************************************
   Declaracao das funcoes
***************************************************************************** */
int contar_colunas(const char*);
int arquivo_existe(const char*);

/* *****************************************************************************
   Funcao principal
***************************************************************************** */
int main(int argc, char **argv){

   /* Strings - s */
   const char *s_lista = "listas_de_arquivos.tmp";
   char s_arquivo_dados[MAX_FILES][MAX_SIZE_STRING],
   s_resultado[MAX_SIZE_STRING],
   nome[MAX_SIZE_STRING],
   ls[MAX_SIZE_STRING];

   /* Arquivos */
   FILE *lista, *resultado, *arquivo_dados[MAX_FILES];

   /* Inteiros */
   int N_arq, arq, N_col, col, fim = FALSE;

   /* Reais */
   double soma[MAX_FILES], valor;

   /* ***
      Cria uma lista contendo os nomes de todos os arquivos de onde vamos tirar
      as medias
   *** */
   if(argc < 2){
      fprintf(stdout,"Qual o padrao do nome dos arquivo para fazer a media (*)? ");
      scanf("%s", nome);
   }else{
      sprintf(nome, "%s", argv[1]);
   }

   /* Apagar o arquivo de resultado, caso ja exista */
   sprintf(s_resultado, "%s.dat", nome);
   if(arquivo_existe(s_resultado)) remove(s_resultado);

   /* Escrever a lista com base no nome */
   sprintf(ls, "env ls -1 %s >> %s", nome, s_lista);
   system(ls);
   
   /* ***
      Rotina para:
      * salvar o nome de todos os arquivos de dados e abrir eles;
      * contar quantos arquivos tem.
   *** */
   lista = fopen(s_lista, "r");
   for(arq = 0;; ++arq){

      /* Menssagem em caso de erro */
      if(arq > MAX_FILES){
         fprintf(stderr, "Erro, ha muitissimos arquivos...\n");
         return ERRO_LIMITE;
      }

      /* Salvar nome e abrir aquivo de dados */
      if(fscanf(lista, "%s", s_arquivo_dados[arq]) == EOF) break;
      arquivo_dados[arq] = fopen(s_arquivo_dados[arq], "r");

      /* Menssagem em caso de erro */
      if(!arquivo_dados[arq]){
         fprintf(stderr, "Erro, houve problema ao abrir um arquivo");
         return ERRO_DADOS;
      }
   }
   N_arq = arq;
   fclose(lista);
   remove(s_lista); /* Apagar a lista */

   /* Contar quantas colunas tem o primeiro arquivo de dados */
   N_col = contar_colunas(s_arquivo_dados[0]);

   resultado = fopen(s_resultado, "w");

   /* ***
      Rotina para calcular a media
   *** */
   for(;;){
      for(col = 0; col < N_col; ++col) soma[col] = 0.0;
      /* some o valor da col-esima coluna de cada arquivo */
      for(col = 0; col < N_col; ++col){
         for(arq = 0; arq < N_arq; ++arq){
            if(fscanf(arquivo_dados[arq], "%lf", &valor) != EOF){
               soma[col] += valor;
            }else{
               fim = TRUE; 
               break;
            }
         }
         if(fim) break;
      }
      if(fim) break;
      for(col = 0; col < N_col; ++col)
      fprintf(resultado, "%g ", soma[col]/((double)N_arq));
      fprintf(resultado, "\n");
   }
   fprintf(stdout, "Pronto!\n");
   return SUCESSO;
}

/* ***
   Rotina calcular quantas colunas separadas por ' ' tem
   cada arquivo (se supoe que todos tem a mesma quantidade)
*** */
int contar_colunas(const char *nome){
   int ch, quantidade_colunas = 0, contar = TRUE;
   FILE *arquivo = fopen(nome, "r");
   if(!arquivo) return -1;
   for(;;){
      ch = fgetc(arquivo); /* Ler um caracter */
      if(ch == (int)'\n'){ /* basta ler a 1a linha */
         break;
      }else if(ch == (int)' '){
         contar = TRUE;
      }else if(contar){
         ++quantidade_colunas;
         contar = FALSE;
      }
   }
   fclose(arquivo);
   return quantidade_colunas;
}

/* ***
   Rotina para verificar se um arquivo existe
*** */
int arquivo_existe(const char *nome){
   FILE *arquivo = fopen(nome, "r");
   if(arquivo){
      fclose(arquivo);
      return TRUE; /* existe */
   }else{
      return FALSE; /* nao existe */
   }
}
