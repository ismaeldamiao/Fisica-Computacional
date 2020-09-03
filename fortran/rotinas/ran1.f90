MODULE ModPreencherMatriz
! Subrotina para preencher a matriz

CONTAINS

   SUBROUTINE preencher( matriz )
! Parametros formais
      IMPLICIT none
      INTEGER, intent(inout) :: matriz(:, :)
! Variaveis locais
      INTEGER :: linha, coluna, quantidade_linhas, quantidade_colunas
! Obter tamanho do array
      quantidade_linhas = size(matriz, 1)
      quantidade_colunas = size(matriz, 2)
col:  DO coluna = 1, quantidade_colunas
  lin:   DO linha = 1, quantidade_linhas
            matriz(linha, coluna) = linha * coluna
  	     END DO lin
  	  END DO col
   END SUBROUTINE
END MODULE ModPreencherMatriz
