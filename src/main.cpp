#include <iostream>
#include <string>
#include "cURLohmann.h"

int main()
{

    std::string Categorey = "Japanese Anime & Manga";
    std::string Dificulty = "easy";
    std::string url = URL_maker(Dificulty, Categorey);
    nlohmann::json json_string = curler(url);
    ////////////////////////////////////////////////////
    std::cout << "\n\n\n\n\n\n";

}