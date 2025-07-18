set terminal epslatex standalone color
#set terminal png size 1600,1000
set output dateiname
set key top
set xlabel "Die Ordnung Q"
set ylabel "\$\\Theta\$ (Fehler der numerischen L\\\"{o}sung)"
set title "Die Abweichung \\(\\Theta\\) in Abh{\\\"a}ngigkeit der Ordnung"
#set yrange [0:0.05]
set xrange [0:100]
plot "../m1o1zi1000ri1000zp1000rp1000mae10mg1oae1og1000zpae10zpg1rpae10rpg1w1f64.txt" using 2:($6/$7) with lp t "\\(\\Theta\\)"
