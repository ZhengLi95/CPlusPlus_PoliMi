#include<iostream>
#include<fstream>
#include<algorithm>
#include<mpi.h>
#include<vector>
#include<string>

using input_data_t = std::vector<int>;

// return the data read from file_name
input_data_t read_data(const std::string & file_name);

std::size_t search_and_count (const std::string & file_name, int key);

int main (int argc, char * argv[])
{
    MPI_Init (&argc, &argv);
    int rank{0}, size{0};
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    
    if (argc == 3){
        unsigned n_elems = search_and_count(argv[1], std::stoi(argv[2]));
        if (rank == 0)
            std::cout << n_elems << " elements equal to " << argv[2] << " found." <<std::endl;
    }
    else{
        if (rank == 0)
            std::cout << "Two parameters expected " << std::endl;
    }

    MPI_Finalize();
    return 0;
}

std::size_t search_and_count (const std::string & file_name, int key){

    unsigned global_count = 0;
    input_data_t local_data;
    input_data_t global_data;

    // Number of values stored in the input file_name
    unsigned n;

    int rank, size;
    MPI_Comm_rank(&rank, MPI_COMM_WORLD);
    MPI_Comm_size(&size, MPI_COMM_WORLD);

    if(rank==0){
        global_data = read_data(file_name);
        n = global_data.size();
    }

    MPI_Bcast(&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // With assumption number of processes is a factor of data size
    const unsigned loc_n = n / size;
    local_data.resize(local_n);

    if(rank==0){
        MPI_Scatter(global_data.data(), MPI_INT, loc_n, local_data.data(), MPI_INT, loc_n, 0, MPI_COMM_WORLD);
    }
    else{
        MPI_Scatter(nullptr, MPI_INT, loc_n, local_data.data(), MPI_INT, loc_n, 0, MPI_COMM_WORLD);
    }

    auto b = local_data.cbegin();
    auto e = local_data.cend();
    unsigned local_count = std::count(b, e, key);

    MPI_Reduce(&local_count, &global_count, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);
}