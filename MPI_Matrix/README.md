# MPI_MATRIX #

In the `matrix.hh` and `matrix.cc` the class of Matrix is created. In the `main.cc`,
a frame for paralleling multiplication of Matrix has been given, and some explains
of the realization could be found in the code file.

Be attentive that **<mpi.h>** is concluded in `main.cc`, thus **the wrapper compiler mpicxx** must be used for compiling.

Compile it as:

`mpicxx -std=c++11 main.cc matrix.cc -o exe`

Run it as:

`mpiexec -np 5 exe A B`

*You can only create factor-many processes.*

*For example, here we create 5 processes because 5 is a factor of the number of rows fo A*

