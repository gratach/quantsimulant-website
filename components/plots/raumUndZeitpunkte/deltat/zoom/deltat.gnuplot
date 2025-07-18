set terminal epslatex standalone color
set output dateiname
set key right bottom
#set nokey
#set format y "$%.0s*10^{%T}$"
set format y "%.10f"
set xlabel "\$\\delta_t\$ in a.u."
set ylabel "\$\\Theta\$ (Fehler der numerischen L\\\"{o}sung)"
set yrange [0.007624843488904865:0.007624845912499627]
set xrange [0:0.002]
#set log y
#set log x
plf = "../../m1o50zi1000ri1000zp49rp50mae1mg1oae1og1zpae50zpg40rpae50rpg40w1f64.txt"
a(b) = 'plf every :::'.b.'::'.b.' using (1/$3):($6/$7) with lp t "'.sprintf("$ N_x = %i $",b*50 + 50).'",'
u(b) = 'plf every :::'.b.'::'.b.' using (1/$3):($6/$7) with lp lc "grey" notitle, '
f = ""
f=f.a(19)
eval "plot ".f." (x**(3.99938))*(455.059)+(0.00762484+0.000000001*3.66043) t '$455 x^{4} +0.00762484366$'"
