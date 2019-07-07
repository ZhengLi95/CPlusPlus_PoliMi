# MPI COUNTER PROBLEM

You have to complete the implementation of a parallel application which counts the occurrences of a number in a text file. In details, you have to:

Develop a parallel function with the following prototype:
```cpp
std::size_t search_and_count (const std::string & file_name, int key); 
```
The function reads from the input text file named file_name a set of integer values and returns the number of values that are equal to key. Assume that the file is available only on rank 0.

Complete the implementation of the main function which is provided in the following, specifying the code to be added in (a), (b), (c):

```cpp
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
    if (argc == /* (a) your code goes here */){
    unsigned n_elems = /* Your code goes here */;
    if (rank == 0)
    std::cout << n_elems << " elements equal to "
    << /* (b) Your code goes here */ << " found." <<std::endl;
    }
    else{
    if (rank == 0)
    std::cout << "Two parameters expected " << std::endl;
    }
    /* (c) Your code goes here */
}
```

You can rely on the already implemented function:
```cpp
input_data_t read_data(const std::string & file_name);
```
which reads the input file named `file_name` and returns a vector of `int`.

The `file_name` and the search key are provided through the command line as first and second parameter, respectively. In other words your end user can run your program as:

```
$ search file_name key
```

For the sake of simplicity, assume that the number of `int`s stored in the input file is a multiple of the number of available processes.

An example of output of your program is the following:
```
$ mpiexec -np 2 ./search input2.txt 1
3 elements equal to 1 found.
```