set terminal epslatex standalone color
set output dateiname
#set key right bottom
#set format x "$%.0s*10^{%T}$"
set xlabel "\$\\delta_t\$ in a.u."
set ylabel "\$\\Theta\$ (Fehler der numerischen L\\\"{o}sung)"
set yrange [0:1]
#set xrange [0.0005:0.02]
#set log y
#set log x
#set xrange [0:0.004]

plot "m1o50zi1e+35ri10000000000000000000zp100rp1000mae1mg1oae20og1zpae100zpg10rpae1rpg0w1f64.txt" using (1/$3):($6/$7) with lp title "64-Bit Fließkommazahlen", "m1o50zi1e+35ri10000000000000000000zp100rp1000mae1mg1oae20og1zpae100zpg10rpae1rpg0w1f32.txt" using (1/$3):($6/$7) with lp title "32-Bit Fließkommazahlen"
