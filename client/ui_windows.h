#pragma once
#include <vector>
#include <string>

//Menu principal
void create_main_menu();
void show_main_menu(bool visible);

//Fen�tre de s�l�ction de team
void create_team_join();
void show_team_join(bool visible);
void updateTeams(std::vector<std::string> values);