#include "curl/curl.h"
#include <iostream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include <fstream>

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
bool error_button = false;

#define CURL_STATICLIB
static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	std::string* data = reinterpret_cast<std::string*>(userdata);
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
	std::vector<std::string> vec = {};
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		//curl_easy_setopt(curl, CURLOPT_URL, "https://mocki.io/v1/01865c09-0e0c-4352-80d5-cbc7288adb20");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
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
				for (int i = 0; i < t; ++i)
				{
					vec.push_back(json_data["results"][i]["question"]);
					vec.push_back(json_data["results"][i]["correct_answer"]);
					vec.push_back(json_data["results"][i]["incorrect_answers"][0]);
					vec.push_back(json_data["results"][i]["incorrect_answers"][1]);
					vec.push_back(json_data["results"][i]["incorrect_answers"][2]);
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
	return vec;
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
	else if (Mode == "Golden" || Mode == "golden")
	{
		return 40;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string URL_maker(std::string Difficulty, std::string Category, int t)
{
	int cate_num = find_category(Category);
	std::string url = "https://opentdb.com/api.php?amount="+std::to_string(t)+"&category="+std::to_string(cate_num)+"&difficulty="+Difficulty+"&type=multiple";
	return url;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void error_window(std::string error)
{
	ImGui::SetNextWindowSize(ImVec2(400, 400));
	if (ImGui::Begin("Error !!", &error_button,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		ImGui::Text(error.c_str());
		if (ImGui::Button("close", ImVec2(130, 50)))
		{
			error_button = false;
		}
	}ImGui::End();

}
void vec_saver(std::vector <std::string > vec)
{
	std::fstream file;
	file.open("Q_A.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < vec.size(); ++i)
	{
		file << vec[i] << "\n";
	}
}
void score_saver(std::string  name, int score, std::string Dificulty)
{
	std::vector <std::vector <std::string >> vec;
	std::fstream file;
	std::string path = "scoreboard/" + Dificulty + "scoreboard.txt";
	if (!file.is_open())
	{
		error_button = true;
		error_window("Cant open Score Board file");
	}
}
void score_reader(std::string Dificulty)
{
	std::fstream file;
	std::string path = "scoreboard/" + Dificulty + "scoreboard.txt";
	file.open(path, std::ios::in | std::ios::app);

	if (!file.is_open())
	{
		error_button = true;
		error_window("Cant open Score Board file");
	}
	else
	{
		std::string n, s;
		try
		{
			if (!(file >> n >> s))
			{
				throw 1;
			}
			else
			{
				int t = 1;
				ImGui::Text("Name     Score");
				while (!file.eof())
				{
					file >> n >> s;
					if (t == 1)
					{
						ImGui::Text("The Big Winner");
					}
					ImGui::Text(("#"+std::to_string(t)).c_str());
					ImGui::Text((n +"\t"+ s).c_str());
					ImGui::Separator();
					t++;
				}
			}
		}
		catch (...)
		{
			error_button = true;
			error_window("No Score info were save");
		}
	}
}
void Im_Spinner(const char* label, float radius, float thickness, ImU32 color) 
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 size = ImVec2(radius * 2, radius * 2);
	ImGui::Dummy(size);
	ImDrawList* DrawList = ImGui::GetWindowDrawList();
	DrawList->PathClear();
	int num_segments = 30;
	float start = fabsf(sinf(ImGui::GetTime() * 1.8f) * (num_segments - 5));
	float a_min = 3.14159265358979323846f * 2.0f * start / num_segments;
	float a_max = 3.14159265358979323846f * 2.0f * (num_segments - 3) / num_segments;
	ImVec2 centre = ImVec2(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);
	for (int i = 0; i <= num_segments; i++) 
	{
		float a = a_min + (i / (float)num_segments) * (a_max - a_min);
		DrawList->PathLineTo(ImVec2(centre.x + cosf(a + ImGui::GetTime() * 8) * radius, centre.y + sinf(a + ImGui::GetTime() * 8) * radius));
	}
	DrawList->PathStroke(color, false, thickness);
}