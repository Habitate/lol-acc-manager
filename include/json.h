#pragma once

#include <string>

namespace json{
    std::string parse_for(const std::string& json, const std::string& field);
    std::string recieve_from(const std::string& url);
}