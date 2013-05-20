﻿#pragma once

#include <string>
#include "game_engine.h"
#include "graphics_engine.h"
#include "network_engine.h"
#include "sound_engine.h"

const std::string PATH_TO_MEDIA = "../Media";
//Need to be replaced with a conf file such as an XML 
//TODO: XML_Manager class to easily read and write in xml files
const std::string MAP_HEIGHTMAP_NAME = "heightmap.png";
const std::string MAP_TEXTURE_NAME = "texture.png";

class game_engine;
class graphics_engine;
class network_engine;
class sound_engine;

class App
{
private:
	static App* instance; //Contiendra la seule instance de App

	//Les différents modules qui compose le jeu
	game_engine* g;
	graphics_engine* gfx;
	network_engine* n;
	sound_engine* s;

	//Boolean du controle du jeu (mettre à false pour quitter)
	bool running;
	
	App(); //Seul getSingleton() doit appeler ce constructeur.

public:
	//Instancie (si non instancié) et retourne un pointeur d'App
	static App* getSingleton();
	~App();

	//Démarre une partie sur <mapname>
	int run();

	//// GETTERS ////
	inline game_engine* getGameEngine() { return g; }
	inline graphics_engine* getGraphicEngine() { return gfx; }
	inline network_engine* getNetworkEngine() { return n; }
	inline sound_engine* getSoundEngine() { return s; }
};

