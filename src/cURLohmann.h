#include "curl/curl.h"
#include <iostream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
//using namespace nlohmann;
//using json = nlohmann::json;
//#pragma once
//intro :
#include "gui/imgui/imgui.h"
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
static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	// Cast userdata back to std::string*
	std::string* data = reinterpret_cast<std::string*>(userdata);
	// Append the received data to the string
	data->append(ptr, size * nmemb);
	return size * nmemb;
}
std::vector <std::string> curler(std::string url , int t)
{
	std::string result;
	CURL* curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	//std::vector <std::vector <std::string>> vec[10][5];
	std::vector<std::string> vec;
	if (curl)
	{
		//curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_URL, "https://mocki.io/v1/01865c09-0e0c-4352-80d5-cbc7288adb20");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

		// Set the user data pointer to be passed to the callback
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		res = curl_easy_perform(curl);
		if (CURLE_OK != res) 
		{
			std::cerr << "\nCURL error: " << res << '\n';
		}
		else
		{
			try
			{
				nlohmann::json json_data = nlohmann::json::parse(result);
				// Print the entire JSON data (optional)
				for (int i = 0; i < t; ++i)
				{
					/*
					char* decoded = curl_unescape(json_data["results"][i]["question"], 12);//.value<char*>()
					char* decoded = curl_unescape(json_data["results"][i]["correct_answer"], 12);
					char* decoded = curl_unescape(json_data["results"][i]["incorrect_answers"], 12);
					*/
					
					//std::cout << json_data["results"][i]["question"] << std::endl;
					//std::cout << json_data["results"][i]["correct_answer"] << std::endl;
					//std::cout << json_data["results"][i]["incorrect_answers"] << std::endl;
					/*vec[i][0].push_back(json_data["results"][i]["question"]);
					vec[i][1].push_back(json_data["results"][i]["correct_answer"]);
					vec[i][2].push_back(json_data["results"][i]["incorrect_answers"][0]);
					vec[i][3].push_back(json_data["results"][i]["incorrect_answers"][1]);
					vec[i][4].push_back(json_data["results"][i]["incorrect_answers"][2]);*/
					vec.push_back(json_data["results"][i]["question"]);
					vec.push_back(json_data["results"][i]["correct_answer"]);
					vec.push_back(json_data["results"][i]["incorrect_answers"]);

					//return vec;
					//std::string t = json_data["results"][i]["question"];
					//ImGui::Text(t.c_str());
					
				}
			}
			catch (nlohmann::json::parse_error& e) 
			{
				std::cerr << "\nError parsing JSON: " << e.what() << std::endl;
			}
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	//return vec[10][5];
	return vec;
	//return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string find_category(int Category)
{
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
		if (categorey_list[i][1] == std::to_string(Category))
		{
			return categorey_list[i][0];
		}
	}
}
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
int tedad_soal(std::string Mode)
{
	if (Mode == "PvP" || Mode == "pvp")
	{
		return 5;
	}
	else if (Mode == "Survival" || Mode == "survival")
	{
		return 20;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string URL_maker(std::string Difficulty, std::string Category, int t)
{
	int cate_num = find_category(Category);
	std::string url = "https://opentdb.com/api.php?amount="+std::to_string(t)+"&category="+std::to_string(cate_num)+"&difficulty="+Difficulty+"&type=multiple";
	return url;
	//curler(url);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////