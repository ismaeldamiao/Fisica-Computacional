#!/usr/bin/env gnuplot
set terminal png size 1280, 720 font ",18"
set key box font ",18"
set output "Posicao.png"
data = "Posicao.dat"

plot data w p lt rgb "blue" pt 7 ps 0.5 title "x(t)"
exit