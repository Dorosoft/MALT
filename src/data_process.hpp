#ifndef __DATA_PROCESS_HPP
#define __DATA_PROCESS_HPP
#include "anime.hpp"
#include <map>

template<typename T>
struct remove_pointer{
  typedef T type;
};

template<typename T>
struct remove_pointer<T*>
{
  typedef typename remove_pointer<T>::type type;
};


template<typename T>
void display_all(T alist){
  for (typename remove_pointer<T>::type::iterator it=alist->begin(); it != alist->end(); ++it){
    std::cout << it->second;
  }
}
// void display_all (std::map<long, Anime>* const alist);
#endif
