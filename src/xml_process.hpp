#ifndef __XML_PROCESS_HPP
#define __XML_PROCESS_HPP

#include <iostream>
#include <string>
#include <map>
#include "anime.hpp"
#include "date.hpp"
#include "pugixml.hpp"

void load_xml_alist(std::string* s_anime_list, std::map<long int, Anime>& alist);
void load_xml_search(std::string* s_anime_list, std::map<long int, searchdata> &dst);
std::string add_xml_anime(const struct myanimedata* data);
void import_xml_alist(std::string& filename, std::map<long int, Anime> &alist);

#endif
