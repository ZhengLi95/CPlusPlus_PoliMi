#ifndef PLACE_HH
#define PLACE_HH

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "comment.hh"

class place{
    private:
    std::string name;
    std::string description;
    std::vector<std::shared_ptr<comment>> comment_vec;

    public:
    place() = default;
    place(const std::string &, const std::string &);
    void add_a_comment(std::shared_ptr<comment>);
    void print_comments();
};

#endif