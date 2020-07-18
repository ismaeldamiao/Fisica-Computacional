!  Programa para gerar em um arquivo os pontos que pertencem ao
!  fractal de Sierpinsky Gasket(do triangulo).
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!  E-mail: ismaellxd@gmail.com
!  Site: https://ismaeldamiao.github.io/
!  30 de Julio de 2019
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!  Copyright © 2020 Ismael Damião

!  Permission is hereby granted, free of charge, to any person obtaining a copy 
!  of this software and associated documentation files (the “Software”), to 
!  deal in the Software without restriction, including without limitation the 
!  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
!  sell copies of the Software, and to permit persons to whom the Software is 
!  furnished to do so, subject to the following conditions:

!  The above copyright notice and this permission notice shall be included in 
!  all copies or substantial portions of the Software.

!  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
!  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
!  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
!  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
!  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
!  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
!  IN THE SOFTWARE.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

PROGRAM Sierpinsky

   IMPLICIT none

   INTEGER, PARAMETER :: QuantidadePontos = 20000, DadosFractal = 7
   INTEGER :: iPonto, indice
   REAL(8) :: xponto, yponto, EscolherVertice
! Vertices de um triangulo equilatero
   REAL(8), PARAMETER, DIMENSION(3) :: xvertices = (/ 0.0, 1.0, 0.5 /), &
   yvertices(3) = (/ 0.0, 0.0, sqrt(3.0)*0.5 /)

! Abre um arquivo
   OPEN(DadosFractal, file="Sierpinsky_Gasket.dat")

! Escolhe um ponto (x,y) aleatorio
   CALL random_seed
   CALL random_number(xponto)
   CALL random_number(yponto)

! Escolhe um vertice aleatorio, calcula a posicao do ponto a meia distancia
! entre o ponto (x,y) e marca este ponto, repetindo o calculo com o novo ponto.
   DO iPonto = 1, QuantidadePontos
      CALL random_number(EscolherVertice)

      EscolherVertice = EscolherVertice * 3.0
      indice = CEILING(EscolherVertice)

      xponto = (xvertices(indice) + xponto) * 0.5
      yponto = (yvertices(indice) + yponto) * 0.5

      WRITE(DadosFractal, fmt=*) xponto, yponto
   END DO

END PROGRAM Sierpinsky
