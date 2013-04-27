#pragma once

#include "engine.h"
#include "map.h"
#include "plane.h"
//Test de CEGUI
#include <CEGUI.h>
#include <RendererModules\Irrlicht\CEGUIIrrlichtRenderer.h>

class Map;
class Plane;
class game;

class graphics_engine : public engine
{
private:
	IrrlichtDevice* device;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr; //Scene manager
	CEGUI::IrrlichtRenderer* mRenderer; //CEGUI

public:
	graphics_engine(game*);
	~graphics_engine(void);

	Map loadMap(std::string); //A bouger dans game engine
	Plane loadPlane(std::string); //A bouger dans game engine

	void frame();

	//// GETTERS ////
	inline IrrlichtDevice* getDevice() { return device; }
	inline video::IVideoDriver* getDriver() { return driver; }
	inline scene::ISceneManager* getSceneManager() { return smgr; }

	//// SETTERS ////
		//Todo
};
