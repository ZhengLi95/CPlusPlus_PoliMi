#ifndef USER_HH
#define USER_HH

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "place.hh"
#include "comment.hh"

class user{
    private:
    std::string name;
    std::string surname;
    std::vector<std::shared_ptr<comment>> comment_vec;
    
    public:
    user() = default;
    user(const std::string &, const std::string &);
    void leave_a_comment(const std::string &, place &);
    void print_comments();
};

#endif