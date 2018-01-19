#include "user.hh"

user::user(const std::string & name, const std::string & surname){
    this->name = name;
    this->surname = surname;
}

void user::leave_a_comment(const std::string & content, place & plc){
    std::shared_ptr<comment> c = std::make_shared<comment>(content);
    comment_vec.push_back(c);
    plc.add_a_comment(c);
}

void user::print_comments(){
    std::cout << std::endl;
    for (auto cmt : comment_vec){
        std::cout << name << " " << surname << ": " << std::endl;
        std::cout << cmt->get_content() << std::endl;
    }
    std::cout << std::endl;
}