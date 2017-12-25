# MPI_MATRIX #

In the `matrix.hh` and `matrix.cc` we have created the class of Matrix, you can check the
available functions. In the `main.cc`, we have given a frame for paralleling multiplication
of Matrix, and some details of the realization could be found in the code file.

Be attentive to in `main.cc`, `<mpi.h>` is conclude, thus you must use **mpi** to compile it,

Compile it as:
`mpicxx -std=c++11 main.cc matrix.cc -o exe`

Run it as:
'mpiexex -np 5 exe'

