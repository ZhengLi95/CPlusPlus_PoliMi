#ifndef MEDICINE_HH
#define MEDICINE_HH

#include <string>
#include <utility>
#include <iostream>

#include "date.hh"

class medicine{
    private:
    std::string name;
    Date proposed_end_date;
    Date expiry_date;
    std::pair<unsigned, unsigned> range;

    public:
    medicine() = default;
    medicine(const std::string &, const Date &, const Date &, const unsigned &, const unsigned &);
    
    std::string get_name() const;
    Date get_proposed_end_date() const;
    Date get_expiry_date() const;

    bool is_compatible_with(const medicine &) const;
    bool is_expired() const;
};

#endif