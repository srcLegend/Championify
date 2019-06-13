#include <csignal>
#include <curl/curl.h>
#include <iostream>
#include <rapidjson/document.h>
#include <string>
//#include "learn.h"
//#include "request.h"

size_t curlCallback(void *contents, size_t size, size_t nmemb, std::string *data){
	size_t newLength = size * nmemb;
	try{
		data->append((char *)contents, newLength);
	} catch (std::bad_alloc){
		std::cerr << "Memory problems!" << std::endl;
		return 1;
	}
	return newLength;
}

void signal_handler(int signal){
	if (signal == SIGABRT){
		std::cerr << "SIGABRT received" << std::endl;
	} else {
		std::cerr << "Unexpected signal " << signal << " received" << std::endl;
	}
	std::_Exit(EXIT_FAILURE);
}

void testing(std::string &data){
	//std::string json = "{\"project\":\"rapidjson\",\"stars\":10}";
	rapidjson::Document document;
	document.Parse(data.c_str());

	try{
		assert(document.HasMember("id8"));
	} catch (int e){
		std::cerr << "Member id doesn't exist!" << e << std::endl;
	}
	assert(document["id"].IsString());
	std::cout << "id = " << document["id"].GetString() << std::endl;
}

int main(){
	auto previous_handler = std::signal(SIGABRT, signal_handler);
	if (previous_handler == SIG_ERR){
		std::cerr << "Setup failed\n";
		return EXIT_FAILURE;
	}

	CURL *curlHandle;
	CURLcode response;
	std::string data;
	std::string link = "https://na1.api.riotgames.com/lol/summoner/v4/summoners/by-name/AzirionSol?api_key=RGAPI-240a2121-e6e2-4424-83fe-ab2996bcfb4b";

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
	if (response != CURLE_OK){
		std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(response) << std::endl;
	} else{
		std::cout << data << std::endl;
	}

	testing(data);
		// Cleanup curl stuff once done
	curl_easy_cleanup(curlHandle);
		// Done with libcurl, so clean it up
	curl_global_cleanup();
	return 0;
}
