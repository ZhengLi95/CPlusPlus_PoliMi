#ifndef MONTECARLO_HH
#define MONTECARLO_HH

#include <utility>
#include <functional>

std::pair<double, double>
monte_carlo (const std::function<double (double)> & f,
    const double & lb, const double & ub, unsigned long N);

#endif