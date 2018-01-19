#include "place.hh"

place::place(const std::string & name, const std::string & description){
    this->name = name;
    this->description = description;
}

void place::add_a_comment(std::shared_ptr<comment> cmt){
    comment_vec.push_back(cmt);
}

void place::print_comments(){
    std::cout << std::endl;
    for (auto cmt : comment_vec){
        std::cout << name << " - " << description << ": " << std::endl; 
        std::cout << cmt->get_content() << std::endl;
    }
    std::cout << std::endl;
}