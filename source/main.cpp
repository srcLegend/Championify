#include <iostream>
#include <string>
#include <vector>
#include "processJSON.hpp"
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
	enum Regions { BR, EUNE, EUW, JP, KR, LAN, LAS, NA, OCE, TR, RU, PBE };

	bool redirected;
	const std::string api = "?api_key=RGAPI-74533ee4-c17a-45cd-8c5b-bbb24411af3a";
	std::string apiHost = "https://" + apiDataEndpoint[NA] + ".api.riotgames.com";
	std::string staticDataHost = "https://ddragon.leagueoflegends.com";
	std::vector<std::string> links = {
		staticDataHost + "/realms/" + realmsEndpoint[NA] + ".json",
		apiHost + "/lol/summoner/v4/summoners/by-name/" + "AzirionSol" + api,
	};
	std::vector<std::string> roles = {"Top", "Jungle", "Middle", "ADC", "Support"};

	std::string data;
	std::vector<std::string> version;
	std::vector<std::string> language;

	data = request(links[0], redirected, false);
	parseJSON(data, "v", version);
	parseJSON(data, "l", language);

	links.push_back(staticDataHost + "/cdn/" + version[0] + "/data/" + language[0] + "/champion.json");
	links.push_back(staticDataHost + "/cdn/" + version[0] + "/data/" + language[0] + "/item.json");

	std::vector<std::string> championIds;
	data = request(links[2], redirected, false);
	parseJSON(data, "id", championIds);
	for (auto &i : championIds) {
		std::cout << i << "\n";
	}

	links.push_back("https://champion.gg/champion/" + championIds[0] + "/" + roles[0]);
	data = request(links[4], redirected, true);
	if (!redirected) {
		std::cout << data << std::endl;
	}


	system("pause");
	return 0;
}
