# MPI_GREP

`grep` is a popular Linux command that helps in searching strings within text files. For example, this simple invocation of the command:

```bash
$ grep pattern filename
```

will print all the lines where `pattern` appears preceded by their number in `filename`. So if the file `dogs.txt` includes the following text:

```txt
Dido is my dog. He loves to get outdoors
and in the forest, surrounded by a world of exciting scents,
he is very happy. I love taking Dido with me
when I go on holiday; sure that means staying reasonably close to home — no exotic beaches for a start!
```

The output of:

```bash
$ grep Dido dogs.txt
```

is:

```bash
1: Dido is my dog. He loves to get outdoors
3: he is very happy. I love taking Dido with me
```

Implement in `MPI` a parallel program similar to `grep`. Assume that any input file `filename` is already split in even parts and every process can access a partial file called `filename-<rank>`, where `<rank>` is a placeholder for each process’s `MPI` rank. In the above example, there are `dogs.txt-0`, `dogs.txt-1`, and so on. In particular, you are only required to provide the main source file and the implementation of the `print_result function`, starting from the code that follows.

```cpp
// grep.hh
#ifndef GREP_HH
#define GREP_HH
#include <vector>
#include <string>
#include <utility>

namespace grep{
    typedef std::pair< unsigned, std::string > number_and_line;
    typedef std::vector< number_and_line > lines_found;
    void search_string (const std::string & file_name,
    const std::string & search_string,
    lines_found & lines, unsigned & local_lines_number);
    void print_result (const lines_found & lines, unsigned local_lines_number);
}
#endif
```

```cpp
// grep.cc
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

    }
}
```