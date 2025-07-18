set terminal png size 1600,1000
set output "test.png"
set datafile separator whitespace
plot "m1o50zi1000ri1000zp50rp50mae10mg1oae10og1zpae50zpg40rpae50rpg40w1f64.txt" using 3:4:6 with image pixels
