#include <iostream>
#include <string>
#include "mal_interface.hpp"
#include "anime.hpp"
#include "hide_input.hpp"


std::string MALUSER;
std::string MALPWD;
std::string FILENAME = "export_list.xml";

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
    << "5 - Export offline xml \n"
    << "6 - Import offline xml \n"
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
    case 5 :
      export_all(&alist);
      break;
    case 6 :
      import_xml_alist(FILENAME, alist);
      break;

    case 0 :
      curl_finalize();
      return EXIT_SUCCESS;
    }
  }
  return EXIT_SUCCESS;
}
