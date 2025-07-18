#!/bin/bash
set terminal epslatex standalone color
#set terminal png size 1600,1000
set output dateiname
set xlabel "Zeit in a.u."
set ylabel "Der Fehler der numerischen L\\\"{o}sung \$ \\Theta \$"
set log y
set format y "$10^{%T}$
set yrange [0.001:(10**30)]
set xrange [0:150000]
plot \
"m1o50zi1000ri1000zp708rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w150f64.txt" using 5:($6/$7) with lp t "\$\\delta_t = 1000/708\$",\
"m1o50zi1000ri1000zp707rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w300f64.txt" using 5:($6/$7) with lp t "\$\\delta_t = 1000/707\$",\
"m1o50zi1000ri1000zp706rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w20f64.txt" using 5:($6/$7) with lp t "\$\\delta_t = 1000/706\$",\
