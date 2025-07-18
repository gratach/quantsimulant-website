set terminal epslatex standalone color
#set terminal png size 1600,1000
set output dateiname
set yrange [0.0006:1.1]
set xrange [0.0006:0.1]
set key right bottom
set xlabel "$\\delta_x$ in a.u"
set ylabel "$\\Theta$ (Fehler der Numerischen L\\\"{o}sung"
set log x
set log y
#set xrange [0:100000]
plf = "t_m1o30zi1000ri1000zp1000rp10mae10mg1oae20og4zpae10zpg1rpae10rpg130w1f64.txt"
a(b) = 'plf every :::'.b.'::'.b.' using (1/$4):($6/$7) with lp t "'.sprintf("Ordnung %i",30+b*20).'",'
f = ""
do for [i=0:4] {
	f=f.a(i)
}
eval "plot ".f
