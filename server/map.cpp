#include "map.h"

#include <iostream>

#include "GLOBALS.h"

#include "server.h"

using namespace std;
using namespace irr;
using namespace constants;


Map::Map(string name, core::vector3df scale)
{
	objectType = 0;
	m_Name = name;
	m_Scale = scale;

	//Chargement du sol
	loadTerrain();
}

bool Map::loadTerrain()
{
	string heightmap = PATH_TO_MEDIA + "/maps/" + m_Name + "/" + MAP_HEIGHTMAP_NAME;

	if (isFile(heightmap))
	{
		// add terrain scene node
		m_Terrain = Server::getSingleton()->getSceneManager()->addTerrainSceneNode(
			heightmap.c_str(),
			0,	// parent node
			-1,	// node id
			core::vector3df(0, 0, 0),	// position
			core::vector3df(0, 0, 0),	// rotation
			m_Scale,	// scale
			video::SColor(255, 255, 255, 255),	// vertexColor
			5,	// maxLOD
			scene::ETPS_17,	// patchSize
			4	// smoothFactor
			);

		return true;
	}

	cout << "[ERROR] The path given isn't valid !" << endl;
	cout << heightmap << endl;

	return false;
}
	
string Map::getName()
{
	return m_Name;
}

core::vector3df Map::getScale()
{
	return m_Scale;
}

scene::ITerrainSceneNode* Map::getTerrain()
{
	return m_Terrain;
}