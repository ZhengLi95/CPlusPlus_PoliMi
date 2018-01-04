#include <iostream>

#include "medicine.hh"
#include "patient.hh"
#include "date.hh"

int main(int argc, char* argv[]){
    
    medicine med1("med1", Date("2017-12-12"), Date("2018-02-21"), 1, 3);
    medicine med2("med2", Date("2017-11-31"), Date("2018-04-12"), 3, 5);    
    medicine med3("med3", Date("2018-02-12"), Date("2018-01-01"), 6, 8);
    medicine med4("med4", Date("2018-02-12"), Date("2018-08-01"), 6, 8);

    patient p;

    p.add(med1);
    p.add(med2);
    p.add(med3);
    p.add(med4);

    p.active_prescriptions();

    return 0;
}