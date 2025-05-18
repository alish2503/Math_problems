#include "plot.h"
#include <stdexcept>

void plot() {
	FILE *gp = popen("gnuplot", "w"); 
	if (!gp) {
        throw std::runtime_error("Error opening pipe to GNU plot");
    }

	std::fprintf(gp, "set terminal pngcairo size 800,600\n");
	std::fprintf(gp, "set output 'heatmap.png'\n");
	std::fprintf(gp, "set xlabel 'X'\n");
	std::fprintf(gp, "set ylabel 'Y'\n");
	std::fprintf(gp, "set xrange [0:1]\n");
	std::fprintf(gp, "set yrange [0:1]\n");
	std::fprintf(gp, "set ticslevel 0\n");
	std::fprintf(gp, "set dgrid3d 30,30 qnorm 3\n");
	std::fprintf(gp, "plot 'data.txt' w image\n");
	std::fflush(gp); 

	std::fprintf(gp, "set output 'graph.png'\n");
	std::fprintf(gp, "set view 40, 40\n");
	std::fprintf(gp, "splot 'data.txt' w pm3d notitle\n");
	std::fflush(gp); 

	pclose(gp);
}
