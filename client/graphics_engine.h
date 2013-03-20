#pragma once

#include "engine.h"
#include "map.h"

class game;

class graphics_engine : public engine
{
private:
	IrrlichtDevice* device;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr; //Scene manager

public:
	graphics_engine(game*);
	~graphics_engine(void);

	Map loadMap(std::string mapname);

	void frame();

	//// GETTERS ////
	inline IrrlichtDevice* getDevice() { return device; }
	inline video::IVideoDriver* getDriver() { return driver; }
	inline scene::ISceneManager* getSceneManager() { return smgr; }

	//// SETTERS ////
		//Todo
};

