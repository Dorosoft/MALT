#include "data_process.hpp"
#include "pugixml.hpp"

void export_all(std::map<long, Anime>* const alist){
  pugi::xml_document doc;
  pugi::xml_node header = doc.prepend_child(pugi::node_declaration);
  header.append_attribute("version") = "1.0";
  header.append_attribute("encoding") = "UTF-8";
  pugi::xml_node mainNode = doc.append_child("list");
  for (std::map<long,Anime>::iterator it=alist->begin(); it != alist->end(); ++it){
    it->second.export_xml(mainNode);
  }
  doc.save_file("export_list.xml");
}

