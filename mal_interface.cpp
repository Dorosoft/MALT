#include "mal_interface.hpp"

static bool AUTHENTIFIED;
static std::string MALACCOUNT;

static bool CURLHANDLE;
static CURL *curl;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
  ((std::string*)userp)->append((char*) contents, size * nmemb);
  return size * nmemb;
}

void load_user_anime_list(std::string& MALUSER, std::map<long, Anime>& dst){
  std::string MalAppInfoURL = "https://myanimelist.net/malappinfo.php?u=" + MALUSER +"&status=all";

  CURL *curl;
  CURLcode res;
  std::string buffer;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, MalAppInfoURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      std::cerr << "curl_easy_perform() failed: "<<
          curl_easy_strerror(res) << std::endl;
    curl_easy_cleanup(curl);
    load_xml_alist(&buffer, dst);
  }
}

bool verify_credentials(std::string& MALUSER, std::string& MALPWD){
  std::string Wrong = "Invalid credentials";
  std::string VerifyURL = "https://myanimelist.net/api/account/verify_credentials.xml";
  MALACCOUNT = MALUSER + ":" + MALPWD;

  if (!CURLHANDLE){
    curl = curl_easy_init();
    if (curl){
      curl_easy_setopt(curl, CURLOPT_USERPWD, MALACCOUNT.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      CURLHANDLE = true;
    }
  }
  CURLcode res;
  std::string buffer;

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, VerifyURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      std::cerr << "curl_easy_perform() failed: "<<
          curl_easy_strerror(res) << std::endl;
  }
  AUTHENTIFIED = buffer !=Wrong;
  if (AUTHENTIFIED){
    MALACCOUNT = MALUSER + ":" + MALPWD;
  }
  return AUTHENTIFIED;
}

void search_list(std::string& keywords, std::map<long, searchdata>& dst){
  if (!AUTHENTIFIED)
    throw 401;

  std::string SearchURL="https://myanimelist.net/api/anime/search.xml?q=" + keywords;

  if (!CURLHANDLE){
    curl = curl_easy_init();
    if (curl){
      curl_easy_setopt(curl, CURLOPT_USERPWD, MALACCOUNT.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      CURLHANDLE = true;
    }
  }
  CURLcode res;
  std::string buffer;

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, SearchURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      std::cerr << "curl_easy_perform() failed: "<<
          curl_easy_strerror(res) << std::endl;

    load_xml_search(&buffer, dst);
  }
}

void curl_finalize(){
  if (CURLHANDLE){
    curl_easy_cleanup(curl);
    CURLHANDLE = false;
  }
}
