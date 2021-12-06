set terminal pdfcairo
set output "plane.pdf"

set size ratio 0.5

set xlabel "Re"
set ylabel "Im"

unset xtics
unset ytics

set cbrange [1:5]
unset colorbox
unset cbtics

set palette defined ( 1 "#FF0000",\
                      2 "#00FF00",\
                      3 "#0000FF",\
                      4 "#F0FF0F",\
                      5 "#F0F0F0")



unset output
unset terminal