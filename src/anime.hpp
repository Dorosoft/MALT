#ifndef __ANIME_HPP
#define __ANIME_HPP

#include <string>
#include <iostream>
#include "date.hpp"
#include "pugixml.hpp"


struct animedata {
    std::string title;
    std::string synonyms;
    int type;
    int total_eps;
    int status;
    Date series_start;
    Date series_end;
    std::string img_url;
    friend std::ostream& operator<<(std::ostream& os, const struct animedata& ani);
};

struct searchdata : animedata {
  std::string english;
  int score;
  std::string synopsis;
  friend std::ostream& operator<<(std::ostream& os, const struct searchdata& ani);
};


struct myanimedata {
    int watched_eps;
    Date my_start;
    Date my_end;
    int my_score;
    int my_status;
    int rewatching_eps;
    std::string tags;
    friend std::ostream& operator<<(std::ostream& os, const struct animedata& ani);
};

class Anime {
  public:
    Anime();
    Anime(long int dbid);
    Anime(long int dbid, struct animedata& data, struct myanimedata& udata);
    friend std::ostream& operator<<(std::ostream& os, const Anime& ani);
    void export_xml(pugi::xml_node&);

  protected:
    struct animedata _data;
    struct myanimedata _userdata;
    long int _dbid;
};

#endif
