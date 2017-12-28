# MPI_MONTE_CARLO_INTEGRATION #

This is a program for parallel computing the integration value by Monte-Carlo method.

Pay attention to that `<mpi.h>` is concluded in `main.cc` and `montecarlo.cc`, thus the wrapper compiler `mpicxx` must be used for compiling.

Compile it as:

`mpicxx -std=c++11 main.cc montecarlo.cc -o exe`

Run it as:

`mpiexec -np 5 exe 1234567`

Here `1234567` is a command line argument which will be pass into `main()` and be used as the experiment times. According to my own experience, we'd better set the number of experiment times greater than **10^6** (which is also the default number of experiment times if the command line argument is not given), or the error will be quite large.

If you want to check the orginal exercise instruction file, please refer to **[es.pdf](../MPI_MONTE_CARLO_INT/es.pdf)** in this repository.

