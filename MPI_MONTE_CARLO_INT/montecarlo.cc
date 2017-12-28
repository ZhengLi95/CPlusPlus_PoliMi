#include <vector>
#include <functional>
#include <random>
#include <ios>
#include <utility>
#include <stdexcept>
#include <iostream>

#include "montecarlo.hh"
#include "mpi.h"

std::pair<double, double>
monte_carlo (const std::function<double (double)> & f,
    const double & lb, const double & ub, unsigned long N){
    
    if (lb >= ub){
        throw std::invalid_argument("We cannot have a lower bound which\
         is greater than the upper bound! Check them please!");
    }

    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned long loc_N = N / size;
    if (rank < N % size){
        loc_N += 1;
    }

    std::default_random_engine engine(size*size*rank*rank);
    std::uniform_real_distribution<double> dis(-1., 1.);

    double loc_avg_y = 0;
    double loc_var_sum = 0;
    double avg_y;
    double var_sum;

    std::vector<double> y_vec;
    for (unsigned i = 0; i < loc_N; i++){
        const double x = dis(engine);
        const double y = f(x);
        y_vec.push_back(y);
    }

    // Calculate the avg of y
    for (double y : y_vec){
        loc_avg_y += y;
    }
    loc_avg_y /= N;

    // Calcalate the sum of square variations
    for (double y : y_vec){
        loc_var_sum = loc_var_sum + (y - loc_avg_y) * (y - loc_avg_y); 
    }

    // MPI_Reduce(&loc_avg_y, &avg_y, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    // MPI_Reduce(&loc_var_sum, &var_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Here we use MPI_Allreduce() rather than MPI_Reduce() because we hope all the
    // processes can return the true result
    MPI_Allreduce(&loc_avg_y, &avg_y, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&loc_var_sum, &var_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    // Calcalate the final result
    double int_val;
    double unbiased_var;
    double quadrature_var;

    int_val = (ub - lb) * avg_y;
    unbiased_var = var_sum / (N - 1);
    quadrature_var = (ub - lb) * (ub - lb) * unbiased_var / N;

    // Return the result
    std::pair<double, double> result {int_val, quadrature_var};
    return result;
    
}