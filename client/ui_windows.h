#pragma once
#include <vector>
#include <string>

//Menu principal
void create_main_menu();
void show_main_menu(bool visible);

//Fenêtre de séléction de team
void create_team_join();
void show_team_join(bool visible);
void team_join_updateTeams(std::vector<std::vector<std::string>> values);