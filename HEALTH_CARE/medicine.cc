#include "medicine.hh"
#include "date.hh"

#include <ctime>
#include <iostream>

medicine::medicine(const std::string & name, const Date & p_date, 
    const Date & e_date, const unsigned & beg, const unsigned & end){
    this->proposed_end_date = p_date;
    this->expiry_date = e_date;
    this->name = name;
    this->range.first = beg;
    this->range.second = end;
}

bool medicine::is_compatible_with(const medicine & med) const{
    
    double int_center = (range.second + range.first)/2.;
    double out_center = (med.range.second + med.range.first)/2.;
    double int_radius = (range.second - range.first)/2.;
    double out_radius = (med.range.second - med.range.first)/2.;
    
    double distance = int_center - out_center;
    if (distance < 0) distance = -distance;

    if (distance <= int_radius + out_radius) 
        return false;
    else
        return true;
}

bool medicine::is_expired() const{
  /*creates a date from now and compares it with expiration date*/
   time_t now = time(0);
   struct tm  tstruct;
   char *buf = new char[80];
   tstruct = *localtime(&now);
   strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
   std::string s (buf, buf+10);
   Date d = Date(s);
   delete []buf;
   return (this->expiry_date < d);
}

Date medicine::get_expiry_date() const{
    return this->expiry_date;
}

Date medicine::get_proposed_end_date() const{
    return this->proposed_end_date;
}

std::string medicine::get_name() const{
    return this->name;
}