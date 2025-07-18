set terminal epslatex standalone color
#set terminal png size 1600,1000
set key bottom right
set nokey
set xtics 200000
set output dateiname
set xlabel "Zeit in a.u."
set ylabel "Der Fehler der numerischen L\\\"{o}sung \$ \\Theta \$"
#set yrange [0:1]
#set xrange [0:100000]
plot "m1o50zi1000ri1000zp1000rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w1000f64.txt" using 5:($6/$7) with lp t "Numerischer Fehler im Verlauf der Zeit (Konvergenzfall)"
