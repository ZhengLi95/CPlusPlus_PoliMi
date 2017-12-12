#include "frame.h"

inline void print_dash(){
    std::cout << "=================" << std::endl;
}

int main(int argc, char* argv[]){

    DataFrame<int> a("Num Score");
    a.set_column("Num", {1, 2, 4, 5, 7, 2});
    a.set_column("Score", {23, 19, 26, 8, 23, 43});
    a.set_column("SCORE", {12, 4, 43, 3});
    a.print();
    print_dash();
    
    a.set_element_at("Score", 3, 0);
    a.print();

    double avg = a.get_mean("Num");

    std::cout << "AVG: " << avg << std::endl;

    a.select_equal("Num", 2).print();
    
    return 0;
}