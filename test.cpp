#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <json/json.h>
#define CURL_STATICLIB

using namespace std;
const std::string ARCHIVO_JSON = "json.json";

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/usuario/list/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    //std::cout << readBuffer << std::endl;
    remove(ARCHIVO_JSON.c_str());
    std::ofstream fescribir;
		fescribir.open(ARCHIVO_JSON.c_str(), ios::out | ios::app); // crear y agregar
		fescribir << readBuffer ;
		fescribir.close();

    ifstream ifs("json.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings
    
    //cout << "Book: " << obj["book"].asString() << endl;
    //cout << "Year: " << obj["year"].asUInt() << endl;
    //const Json::Value& characters = obj["characters"]; // array of characters
    //const Json::Value& characters = obj;
    /*for (int i = 0; i < obj.size(); i++){
        cout << "    nombre: " << obj[i]["id"].asString();
        cout << " correo: " << obj[i]["correo"].asString();
        cout << endl;
    }*/
    cout << obj << endl;
  }
  system("pause");
  return 0;
}