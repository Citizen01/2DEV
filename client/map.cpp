#include "app.h"
#include "map.h"
#include "utils.h"
#include <iostream>

using namespace std;

Map::Map(App* ap, string name, core::vector3df position, core::vector3df rotation, core::vector3df scale)
{
	_app = ap;
	_name = name;
	_path = PATH_TO_MEDIA;
	_heightmap = MAP_HEIGHTMAP_NAME;
	_texture = MAP_TEXTURE_NAME;
	_position = position;
	_rotation = rotation;
	_scale = scale;
	//Chargement du sol
	loadTerrain();
	loadSkybox();
	//Chargement des objets à placer sur le sol (soon)
	//loadObjects();
}

bool Map::loadTerrain()
{
	if (isValidPath(_path))
	{
		string heightmap = _path + "/maps/" + _name + "/" + _heightmap;
		if (isFile(heightmap))
		{
			string texture = _path + "/maps/" + _name + "/" + _texture;
			if (isFile(texture))
			{
				// add terrain scene node
				video::IVideoDriver* driver = _app->getGraphicEngine()->getDriver();
				scene::ISceneManager* smgr = _app->getGraphicEngine()->getSceneManager();
				_terrain = smgr->addTerrainSceneNode(
					heightmap.c_str(),
					0,                  // parent node
					-1,                 // node id
					_position,     // position
					_rotation,     // rotation
					_scale,  // scale
					video::SColor ( 255, 255, 255, 255 ),   // vertexColor
					5,                  // maxLOD
					scene::ETPS_17,     // patchSize
					4                   // smoothFactor
					);

				/*core::vector3df size = _terrain->getScale();
				core::vector3df pos = _terrain->getPosition();
				_terrain->setPosition(core::vector3df(pos.X-(size.X/2), pos.Z-(size.Z/2), pos.Y-(size.Y/2)));*/
				//Auto-éclairage de la map (pour les test)
				_terrain->setMaterialFlag(video::EMF_LIGHTING, false);

				_terrain->setMaterialTexture(0,
						driver->getTexture(texture.c_str()));
	
				_terrain->setMaterialType(video::EMT_DETAIL_MAP);

				_terrain->scaleTexture(1.0f, 1.0f);

				return true;
			}
			else
			{
				cout << "[ERROR] The texture given isn't valid !" << endl;
				cout << texture << endl;
			}
		}
		else
		{
			cout << "[ERROR] The heightmap given isn't valid !" << endl;
			cout << heightmap << endl;
		}
	}
	else
	{
		cout << "[ERROR] The path given isn't valid !" << endl;
		cout << _path << endl;
	}
	return NULL;
}

bool Map::loadSkybox()
{
	video::IVideoDriver* driver = _app->getGraphicEngine()->getDriver();
	scene::ISceneManager* smgr = _app->getGraphicEngine()->getSceneManager();
	// create skybox
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
		driver->getTexture("../Media/skies/skyboxes/irrlicht2_up.jpg"),
		driver->getTexture("../Media/skies/skyboxes/irrlicht2_dn.jpg"),
		driver->getTexture("../Media/skies/skyboxes/irrlicht2_lf.jpg"),
		driver->getTexture("../Media/skies/skyboxes/irrlicht2_rt.jpg"),
		driver->getTexture("../Media/skies/skyboxes/irrlicht2_ft.jpg"),
		driver->getTexture("../Media/skies/skyboxes/irrlicht2_bk.jpg"));

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
	return true;
}

bool Map::loadObjects()
{
	//Todo
	return true;
}

//Name
bool Map::setName(string s)
{
	_name = s;
	return true;
}
	
string Map::getName()
{
	return _name;
}



//Path
bool Map::setPath(string s)
{
	if ( isDir(s) )
	{
		_path = s;
		return true;
	}
	else
		return false;
}
	
string Map::getPath()
{
	return _path;
}

//Heightmap
bool Map::setHeightmap(string s)
{
	if (isFile(s))
	{
		_heightmap = s;
		return true;
	}

	return false;
}
	
string Map::getHeightmap()
{
	return _path;
}

//Texture
bool Map::setTexture(string s)
{
	if (isFile(s))
	{
		_texture = s;
		return true;
	}

	return false;
}
	
string Map::getTexture()
{
	return _texture;
}

//Position
bool Map::setPosition(core::vector3df position)
{
	_position = position;
	return true;
}
	
core::vector3df Map::getPosition()
{
	return _position;
}

//Rotation
bool Map::setRotation(core::vector3df rotation)
{
	_rotation = rotation;
	return true;
}
	
core::vector3df Map::getRotation()
{
	return _rotation;
}

//Scale
bool Map::setScale(core::vector3df scale)
{
	_scale = scale;
	return true;
}
	
core::vector3df Map::getScale()
{
	return _scale;
}

//Terrain

scene::ITerrainSceneNode* Map::getTerrain()
{
	return _terrain;
}

void Map::dump()
{
	printf("[Object Map] => _name: '%s' \n\t _path: '%s' \n\t _heightmap: '%s' \n\t _texture: '%s' \n\t _position: {%d, %d, %d} \n\t _rotation: {%d, %d, %d} \n\t _scale: {%d, %d, %d} \n\n",
		_name, _path, _heightmap, _texture, _position.X, _position.Y, _position.Z, _rotation.X, _rotation.Y, _rotation.Z, _scale.X, _scale.Y, _scale.Z);
}

