#include "anime.hpp"

Anime::Anime(){
}

Anime::Anime(long int dbid){
  _dbid=dbid;
}

Anime::Anime(long dbid, struct animedata& data, struct myanimedata& udata){
  _dbid = dbid;
  _data = data;
  _userdata = udata;
}

std::ostream& operator<<(std::ostream& os, const struct animedata& ani)
{
  os << "Title : " << ani.title << "\n"
    << "Synonyms : " << ani.synonyms << "\n"
    << "Types : " << ani.type << "\n"
    << "Total Eps : " << ani.total_eps << "\n"
    << "Status : " << ani.status << "\n"
    << "Series start : " << ani.series_start << "\n"
    << "Series end : " << ani.series_end << "\n"
    << "Img URL : " << ani.img_url << "\n";
  return os;
}

std::ostream& operator<<(std::ostream& os, const struct myanimedata& ani){
    os << "Watched eps : " << ani.watched_eps << "\n"
    << "Starting date : " <<  ani.my_start << "\n"
    << "Ending date : " << ani.my_end << "\n"
    << "My score : " << ani.my_score << "\n"
    << "My status : " << ani.my_status << "\n"
    << "Rewatching eps : " << ani.rewatching_eps << "\n"
    << "My tags : " << ani.tags << "\n";
    return os;

}

std::ostream& operator<<(std::ostream& os, const struct searchdata& ani){
  os << (const struct animedata) ani
    <<"English : " << ani.english <<"\n"
    <<"Score : " << ani.score << "\n"
    <<"Synopsis : " << ani.synopsis << "\n";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Anime& ani)
{
  os << "MAL id : " << ani._dbid << "\n"
    << ani._data
    << ani._userdata;
  return os;
}

