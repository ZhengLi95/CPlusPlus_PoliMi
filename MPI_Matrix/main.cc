#include "matrix.h"

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]){

    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    la::Matrix A;
    la::Matrix B;

    if (rank == 0){
        A.read("A");
        B.read("B");
    }

    size_t l = A.get_n_rows();
    size_t m = A.get_n_cols();
    size_t n = B.get_n_cols();

    MPI_Bcast(&l, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Here we must create a local matrix B because in the processes (except 0) we did not
    // initilize the vector<double> with scale, thus it can not receive the data from process 0
    la::Matrix loc_B(m, n);

    if (rank == 0){
        MPI_Bcast(B.get_data(), m * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        loc_B = B;
    }
    else{
        MPI_Bcast(loc_B.get_data(), m * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    // Here we devide the first matrix, based on row, into sub matrices
    size_t s = l / size;
    la::Matrix loc_A(s, m);

    if (rank == 0){
        MPI_Scatter(A.get_data(), s * m, MPI_DOUBLE, loc_A.get_data(), 
        s * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    else{
        MPI_Scatter(nullptr, s * m, MPI_DOUBLE, loc_A.get_data(), 
        s * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    // Here we do the paralleling computation
    la::Matrix loc_C = loc_A * loc_B;

    // Here we gather all the entries from the sub matrices
    la::Matrix C(l, n);

    if (rank == 0){
        MPI_Gather(loc_C.get_data(), s * n, MPI_DOUBLE, C.get_data(), 
        s * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    else{
        MPI_Gather(loc_C.get_data(), s * n, MPI_DOUBLE, nullptr, 
        s * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    if (rank == 0){
        C.print(true);
    }
    
    MPI_Finalize();   

    return 0;  
}