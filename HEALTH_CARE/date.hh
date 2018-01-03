#ifndef DATE_HH
#define DATE_HH

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
