#include "json.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <sstream>

using namespace std;

string json::parse_for(const string& json, const string& field){
    auto field_start = json.find('"' + field + '"', 0);
    auto field_end = field_start + field.size() + 2; //? +2 to jump over the closing quote

    auto value_start = field_end;
    while(json[value_start] == ' ' || json[value_start] == ':' || json[value_start] == '"'){
        ++value_start;
    }

    auto value_end = value_start;
    while(json[value_end] != ',' && json[value_end] != '"' && json[value_end] != '}'){
        ++value_end;
    }

    return json.substr(value_start, value_end - value_start);
}

string json::recieve_from(const string& url){
    cURLpp::Easy easyhandle;
    ostringstream response;

    easyhandle.setOpt(curlpp::Options::Url(url));
    easyhandle.setOpt(curlpp::Options::CaInfo("cacert.pem"));
    easyhandle.setOpt(cURLpp::Options::WriteStream(&response));

    easyhandle.perform();

    return response.str();
}