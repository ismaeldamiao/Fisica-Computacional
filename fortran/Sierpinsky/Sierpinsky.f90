!  Autor: Ismael Felipe Ferreira dos Santos
!         Instituto de Fisica,
!         Universidade Federal de Alagoas
!  E-mail: ismaellxd@gmail.com
!  Direitos Reservados sob a LICENCA MIT 2019
!  GIT: https://ismaeldamiao.blogspot.com/fisicacomputacional
!  Objetivo: Gerar em um arquivo os pontos que pertencem ao fractal de 
!            Sierpinsky Gasket(do triangulo).
!  Escrito em: 30 de Julio de 2019

PROGRAM Sierpinsky

   IMPLICIT none

   INTEGER, PARAMETER :: QuantidadePontos = 20000, DadosFractal = 7
   INTEGER :: iPonto, indice
   REAL :: xponto, yponto, EscolherVertice
! Vertices de um triangulo equilatero
   REAL, PARAMETER, DIMENSION(3) :: xvertices=(/ 0., 1., 0.5 /), yvertices(3)=&
   (/ 0., 0., sqrt(3.)*0.5 /)

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

      EscolherVertice = EscolherVertice * 3.
      indice = CEILING(EscolherVertice)

      xponto = (xvertices(indice) + xponto) * 0.5
      yponto = (yvertices(indice) + yponto) * 0.5

      WRITE(DadosFractal, fmt=*) xponto, yponto
   END DO

END PROGRAM Sierpinsky