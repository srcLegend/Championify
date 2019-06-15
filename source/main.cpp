#include <curl/curl.h>
#include <rapidjson/document.h>
#include <iostream>
#include <string>
#include <vector>
//#include "learn.h"
//#include "request.h"

size_t curlCallback(void *contents, size_t size, size_t nmemb, std::string *data) {
	size_t newLength = size * nmemb;
	try {
		data->append((char *)contents, newLength);
	} catch (std::bad_alloc) {
		std::cerr << "Memory problems!" << std::endl;
		return 1;
	}
	return newLength;
}

void testing(std::string &data) {
	rapidjson::Document document;
	document.Parse(data.c_str());
	/*
	{
		"status":
		{
			"message":"Forbidden",
			"status_code":403
		}
	}
	*/
	std::string key;
	std::string key2;
	for (auto i = document.MemberBegin(); i != document.MemberEnd(); ++i) {
		key = i->name.GetString();
		if (key == "status") {
			for (auto a = document[std::to_string(key)].MemberBegin(); a != document[std::to_string(key)].MemberEnd(); ++a) {
				key2 = a->name.GetString();
				std::cout << "Key: " << key2 << "\n";
			}
			std::cout << "Key: " << key << "\n";
		}
	}

	if (document["status"].HasMember("message")) {
		std::cout << "status exists\n";
		if (document["status"]["message"].IsString()) {
			std::cout << "status is a string and its value is : " << document["status"]["message"].GetString() << std::endl;
		} else {
			std::cerr << "status is a not string" << std::endl;
		}
	} else {
		std::cerr << "status doesn't exist" << std::endl;
	}
}

int main() {
		// Brazil, EUNE, EUW, Japan, Korea, Latin America North, Latin America South, NA, Oceania, Turkey, Russia, PBE
	std::vector<std::string> regionalEndpoint = {"br1", "eun1", "euw1", "jp1", "kr", "la1", "la2", "na1", "oc1", "tr1", "ru", "pbe1"};
		// Brazil, EUNE, EUW, Japan, Korea, Latin America North, Latin America South, NA, Oceania, Turkey, Russia, PBE
	enum Regions { BR, EUNE, EUW, JP, KR, LAN, LAS, NA, OCE, TR, RU, PBE };

	const std::string api = "RGAPI-240a2121-e6e2-4424-83fe-ab2996bcfb4b";
	const std::string apiMethod = "/lol/summoner/v4/summoners/by-name/";
	const std::string apiValue = "AzirionSol";
	std::string host = regionalEndpoint[NA] + ".api.riotgames.com";
	std::string link = "https://" + host + apiMethod + apiValue + "?api_key=" + api;

	std::cout << host << std::endl;

	CURL *curlHandle;
	CURLcode response;
	std::string data;

	curl_global_init(CURL_GLOBAL_ALL);
		// Init the curl session
	curlHandle = curl_easy_init();
		// Specify URL to get
	curl_easy_setopt(curlHandle, CURLOPT_URL, link.c_str());
		// No need to verify SSL certificate of HTTPS connections
	curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
		// Send all data to this function
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, curlCallback);
		// We pass our 'chunk' struct to the callback function
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &data);
		// Some servers don't like requests that are made without a user-agent field, so we provide one
	curl_easy_setopt(curlHandle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		// Get it!
	response = curl_easy_perform(curlHandle);

		// Check for errors
	if (response != CURLE_OK) {
		std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(response) << std::endl;
	} else {
		std::cout << response << std::endl;
		std::cout << data << std::endl;
	}

	std::cout << regionalEndpoint[NA] << std::endl;

	testing(data);
		// Cleanup curl stuff once done
	curl_easy_cleanup(curlHandle);
		// Done with libcurl, so clean it up
	curl_global_cleanup();
	return 0;
}
