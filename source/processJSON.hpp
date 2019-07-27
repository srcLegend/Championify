#pragma once
#include <string>

void parseJSON(std::string &data, std::string keyName, std::string &value);
void parseJSON(std::string &data, std::string keyName, std::vector<std::string> &value);
