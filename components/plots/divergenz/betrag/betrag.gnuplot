#!/bin/bash
set terminal epslatex standalone color
#set terminal png size 1600,1000
set output dateiname
set xlabel "Zeit in a.u."
set ylabel "Abweichung der quadratische Norm von 1"
#set nokey
#set log y
#set format y "$%.0s*10^{%T}$
set yrange [-0.000000001: 0.000000001]
set xrange [0:50000]
plot\
"../m1o50zi1000ri1000zp708rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w150f64.txt" using 5:($8 - 1) with lp t "$\\delta_t = 1000/708$",\
"../m1o50zi1000ri1000zp707rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w300f64.txt" using 5:($8 - 1) with lp t "$\\delta_t = 1000/707$",\
"../m1o50zi1000ri1000zp706rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w20f64.txt" using 5:($8 - 1) with lp t "$\\delta_t = 1000/706$",\
