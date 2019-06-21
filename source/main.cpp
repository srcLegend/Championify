#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include "request.hpp"

// git push test
template <typename T> std::string getValueInString(T &document, std::string &keyName) {
	int valueType = document[keyName.c_str()].GetType();
	switch (valueType) {
		case 0: { // Null
			return "0";
		}
		case 1: { // False
			return "False";
		}
		case 2: { // True
			return "True";
		}
		case 3: { // Object
			return "Object";
		}
		case 4: { // Array
			return "Array";
		}
		case 5: { // String
			return document[keyName.c_str()].GetString();
		}
		case 6: { // Number
			return std::to_string(document[keyName.c_str()].GetInt());
		}
	}
}

template <typename T> void parseRecursively(T &document, std::string &keyName, std::vector<std::string> &value) {
	if (document.HasMember(keyName.c_str())) {
		std::cout << "0. Key name : " << keyName << "\n";
		std::cout << "0. Key value : " << document[keyName.c_str()].GetString() << "\n";
		value.push_back(document[keyName.c_str()].GetString());
	} else {
		for (auto &i : document.GetObject()) {
			if (document[i.name].GetType() == 3) {
				parseRecursively(document[i.name], keyName, value);
			} else if (document.HasMember(keyName.c_str())) {
				std::cout << "2. Key name : " << i.name.GetString() << "\n";
				std::cout << "2. Key value : " << i.value.GetString() << "\n";
				value.push_back(i.value.GetString());

			} else {
				std::cout << "3. Key name : " << i.name.GetString() << "\n";
			}
		}
	}
}

void parseJSON(std::string &data, std::string keyName, std::vector<std::string> &value) {
	rapidjson::Document document;
	document.Parse(data.c_str());

	if (document.HasMember("status")) {
		std::cerr << "Connection problem : " << document["status"]["message"].GetString() << "\n";
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
	} else {
		parseRecursively(document, keyName, value);
	}
}

int main() {
	std::vector<std::string> apiDataEndpoint = { // BR, EUNE, EUW, JP, KR, LAN, LAS, NA, OCE, TR, RU, PBE
		"br1", "eun1", "euw1", "jp1",
		"kr",  "la1",  "la2",  "na1",
		"oc1", "tr1",  "ru",   "pbe1"
	};
	std::vector<std::string> realmsEndpoint = { // BR, EUNE, EUW, JP, KR, LAN, LAS, NA, OCE, TR, RU, PBE
		"br", "eune", "euw", "jp",
		"kr",  "lan",  "las",  "na",
		"oce", "tr",  "ru",   "pbe"
	};
	enum Regions {
		BR,  EUNE, EUW, JP,
		KR,  LAN,  LAS, NA,
		OCE, TR,   RU,  PBE
	};

	const std::string api          = "?api_key=RGAPI-74533ee4-c17a-45cd-8c5b-bbb24411af3a";
	std::string apiHost        = "https://" + apiDataEndpoint[NA] + ".api.riotgames.com";
	std::string staticDataHost     = "https://ddragon.leagueoflegends.com";
	std::vector<std::string> links = {
		staticDataHost + "/realms/" + realmsEndpoint[NA] + ".json",
		apiHost + "/lol/summoner/v4/summoners/by-name/" + "AzirionSol" + api,
	};
	std::string data;
	std::vector<std::string> version;
	std::vector<std::string> language;




	data = request(links[0], false);
	parseJSON(data, "v", version);
	parseJSON(data, "l", language);
	std::cout << "\n\n" << data << "\n\n" << std::endl;
	std::cout << version[0] << std::endl;
	std::cout << language[0] << std::endl;

	std::vector<std::string> cdnLinks = {
		staticDataHost + "/cdn/" + version[0] + "/data/" + language[0] + "/champion.json",
	};

	std::vector<std::string> championIds;
	std::cout << cdnLinks[0] << "\n";
	data = request(cdnLinks[0], true);
	parseJSON(data, "id", championIds);
	for (auto &i : championIds) {
		std::cout << i << "\n";
	}
	std::cout << "\n\n" << data << "\n\n" << std::endl;
	std::cout << championIds[0] << std::endl;


	system("pause");
	return 0;
}
