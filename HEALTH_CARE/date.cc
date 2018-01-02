///Header include
#include "date.hh"

///std include
#include <iostream>
#include <sstream>

///STL include
#include <vector>

Date::Date(std::string const& str)
{
  std::vector<int> vect;
  std::istringstream ss(str);
  int i;

  while (ss >> i)
    {
      vect.push_back(i);
      if (ss.peek() == '-') ss.ignore();
    }
  day = vect[2];
  month = vect[1];
  year = vect[0];
}

const std::string Date::Print() const
{
   std::ostringstream converter;
   converter << day << "-" << (month) << "-" << year;
   return converter.str();
}

bool operator< (const Date &d1, const Date &d2)
{
  if (d1.year < d2.year)
      return true;
  else if (d1.year == d2.year)
  {
      if (d1.month < d2.month)
          return true;
      else if (d1.month == d2.month)
      {
          if (d1.day < d2.day)
              return true;
      }
  }
  return false;
}
