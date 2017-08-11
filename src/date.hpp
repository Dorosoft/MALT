#ifndef __DATE_HPP
#define __DATE_HPP
#include <iostream>
#include <string>

class Date {
  public:
    Date();
    Date(int day, int month, int year);
    bool operator<(Date const &second);
    friend std::ostream& operator<<(std::ostream& os, const Date& dt);

    bool valid() const; 
    int day() const; 
    int month() const;
    int year() const;
    void edit(int day, int month, int year);
    std::string xml_str() const;

  protected:
    int _day;
    int _month;
    int _year;
};

Date& convert_to_date(const char* src, Date& dst);
Date& convert_off_to_date(const char* src, Date& dst);
    
#endif
