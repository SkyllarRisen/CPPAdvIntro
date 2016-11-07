set terminal postscript eps size 3.5,2.62 enhanced color \
    font 'Helvetica,20' linewidth 2
set output 'Philipp_problem2a.eps'

set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2
set style line 2 linecolor rgb '#dd181f' linetype 2 linewidth 4

set xrange [0:10]
set yrange [0:10]
set xlabel "x"
set ylabel "f(x)"

f(x) = exp(1/x)
g(x) = exp(x)

plot f(x) title 'exp(1/x)' with lines linestyle 1, \
     g(x) title 'exp(x)' with lines linestyle 2