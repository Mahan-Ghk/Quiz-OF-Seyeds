#include <iostream>
#include <string>
#include <fstream>
#pragma once
//intro :

int find_category(std::string Category)
{
	std::ofstream category_file;
	if (category_file.is_open())
	{
		category_file.open("Categoriess.txt", std::ios::out);
		std::string Category_in_file;
		int t = 0;
		while (Category_in_file != NULL)
		{
			category_file >> Category_in_file;
			if (Category == Category_in_file)
			{
				return t;
			}
			else
			{
				t++;
			}
		}
	}
}
std::string URL_maker(std::string Difficulty , std::string Category)
{
	std::string url = "https://opentdb.com/api.php?amount=5&category=9&difficulty=" + Category + "&type=multiple";
	return url;
}