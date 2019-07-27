#include <iostream>
#include <string>
#include <vector>
#include "processJSON.hpp"
#include "request.hpp"
/*
  "data": {
	"Aatrox": {
	  "version": "9.14.1",
	  "id": "Aatrox",
	  "key": "266",
	  "name": "Aatrox",
*/
class Champion {
	private:
		std::vector<std::string> championValues;
		std::string version;
		std::string id;
		std::string key;
		std::string name;
	public:
		Champion(void) {}

		void setValues(std::string &data) {
			parseJSON(data, "version", version);
			parseJSON(data, "id", id);
			parseJSON(data, "key", key);
			parseJSON(data, "name", name);
		}
		std::vector<std::string> getValues(void) {
			championValues.push_back(version);
			championValues.push_back(id);
			championValues.push_back(key);
			championValues.push_back(name);
			return championValues;
		}

		~Champion(void) {}
};

int main() {
	enum Regions { BR, EUNE, EUW, JP, KR, LAN, LAS, NA, OCE, TR, RU, PBE };
	std::vector<std::string> realmsEndpoint = { // BR, EUNE, EUW, JP, KR, LAN, LAS, NA, OCE, TR, RU, PBE
		"br", "eune", "euw", "jp",
		"kr",  "lan",  "las",  "na",
		"oce", "tr",  "ru",   "pbe"
	};
	std::vector<std::string> links = {"https://ddragon.leagueoflegends.com/realms/" + realmsEndpoint[NA] + ".json"};
	std::vector<std::string> roles = {"Top", "Jungle", "Middle", "ADC", "Support"};
	std::string data;
	std::string version;
	std::string language;
	bool redirected;

	data = request(links[0], redirected, false);
	parseJSON(data, "v", version);
	parseJSON(data, "l", language);

	links.push_back("https://ddragon.leagueoflegends.com/cdn/" + version + "/data/" + language + "/champion.json");
	links.push_back("https://ddragon.leagueoflegends.com/cdn/" + version + "/data/" + language + "/item.json");

	std::vector<std::string> championIds;
	data = request(links[1], redirected, true);
	parseJSON(data, "id", championIds);
	for (auto &i : championIds) {
		std::cout << i << std::endl;
		Champion i;
		i.setValues(data);
	}

	//std::vector<std::string> championValue = i.getValues();


	//links.push_back("https://champion.gg/champion/" + championIds[0] + "/" + roles[0]);
	//data = request(links[3], redirected, true);
	//if (!redirected) {
	//	std::cout << data << std::endl;
	//}

	system("pause");
	return 0;
}
