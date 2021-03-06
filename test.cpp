#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
//#include <json/json.h>
//#include <dist/json/json.h>
//#include <dist/json/json-forwards.h>
#include <dist/jsoncpp.cpp>

#include <algorithm>
#include <locale>
#include <iterator>

#define CURL_STATICLIB

using namespace std;
const std::string ARCHIVO_JSON = "json.json";
const std::string RUTA_RENIEC = ".env";
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string soloLetras(const std::string& str)
{
    const char CaracteresIndeseados[] = { '\"'};
    string cadenaLimpia;
    int n = str.length();
    char cadena[n + 1];
    strcpy(cadena, str.c_str());
    int Switch = 0;
    for (int i = 0; i < strlen(cadena); i++)
    {
        for (int j = 0; j < 1; j++)
            if (cadena[i] == CaracteresIndeseados[j]) Switch = 1;

        if (Switch == 0) cadenaLimpia += cadena[i];
        Switch = 0;
    }
    //cout << cadenaLimpia << endl;
    return cadenaLimpia;
}

string obtenerNombre(string dni){
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  /*string dni;
  cout << "Ingrese DNI a buscar: ";
  getline(cin,dni);*/
  curl = curl_easy_init();
  string url = "http://pad.minem.gob.pe/TICKET/Ticket/ValidarRucServiceDNI?dni="+ dni+"&tipoDoc=1";
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "code=72784658&numero_dni=72403225");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    remove(ARCHIVO_JSON.c_str());
    std::ofstream fescribir;
		fescribir.open(ARCHIVO_JSON.c_str(), ios::out | ios::app); // crear y agregar
		fescribir << readBuffer ;
		fescribir.close();

    ifstream ifs(ARCHIVO_JSON.c_str());
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); 
    string name,apellidop,apellidom ;
    name = obj["Nombres"].asString();
    apellidop = obj["ApellidoPaterno"].asString();
    apellidom = obj["ApellidoMaterno"].asString();
    //cout << soloLetras(name) << " " << soloLetras(apellidop) << " " << soloLetras(apellidom) << endl;
    /*for (int i = 0; i < obj.size(); i++){
      cout << obj[i]["id"].asString() << endl;
    }
    */
    return soloLetras(name);
  }
  return "";
}

int main(void)
{
  /*CURL *curl;
  CURLcode res;
  std::string readBuffer;
  string dni;
  cout << "Ingrese DNI a buscar: ";
  getline(cin,dni);
  curl = curl_easy_init();
  string url = "http://pad.minem.gob.pe/TICKET/Ticket/ValidarRucServiceDNI?dni="+ dni+"&tipoDoc=1";
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "code=72784658&numero_dni=72403225");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    remove(ARCHIVO_JSON.c_str());
    std::ofstream fescribir;
		fescribir.open(ARCHIVO_JSON.c_str(), ios::out | ios::app); // crear y agregar
		fescribir << readBuffer ;
		fescribir.close();

    ifstream ifs(ARCHIVO_JSON.c_str());
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); 
    string name,apellidop,apellidom ;
    name = obj["Nombres"].asString();
    apellidop = obj["ApellidoPaterno"].asString();
    apellidom = obj["ApellidoMaterno"].asString();
    cout << soloLetras(name) << " " << soloLetras(apellidop) << " " << soloLetras(apellidom) << endl;
    
  }*/
  string dni;
  cout << "Ingrese DNI a buscar: ";
  getline(cin,dni);
  cout << obtenerNombre(dni) << endl;
  system("pause");
  return 0;
}