#include "comment.hh"

comment::comment(const std::string & comment_content){
    this->comment_content = comment_content;
}

std::string comment::get_content(){
    return this->comment_content;
}