set terminal pdfcairo
set output "mandelbrot.pdf"

set size ratio 1

set xrange[-3:3]
set yrange[-3:3]

unset xtics
unset ytics

unset cbtics
unset colorbox
set cbrange [0:1]
set palette rgb 21,22,23

plot "mandelbrot.dat" u ($1+0.0001):($2+0.0001):3 matrix w image

unset output
unset terminal