#ifndef COMMENT_HH
#define COMMENT_HH

#include <string>

class comment{
    private:
    std::string comment_content;

    public:
    comment() = default;
    comment(const std::string &);
    std::string get_content();
};

#endif