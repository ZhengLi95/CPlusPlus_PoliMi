#include <fstream>
#include <iostream>
#include <sstream>
#include <mpi.h>
#include "grep.hh"

namespace grep
{
    void search_string (const std::string & file_name, const std::string & search_string, lines_found &local_filtered_lines, unsigned & local_lines_number){
        int rank (0);
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);
        const unsigned rk (rank);
        local_lines_number = 0;
        std::ostringstream file_name_builder;
        file_name_builder << file_name << ’-’ << rk;
        const std::string local_file_name = file_name_builder.str ();
        std::ifstream f_stream (local_file_name);
        // read input file line by line
        for (std::string line; std::getline (f_stream, line); ){
            //increment local number of lines
            ++local_lines_number;
            if (line.find (search_string) != std::string::npos){
                local_filtered_lines.push_back ({local_lines_number, line});
            }
        }
    }
    
    void print_result (const lines_found & local_filtered_lines, unsigned local_lines_number){
        
        int rank(0), size(0);
        constexpr short MAX_LENGTH = 128;

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        // Send number of found lines of each proccess to rank 0
        std::vector<unsigned> nums(size, 0);
        unsigned local_nums_found_lines = local_filtered_lines.size();
        if (rank == 0){
            MPI_Gather(&local_nums_found_lines, 1, MPI_UNSIGNED, nums.data(), 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
        }
        else{
            MPI_Gather(&local_nums_found_lines, 1, MPI_UNSIGNED, nullptr, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
        }

        // Send local lines number, local found lines number and associated line
        MPI_Send(*local_lines_number, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD)
        for (unsigned i=0; i < local_nums_found_lines; i++){
            MPI_Send(*local_filtered_lines[i].first, 1, MPI_UNSIGNED, 0, 2*(i+1), MPI_COMM_WORLD);
        }
        for (unsigned i=0; i < local_nums_found_lines; i++){
            MPI_Send(*local_filtered_lines[i].second, MAX_LENGTH, MPI_CHAR, 0, 2*(i+1)-1, MPI_COMM_WORLD);
        }
        
        if (rank == 0){
            // Print the result returned from rank 0;  
            for (unsigned j = 0; j < nums[0]; j++){
                std::cout << local_filtered_lines[j].first << ": " << local_filtered_lines[j].second << std::endl; 
            }

            // Receive all messages at rank 0
            unsigned accumulated_lines_number = local_lines_number;
            for (unsigned i = 1; i < size; i++){
                unsigned received_local_lines_number;
                MPI_Recv(&received_local_lines_number, 1, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                accumulated_lines_number += received_local_lines_number;
                for (unsigned j = 0; j < nums[i]; j++){
                    std::string received_string(MAX_LENGTH);
                    unsigned received_found_lines_number;
                    MPI_Recv(&received_lines_number, 1, MPI_UNSIGNED, i, 2*(j+1)-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MPI_Recv(&received_string, MAX_LENGTH, MPI_CHAR, i, 2*(j+1), MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    std::cout << accumulated_lines_number + received_lines_number << ": " << received_string << std::endl;
                }
            }
        }

    }
}