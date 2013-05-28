#pragma once

#include <irrlicht.h>
#include <stdio.h>
#include <string>
#include <io.h>

using namespace std;
using namespace irr;

class Map
{

private:
	string _name; //Nom de la map
	string _path; //Chemin vers le dossier de la map (inclut)
	string _heightmap; //Nom du fichier de la heightmap
	string _texture; //Nom du fichier de la texture
	core::vector3df _position; //Position (X; Z; Y)
	core::vector3df _rotation; //Rotation (X; Z; Y)
	core::vector3df _scale; //Taille (X; Z; Y)

	//Objet terrain chargé d'après les infos d'au-dessus
	scene::ITerrainSceneNode* _terrain;

	bool loadTerrain(); //Permet de charger le terrain
	bool loadSkybox(); //Permet de charger la skybox
	bool loadObjects(); //Permet de charger les objets (soon)

public:

	Map(string name,
		core::vector3df position = core::vector3df(0, 0, 0),
		core::vector3df rotation = core::vector3df(0, 0, 0),
		core::vector3df scale = core::vector3df(120, 60, 120));


	/// Getters and Setters ///
	
	//Name
	bool setName(string s);
	string getName();
	

	//Path
	bool setPath(string s);
	string getPath();
	

	//Heightmap
	bool setHeightmap(string s);
	string getHeightmap();
	

	//Texture
	bool setTexture(string s);
	string getTexture();
	

	//Position
	bool setPosition(core::vector3df position);
	core::vector3df getPosition();
	

	//Rotation
	bool setRotation(core::vector3df rotation);
	core::vector3df getRotation();
	

	//Scale
	bool setScale(core::vector3df scale);
	core::vector3df getScale();

	//Terrain
	scene::ITerrainSceneNode* getTerrain();

	/// Dump ///
	void dump();
};