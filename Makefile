comp: clean
	@gcc -O3 mandelbrot.c -lm

clean:
	@rm -f *.out
	@rm -f *.dat
	@clear

plot:
	@gnuplot plot.plt