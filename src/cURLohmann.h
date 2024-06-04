#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "curl/curl.h"
#include "nlohmann/json.hpp"
//#pragma once
//intro :
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
static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}
void curler(std::string url)
{
	std::string result;
	CURL* curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		//curl_easy_setopt(curl, CURLOPT_URL, "https://tcno.co/hello.txt");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (CURLE_OK != res) {
			std::cerr << "CURL error: " << res << '\n';
		}
	}
	curl_global_cleanup();
	std::cout << result << "\n\n";
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int find_category(std::string Category)
{
	/*std::ofstream category_file;
	if (category_file.is_open())
	{
		category_file.open("Categoriess.txt", std::ios::in| std::ios::out);
		char Category_in_file[128];
		int t = 0;
		while (Category_in_file != NULL)
		{
			category_file << Category_in_file;
			if (Category == Category_in_file)
			{
				return t;
			}
			else
			{
				t++;
			}
		}
	}*/
	std::vector<std::vector<std::string>> categorey_list = { {"General Knowledge", "9"},
		{"Books", "10"},
		{"Film", "11"},
		{"Music", "12" },
		{"Musicals & Theatres", "13" },
		{"Television", "14" },
		{"Video Games", "15" },
		{"Board Games", "16"},
		{"Science & Nature", "17"},
		{"Computers", "18"},
		{"Mathematics", "19"},
		{"Mythology", "20"},
		{"Sports", "21"},
		{"Geography", "22"},
		{"History", "23"},
		{"Politics", "24"},
		{"Art", "25"},
		{"Celebrities", "26"},
		{"Animals", "27"},
		{"Vehicles", "28"},
		{"Comics", "29"},
		{"Gadgets", "30"},
		{"Japanese Anime & Manga", "31"},
		{"Cartoon & Animations", "32"} };
	for (int i = 0; i < categorey_list.size(); ++i)
	{
		if (categorey_list[i][0] == Category)
		{
			return i+9;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string URL_maker(std::string Difficulty, std::string Category)
{
	
	int cate_num = find_category(Category);
	std::string url = "https://opentdb.com/api.php?amount=5&category="+std::to_string(cate_num)+"&difficulty=" + Difficulty + "&type=multiple";
	return url;
	//curler(url);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
