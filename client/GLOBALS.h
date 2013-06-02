#pragma once

#include <string>
#include <irrlicht.h>
#include <map>

namespace constants {
	//Toutes les constantes pour le fonctionnement interne du jeu
	const std::string PATH_TO_MEDIA = "../Media";
	const std::string MAP_HEIGHTMAP_NAME = "heightmap.png";
	const std::string MAP_TEXTURE_NAME = "texture.png";

	//Utilisé pour traduire en irr::EKEY_CODE
	//std::map<std::string,irr::EKEY_CODE> KEYMAP;

	enum ACTION_CODE
	{
		ACCELERATE,
		DECELERATE,
		LEFT,
		RIGHT,
		DIVE,
		STRAIGHTEN,
		ROLL_LEFT,
		ROLL_RIGHT,
		PRIMARY_FIRE,
		SECONDARY_FIRE,
		EQUIPMENT,
		TOGGLEMENU,
		ACTION_CODES_COUNT
	};



}