#include "medicine.hh"
#include "date.hh"

medicine::medicine(const std::string & name, const Date & p_date, 
    const Date & e_date, const unsigned & beg, const unsigned & end){
    this->proposed_end_date = p_date;
    this->expiry_date = e_date;
    this->name = name;
    this->range.first = beg;
    this->range.second = end;
}

bool medicine::is_compatible_with(const medicine & med){
    
    double int_center = (range.second + range.first)/2;
    double out_center = (med.range.second + med.range.second)/2;
    double int_radius = (range.second - range.first)/2;
    double out_radius = (med.range.second - med.range.second)/2;

    double distance = int_center - out_center;
    if (distance < 0) distance = -distance;

    if (distance <= int_radius + out_radius) 
        return false;
    else
        return true;

}   