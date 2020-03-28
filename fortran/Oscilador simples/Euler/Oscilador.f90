!  Autor: Ismael Felipe Ferreira dos Santos
!         Instituto de Fisica,
!         Universidade Federal de Alagoas
!  E-mail: ismaellxd@gmail.com
!  Copyright © 2020 MIT LICENCE
!  GIT: https://github.com/ismaeldamiao/ismael-damiao-repo
!  Objetivo: Resolver o oscilador hamonico simples pelo metodo de Euler (cf. 
!            Moyses Vol2 p42)
!  Escrito em: 10 de marco de 2020
PROGRAM Oscilador

   IMPLICIT none
   INTEGER :: count = 0, countMax
   DOUBLE PRECISION :: k, massa, posicao, velocidade, tempo, dt, omega2, aux(2)
   INTEGER, PARAMETER :: fPosicao = 7

   OPEN(fPosicao, FILE="Posicao.dat")

   ! Condicoes de contorno
   massa = 1.0d0 ! Massa oscilante
   k = 1.0d0 ! Constante da mola
   omega2 = k / massa ! Frenquenca angular

   dt = 1.0d-6 ! Discreticaao dos pontos
   posicao = 10.0d0 ! Posicao inicial da massa oscilante
   velocidade = 0.0d0 ! Velocidade inicial da massa oscilante

   countMax = INT(0.1d0/dt) ! Serve para o arquivo nao ficar muito 'pesado'

   tempo = 0.0d0
   DO; IF(tempo <= 30.0d0) THEN
      aux(1) = - omega2 * posicao;
      aux(2) = velocidade;
      ! Calculo para a velocidade em funcao do tempo
      velocidade = velocidade + aux(1) * dt
      ! Calculo para  a posicao em funcao do tempo
      posicao = posicao + aux(2) * dt

      count = count + 1
      IF(count > countMax) THEN
         WRITE(fPosicao, FMT=*) tempo, posicao
         count = 0
      END IF
      tempo = tempo + dt
   ELSE; EXIT; END IF; END DO

END PROGRAM Oscilador
