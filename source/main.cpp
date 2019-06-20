#include <iostream>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include "request.hpp"


template <typename TYPE> std::string valueString(TYPE &document, const char *keyName, int valueType, char numberType) {
	switch (valueType) {
		case 0: { // Null
			return "Null";
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
			return document[keyName].GetString();
		}
		case 6: { // Number
			switch (numberType) {
				case 'i': { // Int
					return std::to_string(document[keyName].GetInt());
				}
			}
		}
	}
}

void parseData(std::string &data, const char *keyName, int level, std::string &value) {
	rapidjson::Document document;
	document.Parse(data.c_str());
	std::string test;

	//if (document.HasMember("status")) {
	//	std::cerr << "Connection problem : " << document["status"]["message"].GetString() << "\n";
	//	switch (document["status"]["status_code"].GetInt()) {
	//		case 403: {
	//			std::cerr << "Probably an invalid API key" << std::endl;
	//			break;
	//		}
	//		default: {
	//			std::cerr << "Error : " << document["status"]["status_code"].GetInt() << std::endl;
	//			break;
	//		}
	//	}
	//	return;
	//}

	switch (level) {
		case 0: {
			if (document.HasMember(keyName)) {
				std::cout << "Document has member " << keyName << "\n";
				std::cout << "Member value is " << document[keyName].GetString() << std::endl;
			} else {
				std::cout << "Couldn't find " << keyName << std::endl;
			}
			break;
		}
		case 1: {
			for (auto &i : document.GetObject()) {
				if (document[i.name].HasMember(keyName)) {
					std::cout << "Document has member " << keyName << " at level 1\n";
					//std::cout << "Member value is " << document[i.name][keyName].GetString() << std::endl;
					test = valueString(document[i.name], keyName, document[i.name][keyName].GetType(), 'i');
					std::cout << test << std::endl;
				} else {
					std::cout << "Couldn't find " << keyName << " at level 1" << std::endl;
				}
				break;
			}
		}
	}

	for (auto &i : document.GetObject()) {
		if (i.name != "status") {
			if (i.name == keyName) {
				value = i.value.GetString();
				std::cout << "Found " << keyName << " : " << value << std::endl;
			}
		} else {
			for (auto &k : document[i.name].GetObject()) {
				if (k.name == "status_code") {
					if (k.value == 403) {
						std::cerr << "Forbidden connection. API key probably expired" << std::endl;
					}
				}
			}
		}
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

	const std::string api          = "?api_key=RGAPI-45692304-fdb5-4b93-b75a-21dc9a273bb3";
	std::string apiDataHost        = "https://" + apiDataEndpoint[NA] + ".api.riotgames.com";
	std::string staticDataHost     = "https://ddragon.leagueoflegends.com";
	std::vector<std::string> links = {
		staticDataHost + "/realms/" + realmsEndpoint[NA] + ".json",
		apiDataHost + "/lol/summoner/v4/summoners/by-name/" + "AzirionSol" + api,
	};
	std::string data;
	std::string version;
	std::string language;

	request(links[0], data, false);
	parseData(data, "v", 0, version);
	parseData(data, "l", 0, language);


	std::cout << "\n\n" << data << "\n\n" << std::endl;
	std::cout << version << std::endl;
	std::cout << language << std::endl;

	std::vector<std::string> cdnLinks = {
		staticDataHost + "/cdn/" + version + "/data/" + language + "champion.json"
	};

	request(cdnLinks[0], data, true);


	system("pause");
	return 0;
}
