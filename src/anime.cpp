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

void Anime::export_xml(pugi::xml_node& main){
  pugi::xml_node mainNode = main.append_child("entry");
  pugi::xml_attribute id_att = mainNode.append_attribute("dbid");
  id_att.set_value(std::to_string(this->_dbid).c_str());
  pugi::xml_node title_node = mainNode.append_child("title");
  title_node.append_child(pugi::node_pcdata).set_value(this->_data.title.c_str());
  pugi::xml_node synonyms_node = mainNode.append_child("synonyms");
  synonyms_node.append_child(pugi::node_pcdata).set_value(this->_data.synonyms.c_str());
  pugi::xml_node type_node = mainNode.append_child("type");
  type_node.append_child(pugi::node_pcdata).set_value(std::to_string(this->_data.type).c_str());
  pugi::xml_node total_eps_node = mainNode.append_child("total_eps");
  total_eps_node.append_child(pugi::node_pcdata).set_value(std::to_string(this->_data.total_eps).c_str());
  pugi::xml_node status_node = mainNode.append_child("status");
  status_node.append_child(pugi::node_pcdata).set_value(std::to_string(this->_data.status).c_str());
  pugi::xml_node series_start_node = mainNode.append_child("series_start");
  series_start_node.append_child(pugi::node_pcdata).set_value(this->_data.series_start.xml_str().c_str());
  pugi::xml_node series_end_node = mainNode.append_child("series_end");
  series_end_node.append_child(pugi::node_pcdata).set_value(this->_data.series_end.xml_str().c_str());
  pugi::xml_node img_url_node = mainNode.append_child("img_url");
  img_url_node.append_child(pugi::node_pcdata).set_value(this->_data.img_url.c_str());
  pugi::xml_node watched_eps_node = mainNode.append_child("watched_eps");
  watched_eps_node.append_child(pugi::node_pcdata).set_value(std::to_string(this->_userdata.watched_eps).c_str());
  pugi::xml_node my_start_node = mainNode.append_child("my_start");
  my_start_node.append_child(pugi::node_pcdata).set_value(this->_userdata.my_start.xml_str().c_str());
  pugi::xml_node my_end_node = mainNode.append_child("my_end");
  my_end_node.append_child(pugi::node_pcdata).set_value(this->_userdata.my_end.xml_str().c_str());
  pugi::xml_node my_score_node = mainNode.append_child("my_score");
  my_score_node.append_child(pugi::node_pcdata).set_value(std::to_string(this->_userdata.my_score).c_str());
  pugi::xml_node my_status_node = mainNode.append_child("my_status");
  my_status_node.append_child(pugi::node_pcdata).set_value(std::to_string(this->_userdata.my_status).c_str());
  pugi::xml_node rewatching_eps_node = mainNode.append_child("rewatching_eps");
  rewatching_eps_node.append_child(pugi::node_pcdata).set_value(std::to_string(this->_userdata.rewatching_eps).c_str());
  pugi::xml_node tags_node = mainNode.append_child("tags");
  tags_node.append_child(pugi::node_pcdata).set_value(this->_userdata.tags.c_str());
}
