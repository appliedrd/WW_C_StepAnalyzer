#gnuplot
```console
gnuplot

plot 'multi1.csv' u 1:2 t "angular velocity" w l, 'multi1.csv' u 1:3 w p t "HeeStrike" pointtype 6 lc rgb "black", 'multi1.csv' u 1:4 t "good step BEEP" w p, 'multi1.csv'
u 1:5 t "peak detector" w l
```
