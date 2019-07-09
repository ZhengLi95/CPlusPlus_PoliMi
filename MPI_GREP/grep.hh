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