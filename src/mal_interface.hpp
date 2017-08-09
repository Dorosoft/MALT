#ifndef __MAL_INTERFACE_HPP
#define __MAL_INTERFACE_HPP

#include <iostream>
#include <curl/curl.h>
#include <string>
#include "xml_process.hpp"
#include "anime.hpp"
#include "data_process.hpp"

void load_user_anime_list(std::string& MALUSER, std::map<long, Anime>& dst);
bool verify_credentials(std::string& MALUSER, std::string& MALPWD);
void search_list(std::string& keywords, std::map<long, searchdata>& dst);
void curl_finalize();


#endif
