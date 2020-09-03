MODULE ran
! Subrotina para preencher a matriz

CONTAINS

   FUNCTION ran1(idum)
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
