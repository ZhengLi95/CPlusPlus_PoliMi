# MPI_MATRIX

In the `matrix.hh` and `matrix.cc` the class of Matrix is created. In the `main.cc`, a frame for parallel multiplication of Matrix has been given, and some explaination of ideas could be found in the code file.

Be attentive that **<mpi.h>** is concluded in `main.cc`, thus **the wrapper compiler mpicxx** must be used for compiling.

Compile it as:

`mpicxx -std=c++11 main.cc matrix.cc -o exe`

Run it as:

`mpiexec -np 5 exe A B`

*Notice that the number of processes cannot be greater than the first matrix's number of rows! Or some processes will be wasted. This is also not supported by the data structure of `class Matrix`, because in each process a sub-matrix will be created, and it is not supposed to have 0 row.*

