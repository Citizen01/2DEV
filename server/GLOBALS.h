#pragma once

#include <string>
#include <vector>
#include <map>

#include <irrlicht.h>

namespace constants {

	//Toutes les constantes pour le fonctionnement interne du jeu
	const std::string PATH_TO_MEDIA = "../Media";
	const std::string MAP_HEIGHTMAP_NAME = "heightmap.png";

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

struct FactionSpecs
{
	std::string Name;
	std::vector<std::string> PlanesName;
	int UsedSlots;
	int MaxSlots;
};

struct GameRules
{
	int AmmoCost;

	int BulletDamages;
	int MissilesDamages;

	int Earnings;
	int StartingMoney;

	int RadarReach;
 
	std::vector<FactionSpecs> Factions;
	int FactionSlots;
};