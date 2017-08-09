#include "date.hpp"

/* Constructor */
Date::Date()
{
  _day = 0;
  _month = 0;
  _year = 0;
}

Date::Date(int day, int month, int year)
{
  _day = day;
  _month = month;
  _year = year;
  if (not this->valid())
    std::cerr << "Warning ! Build an invalid date" << day << "/" << month << "/" << year << std::endl;
}

bool Date::operator<(Date const &second){
  if (this->year() < second.year())
    return true;
  if (this->year() == second.year()){
    if (this->month() < second.month())
      return true;
    if (this->month() == second.month())
      return (this->day() < second.day());
    return false;
  }
  return false;
}

std::ostream& operator<<(std::ostream& os, const Date& dt){
  os << dt._day << "/" << dt._month << "/" << dt._year;
  return os;
}

/* Check if the date correspond to a correct calendar day */
bool Date::valid() const
{
  bool valid_day = false;
  bool valid_month = false;
  bool valid_year = false;
  if ((_day < 0) or (_month < 0) or (_year < 0))
    return false;
  if (_month%2==0) {
    if (_month != 2) 
        if (_month < 7)
          valid_day = _day < 31;
        else valid_day = _day <= 31;
    else
      if ((_year%4==0 and _year%100!=0) or _year%400==0) //Leap year
        valid_day = _day <= 29;
      else
        valid_day = _day < 29;
  }
  else
    if (_month < 7)
      valid_day = _day <= 31;
    else
      valid_day = _day < 31;
  if (_month < 13)
    valid_month = true;
  if (_year < 9999)
    valid_year = true;
  return (valid_day and valid_month and valid_year);
}
/* Accessor */
int Date::day() const
{
  return _day;
}

int Date::month() const
{
  return _month;
}

int Date::year() const
{
  return _year;
}

void Date::edit(int day, int month, int year)
{
  Date tmp(day, month, year);
  if (tmp.valid()) {
    _day = day;
    _month = month;
    _year = year;
  }
  else
    std::cerr << "Invalid date ! \n" << std::endl;
}

/* Convert yyyy-mm-dd string to Date */
Date& convert_to_date(const char* src, Date& dst){
  int year = (src[0]-'0')*1000 + (src[1]-'0')*100
    + (src[2]-'0')*10 + (src[3]-'0');
  int month = (src[5]-'0')*10 + (src[6]-'0');
  int day = (src[8]-'0')*10 + (src[9]-'0');
  dst = Date(day,month,year);
  return dst;
}

std::string Date::xml_str() const{
  std::string d,m,y;
  if (_day < 10)
    d.append("0");
  d.append(std::to_string(_day));
  if (_month < 10)
    m.append("0");
  m.append(std::to_string(_month));
  y.append(std::to_string(_year));
  if (this->valid())
    return m + d + y;
  else
    return "";
}

