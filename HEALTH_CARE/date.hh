#ifndef DATE_HPP_
#define DATE_HPP_

///STD include
#include <string>

struct Date
{
public:
  int day, month, year;
  Date () = default;
  Date (Date const&) = default;

  Date (std::string const& str);
  //format needs to be checked

  const std::string Print() const;


      /**
       * comparing two dates
       */
  friend bool operator< (const Date&, const Date&);

};

#endif
