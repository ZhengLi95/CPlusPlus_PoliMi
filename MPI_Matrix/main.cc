#include "matrix.h"

#include <iostream>

inline void print_dash(){
    std::cout << "=============================" << std::endl;
}

int main(int argc, char* argv[]){
    
    la::Matrix m(2, 3, 5.5);
    m.print(true);
    print_dash();

    la::Matrix a(3, 4, 2);
    a.print(true);
    print_dash();

    la::Matrix b(3, 4, 3);
    b.print(true);
    print_dash();

    la::Matrix c = m * a;
    c.print(true);
    print_dash();

    la::Matrix d = a + b;
    d.print(true);
    print_dash();

    return 0;  
}