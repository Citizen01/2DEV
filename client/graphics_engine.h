#pragma once

#include <irrlicht.h>
#include "Cgui.h"
#include "game.h"
#include "map.h"
#include "plane.h"
#include "MainEventListener.h"

class Map;
class Plane;
class game;

class graphics_engine : public engine
{
private:
	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* smgr; //Scene manager
	Cgui* cegui;
	MainEventListener* mainrcvr;


public:
	graphics_engine(game*);
	~graphics_engine(void);

	Map loadMap(std::string); //TODO: A bouger dans game engine
	Plane loadPlane(std::string); //TODO: A bouger dans game engine

	void frame();

	void on_engines_linked();

	//// GETTERS ////
	inline irr::IrrlichtDevice* getDevice() { return device; }
	inline irr::video::IVideoDriver* getDriver() { return driver; }
	inline irr::scene::ISceneManager* getSceneManager() { return smgr; }
	inline Cgui* getCegui() { return cegui; }
	inline MainEventListener* getEventListener() { return mainrcvr; }

	//// SETTERS ////
		//Todo
};
