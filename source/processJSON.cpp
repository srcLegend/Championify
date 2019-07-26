#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <rapidjson/document.h>

//template <typename T1, typename T2> void setValue(T1 &document, std::string &keyName, T2 &value) {
//	if (typeid(value) == typeid(std::string)) {
//		value = document[keyName.c_str()].GetString();
//	} else if (typeid(value) == typeid(std::vector<std::string>)) {
//		value.push_back(document[keyName.c_str()].GetString());
//	}
//}

template <typename T1, typename T2> void parseRecursively(T1 &document, std::string &keyName, T2 &value) {
	if (document.HasMember(keyName.c_str())) {
		std::vector<std::string> tempVector;
		tempVector.push_back(document[keyName.c_str()].GetString());

		if (typeid(value) == typeid(std::string)) {
			//value = tempVector[0];
			std::cout << "Issa string" << std::endl;
		} else if (typeid(value) == typeid(std::vector<std::string>)) {
			value.push_back(document[keyName.c_str()].GetString());
			std::cout << "Issa vector" << std::endl;
		}
	} else {
		for (auto &i : document.GetObject()) {
				// GetType() types are : Null = 0, False = 1, True = 2, Object = 3, Array = 4, String = 5, Number = 6
			switch (document[i.name].GetType()) {
				case 0: break;
				case 1: break;
				case 2: break;
				case 3: {
					parseRecursively(document[i.name], keyName, value);
					break;
				}
				case 4: break;
				case 5: {
					if (document.HasMember(keyName.c_str())) {
						//value.push_back(i.value.GetString());
					}
					break;
				}
				case 6: break;
				default: {
					std::cerr << "Unknown key type : " << i.name.GetString() << std::endl;
					//value.push_back("Error");
					break;
				}
			}
		}
	}
}

void stringParseJSON(std::string &data, std::string keyName, std::string &stringValue) {
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
		stringValue = "Error";
	} else {
		std::vector<std::string> vectorValue;
		//std::string testValue;
		parseRecursively(document, keyName, vectorValue);
		//parseRecursively(document, keyName, testValue);
		if (vectorValue[0] == "Error") {
			std::cerr << "Value not found" << std::endl;
			stringValue = "Error";
		} else {
			stringValue = vectorValue[0];
		}
	}
}
