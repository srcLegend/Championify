#include <curl/curl.h>
#include <iostream>
#include <vector>
#include "learn.h"

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp){
	std::cout << buffer << "\n" << size << "\n" << nmemb << "\n" << userp << std::endl;
	return size *nmemb;
}

void request(const char *link){
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl){
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_URL, link);

			/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
			/* Check for errors */
		if (res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

			/* always cleanup */
		curl_easy_cleanup(curl);
	}
}

int main(){
	learn();
	request("https://na1.api.riotgames.com/lol/summoner/v4/summoners/by-name/AzirionSol?api_key=RGAPI-bdb7c8fb-e61a-4336-86b4-11c62c3299b1");
	return 0;
}
