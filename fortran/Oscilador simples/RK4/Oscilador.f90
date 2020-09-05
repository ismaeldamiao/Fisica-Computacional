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
   DOUBLE PRECISION :: k, massa, posicao, velocidade, tempo, dt, dt2, dt6, &
      omega2, kx(4), kv(4)
   INTEGER, PARAMETER :: fPosicao = 7

   OPEN(fPosicao, FILE="Posicao.dat")

   ! Condicoes de contorno
   massa = 1.0d0 ! Massa oscilante
   k = 1.0d0 ! Constante da mola
   omega2 = k / massa ! Frenquenca angular

   dt = 1.0d-3 ! Discreticaao dos pontos
   dt2 = dt * 0.5d0
   dt6 = dt / 6.0d0
   posicao = 10.0d0 ! Posicao inicial da massa oscilante
   velocidade = 0.0d0 ! Velocidade inicial da massa oscilante

   countMax = INT(0.1d0/dt) ! Serve para o arquivo nao ficar muito 'pesado'

   tempo = 0.0d0
   DO; IF(tempo <= 30.0d0) THEN
      kv(1) = - omega2 * posicao
      kx(1) = velocidade

      kv(2) = -omega2 * (posicao + kx(1) * dt2)
      kx(2) = velocidade + kv(1) * dt2

      kv(3) = -omega2 * (posicao + kx(2) * dt2)
      kx(3) = velocidade + kv(2) * dt2

      kv(4) = -omega2 * (posicao + kx(3) * dt2)
      kx(4) = velocidade + kv(3) * dt
      ! Calculo para a velocidade em funcao do tempo
      velocidade = velocidade + &
         (kv(1) + 2.0d0 * kv(2) + 2.0d0 * kv(3) + kv(4)) * dt6
      ! Calculo para  a posicao em funcao do tempo
      posicao = posicao + &
         (kx(1) + 2.0d0 * kx(2) + 2.0d0 * kx(3) + kx(4)) * dt6

      count = count + 1
      IF(count > countMax) THEN
         WRITE(fPosicao, FMT=*) tempo, posicao
         count = 0
      END IF
      tempo = tempo + dt
   ELSE; EXIT; END IF; END DO

END PROGRAM Oscilador
