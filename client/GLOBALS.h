#pragma once

#include <string>
#include <irrlicht.h>
#include <map>
#include <vector>

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

	enum PARTICLE_TYPE
	{
		PARTICLE_FIRE_NORMAL, //Feu dirigé vers le haut
		PARTICLE_FIRE_DIRECTED, //Feu dirigé autrement (ex: propulsion)
		PARTICLE_EXPLOSION, //Explosion
		PARTICLE_SMOKE_WHITE, //Fumée blanche
		PARTICLE_SMOKE_BLACK, //Fumée noire
		PARTICLE_LIGHT_WHITE, //Lumière blanche (addLightSceneNode ?)
		PARTICLE_TYPE_COUNT //Contient le nombre de types de particules.
	};

}


struct GameRules
{
	int AmmoCost;
 
	int BulletDamages;
	int MissileDamages;
 
	int StartingMoney;
	int Bounty;
 
	int RadarReach;
 
	int FactionsCount;
	int FactionSlots;
 
	//const int PlanesCount = 5; //Compil error

	/* Il y a 5 avions en tout, et pour chaque faction (une faction par index du vector),
		* on a un tableau de bool indiquant si l'avion est disponible ou non.
		*/
	//std::vector<bool[PlanesCount]> Planes; //Impossible à utiliser sans PlanesCount
};

void initialiseGlobals();

///// Proposition /////
struct faction
{
	std::string name;
	std::vector<std::string> planes_name;
	int usedSlots;
	int maxSlots;
};

struct GameRules2
{
	int AmmoCost;

	int BulletDamages;
	int MissilesDamages;

	int Earnings;
	int StartingMoney;

	int RadarReach;
 
	std::vector<faction> Factions;
	int FactionSlots;
};
