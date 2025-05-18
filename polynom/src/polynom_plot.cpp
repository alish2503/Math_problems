#include "polynom_plot.h"
#include <stdexcept>

void plot() {
    FILE *gp = popen("gnuplot","w"); 
    if (!gp) {
        throw std::runtime_error("Error opening pipe to GNU plot");
    }
    std::fprintf(gp, "set terminal png\n");  
    std::fprintf(gp, "set xlabel 'x'\n");
    std::fprintf(gp, "set ylabel 'y'\n");
    std::fprintf(gp, "set output 'problem.png'\n");
    std::fprintf(gp, "plot 'points.txt' index 0 with linespoints pt 7 lt rgb 'red' title 'exact','points.txt' index 1 with linespoints pt 7 lt rgb 'yellow' title 'polynom1','points.txt' index 1 with linespoints pt 7 lt rgb 'green' title 'polynom2'\n"); 
    pclose(gp); 
}
