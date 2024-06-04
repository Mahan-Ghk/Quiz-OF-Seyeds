#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")

#define CURL_STATICLIB
#include <iostream>
#include <string>

#include "curl/curl.h"
#include "Header.h"
static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

int main()
{
	std::string result;
	CURL* curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		//curl_easy_setopt(curl, CURLOPT_URL, "https://tcno.co/hello.txt");
		curl_easy_setopt(curl, CURLOPT_URL, "https://opentdb.com/api.php?amount=10&category=9&difficulty=easy&type=multiple");
		/*		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);*/
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (CURLE_OK != res) {
			std::cerr << "CURL error: " << res << '\n';
		}
	}
	curl_global_cleanup();
	std::cout << result << "\n\n";
}