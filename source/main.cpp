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
	public:
		Champion(void) {}
		~Champion(void) {}
		void setValues(std::string &data) {
			championValues.push_back(stringParseJSON(data, "version"));
			championValues.push_back(stringParseJSON(data, "id"));
			championValues.push_back(stringParseJSON(data, "key"));
			championValues.push_back(stringParseJSON(data, "name"));
		}
};


class Line {
	private:
		double length;

	public:
		void setLength(double len) {
			length = len;
		}
		double getLength(void) {
			return length;
		}
			// This is the constructor declaration
		Line(void) {
			length = 0;
			std::cout << "Object is being created" << std::endl;
		}
			// This is the destructor: declaration
		~Line(void) {
			std::cout << "Object is being deleted" << std::endl;
		}
};


void testClass() {
	Line line;
		// Set line length
	line.setLength(6.0);
	std::cout << "Length of line : " << line.getLength() << std::endl;
}


int main() {
	testClass();

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
	std::string version;
	std::string language;

	data = request(links[0], redirected, false);
	stringParseJSON(data, "v", version);
	stringParseJSON(data, "l", language);

	links.push_back("https://ddragon.leagueoflegends.com/cdn/" + version + "/data/" + language + "/champion.json");
	links.push_back("https://ddragon.leagueoflegends.com/cdn/" + version + "/data/" + language + "/item.json");

	std::vector<std::string> championIds;
	data = request(links[1], redirected, false);
		//stringParseJSON(data, "id", championIds);
	for (auto &i : championIds) {
		std::cout << i << "\n";
	}

	//links.push_back("https://champion.gg/champion/" + championIds[0] + "/" + roles[0]);
	//data = request(links[3], redirected, true);
	if (!redirected) {
		std::cout << data << std::endl;
	}

	system("pause");
	return 0;
}
