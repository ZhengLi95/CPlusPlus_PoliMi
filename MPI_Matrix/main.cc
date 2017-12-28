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
        if (argc == 3){
            A.read(argv[1]);
            B.read(argv[2]);
        }
        else{
            throw std::invalid_argument("Two files containing the matrix must be supplied!");
        }
    }

    size_t l = A.get_n_rows();
    size_t m = A.get_n_cols();
    size_t n = B.get_n_cols();

    MPI_Bcast(&l, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Here we must create a local matrix of the second matrix because in the processes (except 0) we 
    // did not initilize the vector<double> with scale, thus it can not receive the data from process 0
    la::Matrix loc_B(m, n);

    if (rank == 0){
        MPI_Bcast(B.get_data(), m * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        loc_B = B;
    }
    else{
        MPI_Bcast(loc_B.get_data(), m * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    // From now we really begin the parallel computing
    // Fisrt let's decide how many row vectors of matrix A each process will get
    int stripe = l / size;
    if (rank < l % size) 
        stripe += 1;
    
    // Create sub-matrix of matrix A
    la::Matrix loc_A(stripe, m);
     
    // Creat sendcounts[] and displs[] which will be used in MPI_Scatterv()
    // And we will calculate all the information of distribution into process 0 
    int sendcounts[size], displs[size];
    if (rank == 0){
        for (unsigned i = 0; i < size; i++){
            i < l % size ? sendcounts[i] = m * (l / size + 1) : sendcounts[i] = m * (l / size);
        }
        for (unsigned i = 0; i < size; i++){
            if (i == 0)
                displs[i] = 0;
            else
                displs[i] = displs[i-1] + sendcounts[i-1];
        }
        for (unsigned i = 0; i < size; i++){
            std::cout << "Rank: " << i << " sendcounts: " << sendcounts[i] << " displs: " << displs[i] << std::endl;
        }     
        MPI_Scatterv(A.get_data(), sendcounts, displs, MPI_DOUBLE, 
            loc_A.get_data(), stripe * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    else{
        MPI_Scatterv(nullptr, nullptr, nullptr, MPI_DOUBLE, 
            loc_A.get_data(), stripe * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    // Here we do the paralleling computation
    la::Matrix loc_C = loc_A * loc_B;

    // Here we gather all the entries from the sub matrices
    la::Matrix C(l, n);
    
    int* recvcounts = sendcounts;
    if (rank == 0){
        MPI_Gatherv(loc_C.get_data(), stripe * n, MPI_DOUBLE, C.get_data(),
            recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    else{
        MPI_Gatherv(loc_C.get_data(), stripe * n, MPI_DOUBLE, nullptr,
            nullptr, nullptr, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    // Print the final result
    if (rank == 0){
        std::cout << std::endl << "The matrix " << argv[1] << " is as:" << std::endl; 
        A.print(true, true, 3);
        std::cout << std::endl << "The matrix " << argv[2] << " is as:" << std::endl;
        B.print(true, true, 3);
        std::cout << std::endl << "The answer of " << argv[1] << " * " << argv[2] << " is as:" << std::endl;
        C.print(true, true, 3);
    }
    
    MPI_Finalize();   

    return 0;
}