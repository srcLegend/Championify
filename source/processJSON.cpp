#include <iostream>
#include <string>
#include <vector>
#include <rapidjson/document.h>


template <typename T> std::string parseRecursively(T &document, std::string &keyName) {
	if (document.HasMember(keyName.c_str())) {
		return document[keyName.c_str()].GetString()
	} else {
		for (auto &i : document.GetObject()) {
				// GetType() types are : Null = 0, False = 1, True = 2, Object = 3, Array = 4, String = 5, Number = 6
			switch (document[i.name].GetType()) {
				case 0: break;
				case 1: break;
				case 2: break;
				case 3: {
					parseRecursively(document[i.name], keyName);
					break;
				}
				case 4: break;
				case 5: {
					if (document.HasMember(keyName.c_str())) {
						return i.value.GetString();
					}
					break;
				}
				case 6: break;
				default: {
					std::cerr << "Unknown key type : " << i.name.GetString() << std::endl;
					break;
				}
			}
		}
	}
	return "Error";
}

std::string parseJSON(std::string &data, std::string keyName) {
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
		std::string value = parseRecursively(document, keyName);
		if (value == "Error") {
			std::cerr << "Value not found" << std::endl;
			return "Error";
		} else {
			return parseRecursively(document, keyName);
		}
	}
}
