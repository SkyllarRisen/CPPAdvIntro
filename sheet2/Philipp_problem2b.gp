set terminal postscript eps size 3.5,2.62 enhanced color \
    font 'Helvetica,20' linewidth 2
set output 'Philipp_problem2b.eps'

set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 1
set style line 2 linecolor rgb '#dd181f' linetype 2 linewidth 4

set title "Plot w/o fit"
plot "data.dat" title 'data' linestyle 1

f(x) = a*x**2 + b*x + c

a=1
b=1
c=1

fit f(x) "data.dat" via a,b,c

set title "Plot w/ fit"
plot "data.dat" title "raw data" linestyle 1, \
     f(x) title "fitted curve" with lines linestyle 2