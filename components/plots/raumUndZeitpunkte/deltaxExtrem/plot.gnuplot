set terminal epslatex standalone color
set output dateiname
set key right bottom
#set format x "$%.0s*10^{%T}$"
set xlabel "\$\\delta_x\$ in a.u."
set ylabel "\$\\Theta\$ (Fehler der numerischen L\\\"{o}sung)"
set yrange [0:0.5]
set xrange [0:0.01]
#set log y
#set log x
#set xrange [0:0.004]

plot\
"zusatzdaten/m1o50zi1000ri1000zp10000rp10mae1mg1oae1og1zpae50zpg1rpae10rpg380w1f64.txt" using (1/$4):($6/$7) with lp title "Der Fehler $\\Theta$ bei $N_t = 10001$", x**1.99954*7585.98  t "$7586 x^{2}$"
# "werteKombiniert" using (1/$4):($6/$7) with lp title "Der Fehler $\\Theta$ bei $N_t = 10001$",\
