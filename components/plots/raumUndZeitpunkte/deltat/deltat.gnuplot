set terminal epslatex standalone color
set output dateiname
set key right bottom
#set nokey
#set format y "$%.0s*10^{%T}$"
set xlabel "\$\\delta_t\$ in a.u."
set ylabel "\$\\Theta\$ (Fehler der numerischen L\\\"{o}sung)"
set yrange [0:0.05]
#set yrange [0.002:0.1]
set xrange [0:0.008]
#set log y
#set log x
plf = "../m1o50zi1000ri1000zp49rp50mae1mg1oae1og1zpae50zpg40rpae50rpg40w1f64.txt"
a(b) = 'plf every :::'.b.'::'.b.' using (1/$3):($6/$7) with lp t "'.sprintf("$ N_x = %i $",b*50 + 50).'",'
u(b) = 'plf every :::'.b.'::'.b.' using (1/$3):($6/$7) with lp lc "grey" notitle, '
f = ""
do for [i=0:4] {
	do for [j=i*10:i*10+8]{
		f=f.u(j)
	}
}
f=f.a(9).a(19).a(29)
eval "plot ".f
