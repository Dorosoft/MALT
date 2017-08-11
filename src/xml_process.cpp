#include <sstream>
#include "xml_process.hpp"
#include "date.hpp"


/* SAMPLE BEGIN*/
//static struct myanimedata SAMPLE = 
//{ .watched_eps = 8,
//  .my_start = Date(1,1,2005),
//  .my_end = Date(16,10,2015),
//  .my_score = 7,
//  .my_status = 1};
/* SAMPLE END */



void load_xml_alist(std::string* s_anime_list, std::map<long int, Anime> &alist){
  pugi::xml_document doc;
  pugi::xml_parse_result anime_list = doc.load_buffer(s_anime_list->c_str(), s_anime_list->size());
  std::cout << "Load result: " << anime_list.description() << std::endl;
  pugi::xml_node animeNode = doc.first_child();
  
  long int cid;
  for (pugi::xml_node cn = animeNode.child("anime"); cn; cn = cn.next_sibling())
  {
    cid = std::stol(cn.child_value("series_animedb_id"));
    Date series_start, series_end, my_start, my_end;
    series_start = convert_to_date(cn.child_value("series_start"), series_start);
    series_end = convert_to_date(cn.child_value("series_end"), series_end);
    my_start = convert_to_date(cn.child_value("my_start_date"), my_start);
    my_end = convert_to_date(cn.child_value("my_finish_date"), my_end); 
    
    struct animedata cdata; 
    cdata.title = cn.child_value("series_title");
    cdata.synonyms = cn.child_value("series_synonyms");
    cdata.type = std::stoi(cn.child_value("series_type"));
    cdata.total_eps = std::stoi(cn.child_value("series_episodes"));
    cdata.status = std::stoi(cn.child_value("series_status"));
    cdata.series_start = series_start;
    cdata.series_end = series_end;
    cdata.img_url = cn.child_value("series_image");

    struct myanimedata cudata;
    
    cudata.watched_eps = std::stoi(cn.child_value("my_watched_episodes"));
    cudata.my_start = my_start;
    cudata.my_end = my_end;
    cudata.my_score = std::stoi(cn.child_value("my_score"));
    cudata.my_status = std::stoi(cn.child_value("my_status"));
    cudata.rewatching_eps = std::stoi(cn.child_value("my_rewatching_ep"));
    cudata.tags = cn.child_value("my_tags");
        
    Anime currentanime(cid, cdata, cudata);
    alist[cid] = currentanime;
  }
}

std::string get_matching_serie_type(int id){
  std::string str[7] = {"","TV","OVA","Movie","Special","ONA","Music"};
  return str[id];
}

int get_matching_serie_status(std::string& src){
  std::string str[4] = {"","Currently Airing","Finished Airing","Not yet aired"};
  for (int k=0; k<4;++k){
    if (src == str[k])
      return k;
  }
  return 0;
}

std::string get_matching_serie_status(int id){
  std::string str[4] = {"","Currently Airing","Finished Airing","Not yet aired"};
  return str[id];
}

int get_matching_serie_type(std::string& src){
  std::string str[7] = {"","TV","OVA","Movie","Special","ONA","Music"};
  for (int k=0; k<7;++k){
    if (src == str[k]){
      return k;
    }
  }
  return 0;
}

void load_xml_search(std::string* s_anime_list, std::map<long int, searchdata> &dst){
  pugi::xml_document doc;
  pugi::xml_parse_result anime_list = doc.load_buffer(s_anime_list->c_str(), s_anime_list->size());
  std::cout << "Load result: " << anime_list.description() << std::endl;
  pugi::xml_node animeNode = doc.first_child();
  std::cout << "First Child name : " << animeNode.name() << "\n";

  struct searchdata currentdata;
  long int cid;
  std::string strbuff;
  Date series_start, series_end;

  for (pugi::xml_node cn = animeNode.child("entry"); cn; cn = cn.next_sibling())
  {
    cid = std::stol(cn.child_value("id"));
    
    currentdata.title = cn.child_value("title");
    currentdata.english = cn.child_value("english");
    currentdata.synonyms = cn.child_value("synonyms");
    strbuff = cn.child_value("type");
    currentdata.type = get_matching_serie_type(strbuff);
    currentdata.total_eps = std::stoi(cn.child_value("episodes"));
    strbuff = cn.child_value("status");
    currentdata.status = get_matching_serie_status(strbuff);
    series_start = convert_to_date(cn.child_value("start_date"), series_start);
    series_end = convert_to_date(cn.child_value("end_date"), series_end);
    currentdata.series_start = series_start;
    currentdata.series_end = series_end;
    currentdata.synopsis = cn.child_value("synopsis");
    currentdata.img_url = cn.child_value("image");

    dst[cid] = currentdata;
  }
}


std::string add_xml_anime(const struct myanimedata* data){
  std::stringstream ss;
  
  pugi::xml_document doc;
  pugi::xml_node header = doc.prepend_child(pugi::node_declaration);
  header.append_attribute("version") = "1.0";
  header.append_attribute("encoding") = "UTF-8";
  pugi::xml_node mainNode = doc.append_child("entry");
  pugi::xml_node node_eps = mainNode.append_child("episode");
  node_eps.append_child(pugi::node_pcdata).set_value((std::to_string(data->watched_eps)).c_str());

  pugi::xml_node node_status = mainNode.append_child("status");
  node_status.append_child(pugi::node_pcdata).set_value((std::to_string(data->my_status)).c_str());

  pugi::xml_node node_score = mainNode.append_child("score");
  node_score.append_child(pugi::node_pcdata).set_value((std::to_string(data->my_score)).c_str());

  pugi::xml_node node_stort = mainNode.append_child("storage_type");
  node_stort.append_child(pugi::node_pcdata).set_value("");

  pugi::xml_node node_storv = mainNode.append_child("storage_value");
  node_storv.append_child(pugi::node_pcdata).set_value("");

  pugi::xml_node node_tr = mainNode.append_child("times_rewatched");
  node_tr.append_child(pugi::node_pcdata).set_value("");

  pugi::xml_node node_rv = mainNode.append_child("rewatch_value");
  node_rv.append_child(pugi::node_pcdata).set_value("");

  pugi::xml_node node_startd = mainNode.append_child("date_start");
  node_startd.append_child(pugi::node_pcdata).set_value(data->my_start.xml_str().c_str());

  pugi::xml_node node_endd = mainNode.append_child("date_finish");
  node_endd.append_child(pugi::node_pcdata).set_value(data->my_end.xml_str().c_str());

  pugi::xml_node node_pr = mainNode.append_child("priority");
  node_pr.append_child(pugi::node_pcdata).set_value("");

  pugi::xml_node node_discuss = mainNode.append_child("enable_discussion");
  node_discuss.append_child(pugi::node_pcdata).set_value("");

  pugi::xml_node node_rewatch = mainNode.append_child("enable_rewatching");
  node_rewatch.append_child(pugi::node_pcdata).set_value("");

  pugi::xml_node node_com = mainNode.append_child("comments");
  node_com.append_child(pugi::node_pcdata).set_value("");

  pugi::xml_node node_tag = mainNode.append_child("tags");
  node_tag.append_child(pugi::node_pcdata).set_value("");
  doc.print(ss);
  return ss.str();
}

void import_xml_alist(std::string& filename, std::map<long int, Anime> &alist){
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename.c_str());


  std::cout << "Load result: " << result.description() << std::endl;
  pugi::xml_node animeNode = doc.first_child();
  
  long int cid;
  for (pugi::xml_node cn = animeNode.child("entry"); cn; cn = cn.next_sibling())
  {
    cid = std::stol(cn.attribute("dbid").value());
    Date series_start, series_end, my_start, my_end;
    series_start = convert_off_to_date(cn.child_value("series_start"), series_start);
    series_end = convert_off_to_date(cn.child_value("series_end"), series_end);
    my_start = convert_off_to_date(cn.child_value("my_start"), my_start);
    my_end = convert_off_to_date(cn.child_value("my_end"), my_end); 
    
    struct animedata cdata; 
    cdata.title = cn.child_value("title");
    cdata.synonyms = cn.child_value("synonyms");
    cdata.type = std::atoi(cn.child_value("type"));
    cdata.total_eps = std::stoi(cn.child_value("total_eps"));
    cdata.status = std::atoi(cn.child_value("status"));
    cdata.series_start = series_start;
    cdata.series_end = series_end;
    cdata.img_url = cn.child_value("img_url");

    struct myanimedata cudata;
    
    cudata.watched_eps = std::atoi(cn.child_value("watched_eps"));
    cudata.my_start = my_start;
    cudata.my_end = my_end;
    cudata.my_score = std::atoi(cn.child_value("my_score"));
    cudata.my_status = std::atoi(cn.child_value("my_status"));
    cudata.rewatching_eps = std::atoi(cn.child_value("rewatching_ep"));
    cudata.tags = cn.child_value("tags");
        
    Anime currentanime(cid, cdata, cudata);
    alist[cid] = currentanime;
  }
}
