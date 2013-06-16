#pragma once
#include <vector>
#include <string>

//Menu principal
void create_main_menu();
void show_main_menu(bool visible);

//Fenêtre de sélection de team
void create_team_selection();
void show_team_selection(bool visible);
void update_team_selection(std::vector<std::vector<std::string>> values);

//Fenêtre de selection de l'avion
void create_plane_selection();
void show_plane_selection(bool visible);
void update_plane_selection(std::vector<std::string> values);

//Menu ingame
void create_ingame_menu();
void show_ingame_menu(bool visible);