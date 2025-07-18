set terminal epslatex standalone color
set output dateiname
#set key right bottom
#set format x "$%.0s*10^{%T}$"
set xlabel "\$\\delta_x\$ in a.u."
set ylabel "\$\\Theta\$ (Fehler der numerischen L\\\"{o}sung)"
set yrange [0.005:0.008]
#set xrange [0.0005:0.02]
#set log y
#set log x
#set xrange [0:0.004]

plot "m1o50zi1000ri1000zp1000rp1100mae10mg1oae20og1zpae10zpg1rpae1rpg100w1f64.txt" using (1/$4):($6/$7) with lp title "64-Bit Fließkommazahlen", "m1o50zi1000ri1000zp1000rp1100mae10mg1oae20og1zpae10zpg1rpae1rpg100w1f32.txt" using (1/$4):($6/$7) with lp title "32-Bit Fließkommazahlen"
