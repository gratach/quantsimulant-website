set terminal epslatex standalone color
#set terminal png size 1600,1000
set output dateiname
set key bottom
set xlabel "Die Ordnung Q"
set ylabel "\$\\Theta\$ (Fehler der numerischen L\\\"{o}sung)" tc lt 1
set y2label 'Quadratische Norm' tc lt 2
#set yrange [0:1]
#set xrange [0:100000]
plot "../m1o1zi1000ri1000zp1000rp1000mae10mg1oae1og1000zpae10zpg1rpae10rpg1w1f64.txt" using 2:($6/$7) with lp t "$\\Theta$", "../m1o1zi1000ri1000zp1000rp1000mae10mg1oae1og1000zpae10zpg1rpae10rpg1w1f64.txt" using 2:8 with lp t 'Quadratische, numerische Norm'

