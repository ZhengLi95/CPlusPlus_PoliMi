#ifndef MEDICINE_HH
#define MEDICINE_HH

#include <string>
#include <utility>

#include <date.hh>

class medicine{
    private:
    std::string name;
    Date proposed_end_date;
    Date expiry_date;
    std::pair<unsigned, unsigned> range;

    public:
    medicine() = default;
    medicine(const std::string &, const Date &, const Date &, const unsigned &, const unsigned &);

    bool is_compatible_with(const medicine &);
    bool is_expired();
};

#endif