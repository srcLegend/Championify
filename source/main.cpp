#include <iostream>
#include <string>
#include <vector>
#include "processJSON.hpp"
#include "request.hpp"

class Champion {
	public:
		int asd;
};

int main() {
	enum Regions { BR, EUNE, EUW, JP, KR, LAN, LAS, NA, OCE, TR, RU, PBE };
	std::vector<std::string> realmsEndpoint = { // BR, EUNE, EUW, JP, KR, LAN, LAS, NA, OCE, TR, RU, PBE
		"br", "eune", "euw", "jp",
		"kr",  "lan",  "las",  "na",
		"oce", "tr",  "ru",   "pbe"
	};

	bool redirected;
	std::vector<std::string> links = {"https://ddragon.leagueoflegends.com/realms/" + realmsEndpoint[NA] + ".json"};
	std::vector<std::string> roles = {"Top", "Jungle", "Middle", "ADC", "Support"};

	std::string data;
	std::vector<std::string> version;
	std::vector<std::string> language;

	data = request(links[0], redirected, false);
	parseJSON(data, "v", version);
	parseJSON(data, "l", language);

	links.push_back("https://ddragon.leagueoflegends.com/cdn/" + version[0] + "/data/" + language[0] + "/champion.json");
	links.push_back("https://ddragon.leagueoflegends.com/cdn/" + version[0] + "/data/" + language[0] + "/item.json");

	std::vector<std::string> championIds;
	data = request(links[1], redirected, false);
	parseJSON(data, "id", championIds);
	for (auto &i : championIds) {
		std::cout << i << "\n";
	}

	links.push_back("https://champion.gg/champion/" + championIds[0] + "/" + roles[0]);
	data = request(links[3], redirected, true);
	if (!redirected) {
		std::cout << data << std::endl;
	}


	system("pause");
	return 0;
}
