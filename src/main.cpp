#include <iostream>
#include <string>
#include "mal_interface.hpp"
#include "anime.hpp"
#include "hide_input.hpp"


std::string MALUSER;
std::string MALPWD;


int main()
{
  int choice = 1;
  std::map<long int, Anime> alist;
  std::map<long, struct searchdata> slist;
  std::string keywords;

  while (choice){
  std::cout << "1 - Connect to a MAL account \n"
    << "2 - Load anime list \n"
    << "3 - Print anime list \n"
    << "4 - Make a search\n"
    << "0 - Exit \n"
    << "Enter your choice : ";
  std::cin >> choice;

  switch (choice) {
    case 1 :
      std::cout << "Username : ";
      std::cin >> MALUSER;
      std::cout << "\n";
      std::cout <<"Password : ";
      SetStdinEcho(false);
      std::cin >> MALPWD;
      SetStdinEcho(true);
      std::cout << "\n";
      if (verify_credentials(MALUSER, MALPWD)) 
        std::cout << "Connection to " << MALUSER << " account succeed \n";
      else std::cout << "Invalid Credentials !\n";
      break;
    case 2 :
      load_user_anime_list(MALUSER, alist);
      break;
    case 3 :
      display_all(&alist);
      break;
    case 4 :
      slist.clear();
      std::cout << "Search : ";
      std::cin >> keywords;
      search_list(keywords, slist);
      display_all(&slist);
      break;
    case 0 :
      curl_finalize();
      return EXIT_SUCCESS;
    }
  }
  return EXIT_SUCCESS;
}
