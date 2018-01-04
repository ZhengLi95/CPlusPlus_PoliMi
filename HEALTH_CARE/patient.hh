#ifndef PATIENT_HH
#define PATIENT_HH

#include <iostream>
#include <map>
#include <string>
#include <list>

#include "date.hh"
#include "medicine.hh"

class patient{
    private:
    std::multimap<Date, medicine> prescriptions;
    
    public:
    patient() = default;
    void add(medicine);
    std::list<medicine> active_prescriptions(void);
};

#endif