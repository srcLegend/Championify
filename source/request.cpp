#include <iostream>
#include <string>
#include <curl/curl.h>

size_t curlCallback(void *contents, size_t size, size_t nmemb, std::string *data) {
	size_t newLength = size * nmemb;
	try {
		data->append((char *)contents, newLength);
	} catch (std::bad_alloc &e) {
		std::cerr << "Memory problems: " << &e << std::endl;
		return 1;
	}
	return newLength;
}

std::string request(std::string &link, bool &redirected, bool cleanup) {
	CURL *curlHandle;
	std::string data;
	redirected = false;

	if (&curlHandle) {
		CURLcode response;
		long responseCode;

		curl_global_init(CURL_GLOBAL_WIN32);
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
			response = curl_easy_getinfo(curlHandle, CURLINFO_RESPONSE_CODE, &responseCode);
			if ((response == CURLE_OK) && ((responseCode / 100) == 3)) {
				redirected = true;
			}
		}


		if (cleanup) {
				// Cleanup curl stuff once done
			curl_easy_cleanup(curlHandle);
				// Done with libcurl, so clean it up
			curl_global_cleanup();
		}
	}
	return data;
}
