#include <iostream>
#include <string>
#include <vector>
#include "parseJSON.hpp"
#include "request.hpp"


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
	std::cout << version[0] << std::endl;
	std::cout << language[0] << std::endl;

	links.push_back(staticDataHost + "/cdn/" + version[0] + "/data/" + language[0] + "/champion.json");

	std::vector<std::string> championIds;
	std::cout << links[2] << "\n";
	data = request(links[2], true);
	parseJSON(data, "id", championIds);
	for (auto &i : championIds) {
		std::cout << i << "\n";
	}
	std::cout << "\n\n" << data << "\n\n" << std::endl;
	std::cout << championIds[0] << std::endl;


	system("pause");
	return 0;
}
