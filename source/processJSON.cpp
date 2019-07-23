#include <iostream>
#include <string>
#include <vector>
#include <rapidjson/document.h>


template <typename T> void parseStringRecursively(T &document, std::string &keyName, std::string &stringValue) {
	if (document.HasMember(keyName.c_str())) {
		stringValue = document[keyName.c_str()].GetString();
	} else {
		for (auto &i : document.GetObject()) {
				// GetType() types are : Null = 0, False = 1, True = 2, Object = 3, Array = 4, String = 5, Number = 6
			switch (document[i.name].GetType()) {
				case 0: break;
				case 1: break;
				case 2: break;
				case 3: {
					parseStringRecursively(document[i.name], keyName, stringValue);
					break;
				}
				case 4: break;
				case 5: {
					if (document.HasMember(keyName.c_str())) {
						stringValue = i.value.GetString();
					}
					break;
				}
				case 6: break;
				default: {
					std::cerr << "Unknown key type : " << i.name.GetString() << std::endl;
					stringValue = "Error";
					break;
				}
			}
		}
	}
}

template <typename T> void parseVectorRecursively(T &document, std::string &keyName, std::vector<std::string> &vectorValue) {
	if (document.HasMember(keyName.c_str())) {
		stringValue = document[keyName.c_str()].GetString();
	} else {
		for (auto &i : document.GetObject()) {
				// GetType() types are : Null = 0, False = 1, True = 2, Object = 3, Array = 4, String = 5, Number = 6
			switch (document[i.name].GetType()) {
				case 0: break;
				case 1: break;
				case 2: break;
				case 3: {
					parseVectorRecursively(document[i.name], keyName, stringValue);
					break;
				}
				case 4: break;
				case 5: {
					if (document.HasMember(keyName.c_str())) {
						stringValue = i.value.GetString();
					}
					break;
				}
				case 6: break;
				default: {
					std::cerr << "Unknown key type : " << i.name.GetString() << std::endl;
					stringValue = "Error";
					break;
				}
			}
		}
	}
}

std::string parseJSON(std::string &data, std::string keyName, bool vector) {
	rapidjson::Document document;
	document.Parse(data.c_str());

	if (document.HasMember("status")) {
		std::cerr << "Connection problem : " << document["status"]["message"].GetString() << std::endl;
		switch (document["status"]["status_code"].GetInt()) {
			case 403: {
				std::cerr << "Probably an invalid API key" << std::endl;
				break;
			}
			default: {
				std::cerr << "Error : " << document["status"]["status_code"].GetInt() << std::endl;
				break;
			}
		}
		return "Error";
	} else {
		std::string value;
		parseStringRecursively(document, keyName, value);
		if (value == "Error") {
			std::cerr << "Value not found" << std::endl;
			return "Error";
		} else {
			return value;
		}
	}
}
