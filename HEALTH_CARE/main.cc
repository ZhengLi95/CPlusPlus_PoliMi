#include <iostream>

#include "medicine.hh"
#include "date.hh"

int main(int argc, char* argv[]){
    medicine med1("med1", Date("2017-12-12"), Date("2018-02-21"), 1, 3);
    medicine med2("med2", Date("2017-11-31"), Date("2018-04-12"), 3, 5);    
    if (med1.is_compatible_with(med2)){
        std::cout << "MATRICOLA" << std::endl;
    }
    return 0;
}