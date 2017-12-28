#include <iostream>
#include <iomanip>

#include <stdlib.h>
#include <mpi.h>
#include "montecarlo.hh"

double f(double x){
    return x * x -  x + 2;
}

int main(int argc, char* argv[]){
    
    double lb = -1;
    double ub = 1;
    unsigned long times;
    argc == 2 ? times = std::atol(argv[1]) : times = 1e+06;

    MPI_Init(&argc, &argv);
    
    auto result = monte_carlo(f, lb, ub, times);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        std::cout.setf(std::ios::scientific, std::ios::floatfield);
        std::cout.precision(3);
        std::cout << "Integration value: " << result.first << std::endl 
        << "Quadrature variance: " << result.second << std::endl;
    }

    MPI_Finalize();

    return 0;
}