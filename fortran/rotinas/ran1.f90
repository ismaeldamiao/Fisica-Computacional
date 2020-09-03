! Gerador de numeros aleatorios.
! Adaptado ao Fortran 90 por SANTOS. I.F.F. (Ismael Damião)
! https://ismaeldamiao.github.io/
! "Numerical Recipes in Fortran 77" (Cambridge Univ. Press)
! The Art of Scientific Computing, 2nd Edition, 1992 p 280
! by W.H. Press, S.A. Teukolsky, W.T. Vetterling, and B.P. Flannery

! Nao usar para gerar mais de 100000000 de numeros, use ran2 ou ran3
! double var = ran1(&semente); // Guarda em var um numero aleatorio em [0, 1)
MODULE ran

CONTAINS
! “Minimal” random number generator of Park and Miller with Bays-Durham shuffle
! and added safeguards. Returns a uniform random deviate between 0.0 and 1.0
! (exclusive of the endpoint values). Call with idum a negative integer to
! initialize; thereafter, do not alter idum between successive deviates in a
! sequence. RNMX should approximate the largest floating value that is less
! than 1.
   REAL(8) FUNCTION ran1(idum)
      INTEGER(8), PARAMETER :: IA = 16807, IM = 2147483647, IQ = 127773,&
      NTAB = 32, NDIV = 1+(IM-1)/NTAB, IR = 2836
      REAL(8), PARAMETER :: AM = 1.0d0/IM, EPS = 1.2d-7, RNMX = 1.0d0-EPS
      INTEGER(8), intent(inout) :: idum
      INTEGER(8) :: j, k
      INTEGER(8), SAVE :: iy = 0, iv(NTAB)
      
      IF((idum.le.0) .or. (iy.eq.0)) THEN
         idum = MAX(-idum, 1)
         DO j = NTAB+8, 1, -1
            k = idum / IQ
            idum = IA*(idum-k*IQ)-IR*k
            IF(idum .lt. 0) idum = idum + IM
            IF(j .le. NTAB) iv(j) = idum
         ENDDO
         iy=iv(1)
      ENDIF
      k = idum/IQ
      idum = IA*(idum-k*IQ)-IR*k
      IF(idum.lt.0) idum = idum+IM
      j = 1 + iy/NDIV
      iy = iv(j)
      iv(j) = idum
      ran1 = MIN(AM*iy, RNMX)
      return
   END FUNCTION ran1
END MODULE ran
