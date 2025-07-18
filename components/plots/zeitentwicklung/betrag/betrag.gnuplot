set terminal epslatex standalone color
#set terminal png size 1600,1000
set output dateiname
set xtics 20000
set xlabel "Zeit in a.u."
set ylabel "Abweichung der quadratische Norm von 1"
set nokey
#set yrange [0:1]
#set xrange [0:100000]
plot "../m1o50zi100ri1000zp100rp1001mae1mg1oae1og1zpae50zpg1rpae50rpg1w1000f64.txt" using 5:($8 - 1) with lp t "Test"
