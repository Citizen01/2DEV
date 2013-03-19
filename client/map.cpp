#include "map.h"
#include "utils.h"
#include <iostream>

using namespace std;

Map::Map( string name, string path, string heightmap, string texture, core::vector3d<s32> position, core::vector3d<s32> rotation, core::vector3d<s32> scale )
{
	_name = name;
	_path = path;
	_heightmap = heightmap;
	_texture = texture;
	_position = position;
	_rotation = rotation;
	_scale = scale;
	loadTerrain();
}

bool Map::loadTerrain()
{
	if (isValidPath(_path))
	{
		string heightmap = _path + _heightmap;
		if (isFile(heightmap))
		{
			string texture = _path + _texture;
			if (isFile(texture))
			{
				// add terrain scene node
				scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
					_heightmap,
					0,                  // parent node
					-1,                 // node id
					core::vector3df(0.f, 0.f, 0.f),     // position
					core::vector3df(0.f, 0.f, 0.f),     // rotation
					core::vector3df(120.f, 60.f, 120.f),  // scale
					video::SColor ( 255, 255, 255, 255 ),   // vertexColor
					5,                  // maxLOD
					scene::ETPS_17,     // patchSize
					4                   // smoothFactor
					);

				//Auto luminescence de la map (pour les test)
				terrain->setMaterialFlag(video::EMF_LIGHTING, true);

				terrain->setMaterialTexture(0,
						driver->getTexture(_texture));
    
				terrain->setMaterialType(video::EMT_DETAIL_MAP);

				terrain->scaleTexture(1.0f, 1.0f);
			}
			else
			{
				cout << "[ERROR] The texture given isn't valid !" << endl;
			}
		}
		else
		{
			cout << "[ERROR] The heightmap given isn't valid !" << endl;
		}
	}
	else
	{
		cout << "[ERROR] The path given isn't valid !" << endl;
	}
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
bool Map::setPosition(core::vector3d<s32> position)
{
	_position = position;
	return true;
}
	
core::vector3d<s32> Map::getPosition()
{
	return _position;
}

//Rotation
bool Map::setRotation(core::vector3d<s32> rotation)
{
	_rotation = rotation;
	return true;
}
	
core::vector3d<s32> Map::getRotation()
{
	return _rotation;
}

//Scale
bool Map::setScale(core::vector3d<s32> scale)
{
	_scale = scale;
	return true;
}
	
core::vector3d<s32> Map::getScale()
{
	return _scale;
}

void Map::dump()
{
	printf("[Object Map] => _name: '%s' \n\t _path: '%s' \n\t _heightmap: '%s' \n\t _texture: '%s' \n\t _position: {%d, %d, %d} \n\t _rotation: {%d, %d, %d} \n\t _scale: {%d, %d, %d} \n\n",
		_name, _path, _heightmap, _texture, _position.X, _position.Y, _position.Z, _rotation.X, _rotation.Y, _rotation.Z, _scale.X, _scale.Y, _scale.Z);
}

