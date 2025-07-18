set terminal epslatex standalone color
#set terminal png size 1600,1000
set nokey
set output dateiname
set xlabel "Zeit in a.u."
set ylabel "Der Fehler der numerischen L\\\"{o}sung \$ \\Theta \$"
#set yrange [0:1]
set xrange [0:40000]
plot "../m1o50zi100ri1000zp100rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w1000f64.txt" using 5:($6/$7) with lp t "Der Fehler der numerischen L\\\"{o}sung \$ \\Theta \$"
