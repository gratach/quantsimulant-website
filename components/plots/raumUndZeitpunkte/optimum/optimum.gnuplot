set terminal epslatex standalone color
#set terminal png size 1600,1000
set output dateiname
set xlabel "$\\delta_t$"
set ylabel "$\\delta_x$"
set key bottom right
#set title "Die Abweichung \\(\\Theta\\) in Abh{\\\"a}ngigkeit der Ordnung"
#set yrange [0:0.003]
#set xrange [0:0.012]
#set log x
#set log y
plot "optimum.dat" using (1/($3 + 1)):(1/$4) with p t "$\\delta_x$ mit $\\Theta$ minimal",\
(0.0301652)*x**(0.515709) t "$0.030 x^{0.52}$"
