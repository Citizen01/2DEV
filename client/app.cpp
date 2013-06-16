#include <irrlicht.h>
#include <irrKlang.h>
#include <iostream>
#include "app.h"
#include "server_manager.h"
#include "events.h"
#include "utils.h"
#include "XMLParser.h"
#include "GLOBALS.h"
#include "ui_windows.h"

using namespace std;
using namespace irr;
using namespace constants;

App* App::instance = NULL;

App::App()
{
	initialiseGlobals();
	loadSettings();
	loadBinds();

	//Crée et store les différents modules
	gfx = new graphics_engine(this);
	g = new game_engine(this);
	n = new network_engine(this);
	s = new sound_engine(this);

	/// Linkage des modules entre eux ///
	//game_engine aux autres//
	g->link_graphics_engine(gfx);
	g->link_network_engine(n);
	g->link_sound_engine(s);

	//graphics_engine aux autres//
	gfx->link_game_engine(g);
	gfx->link_network_engine(n);
	gfx->link_sound_engine(s);

	//network_engine aux autres//
	n->link_game_engine(g);
	n->link_graphics_engine(gfx);
	n->link_sound_engine(s);

	//sound_engine aux autres//
	s->link_game_engine(g);
	s->link_graphics_engine(gfx);
	s->link_network_engine(n);

	server_manager::getSingleton()->loadServers();

	running = true;
}

App* App::getSingleton()
{
	if (!instance)
		instance = new App();
	return instance;
}


App::~App()
{
	delete g;
	delete gfx;
	delete n;
	delete s;
}

int App::run()
{
	IrrlichtDevice* device = getGraphicEngine()->getDevice();

	show_main_menu(true);

	scene::IMeshSceneNode* box = device->getSceneManager()->addCubeSceneNode(1, 0, -1, core::vector3df(0, 0, 0), core::vector3df(0, 0, 0), core::vector3df(10000, 1, 10000));
	box->setMaterialTexture(0, getGraphicEngine()->getDriver()->getTexture("../Media/texture.jpg"));
	box->setMaterialFlag(video::EMF_LIGHTING, false);
	
	//scene::ISceneManager* smgr = App::getSingleton()->getGraphicEngine()->getSceneManager();
	//std::string modefile = constants::PATH_TO_MEDIA + "/projectiles/missile/missile.3DS";
	//scene::IAnimatedMeshSceneNode* missile = smgr->addAnimatedMeshSceneNode(smgr->getMesh(modefile.c_str()));
 // 
	////On met l'auto-éclairage (debug)
	//missile->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	//
	//missile->setPosition(core::vector3df(10, 2, 10));

	int lastFPS = -1;
	while(device->run() && running)
	{
		//Chaque moteur doit faire son boulot
		getNetworkEngine()->frame();
		getGameEngine()->frame();
		getSoundEngine()->frame();
		getGraphicEngine()->frame();
	}
	cout << "Quitting ..." << endl;

	//Logique pour quitter le jeu:
	//TODO: quitter le jeu proprement (destructeurs des engines ?)

	return 0;
}

void App::stop()
{
	running = false;
}

////////////// SETTINGS ////////////////
void App::loadSettings(){
	XMLParser settingsParser("../config/coreconfig.xml");
	if (!settingsParser.populateSettings(settings))
	{
		loadDefaultSettings();
	}
}

void App::loadDefaultSettings(){
	settings["nickname"] = "Unknown_Pilot";
	settings["anti_aliasing"] = "0";
	settings["display_windowed"] = "1";
	settings["current_skin"] = "default";
}

////////////// BINDS ////////////////
void App::loadBinds(){
	XMLParser coreParser("../config/coreconfig.xml");
	if (!coreParser.populateBind(binds))
	{
		loadDefaultBinds();
	}
}

void App::loadDefaultBinds(){
	binds[ACCELERATE] = KEY_KEY_Z;
	binds[DECELERATE] = KEY_KEY_S;
	binds[LEFT] = KEY_KEY_Q;
	binds[RIGHT] = KEY_KEY_D;
	binds[DIVE] = KEY_UP;
	binds[STRAIGHTEN] = KEY_DOWN;
	binds[ROLL_LEFT] = KEY_LEFT;
	binds[ROLL_RIGHT] = KEY_RIGHT;
	binds[PRIMARY_FIRE] = KEY_LBUTTON;
	binds[SECONDARY_FIRE] = KEY_RBUTTON;
	binds[EQUIPMENT] = KEY_SPACE;
	binds[TOGGLEMENU] = KEY_ESCAPE;
}