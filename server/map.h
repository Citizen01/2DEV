#pragma once

#include <string>
#include <irrlicht.h>
#include "collidableObject.h"

class Map : public collidableObject
{
private:

	std::string m_Name; //Nom de la map

	irr::core::vector3df m_Scale; //Taille (X; Z; Y)

	//Objet terrain chargé d'après les infos d'au-dessus
	irr::scene::ITerrainSceneNode* m_Terrain;

	bool loadTerrain(); //Permet de charger le terrain

public:

	Map(std::string name, irr::core::vector3df scale = irr::core::vector3df(120, 60, 120));
	
	std::string getName();	

	irr::core::vector3df getScale();

	irr::scene::ITerrainSceneNode* getTerrain();
	inline irr::scene::ISceneNode* getNode() { return static_cast<irr::scene::ISceneNode*>(m_Terrain);  }
};