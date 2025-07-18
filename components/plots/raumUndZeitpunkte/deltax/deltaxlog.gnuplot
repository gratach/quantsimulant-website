set terminal epslatex standalone color
set output dateiname
set key right bottom
#set format x "\$%.0s*10^{%T}\$"
#set yrange [0:1]
set yrange [0.0026:1]
set xrange [0.0005:0.02]
set xlabel "\$\\delta_x\$ in a.u."
set ylabel "\$\\Theta\$ (Fehler der numerischen L\\\"{o}sung)"
set log y
set log x
plf = "../t_m1o50zi1000ri1000zp49rp50mae1mg1oae1og1zpae50zpg40rpae50rpg40w1f64.txt"
a(b) = 'plf every :::'.b.'::'.b.' using (1/($4-1)):($6/$7) with lp t "'.sprintf("$ N_t = %i $",b*50+50).'",'
u(b) = 'plf every :::'.b.'::'.b.' using (1/($4-1)):($6/$7) with lp lc "grey" notitle,'
f = ""
#do for [i=0:4] {
#	do for [j=i*10:i*10+8]{
#		f=f.u(j)
#	}
#}
do for [i=0:4] {
	f=f.a(i*10+9)
}
eval "plot ".f."(6534.2)*x**(1.97537) t '$6534 x^{2}$'"
