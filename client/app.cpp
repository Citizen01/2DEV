
#include <irrlicht.h>
#include <irrKlang.h>
#include <iostream>
#include "app.h"
#include "events.h"
#include "utils.h"

using namespace std;
using namespace irr;

App* App::instance = NULL;

App::App()
{
	//Crée et store les différents modules
	gfx = new graphics_engine();
	g = new game_engine();	
	n = new network_engine();
	s = new sound_engine();

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
	Map theMap = gfx->loadMap("mountain"); // GAME
	Plane thePlane = gfx->loadPlane("SU 25"); // GAME
	
	/// Cette partie reste là le temps des tests ///
	IrrlichtDevice* device = getGraphicEngine()->getDevice();
	video::IVideoDriver* driver = getGraphicEngine()->getDriver();
	scene::ISceneManager* smgr = getGraphicEngine()->getSceneManager();
	
	//////// Player->setPosition(core::vector3df(x,y,z)) ////////
	scene::IAnimatedMeshSceneNode* planeNode = thePlane.getMesh();
	planeNode->setPosition(core::vector3df(50000,19997,50015));
	////////////////////////////////////////////////////////////

	// add camera
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNode(0, core::vector3df(0,0,0), core::vector3df(1,0,0)); // GAME ou Local_Player constructor
	
	camera->setPosition(core::vector3df(50000,20000,50000));
	camera->setFarValue(420000.0f); //Distance d'affichage

	int lastFPS = -1;
	while(device->run() && running)
	{
		if (device->isWindowActive())
		{
			//Chaque moteur doit faire son boulot
			getNetworkEngine()->frame();
			getGameEngine()->frame();
			getSoundEngine()->frame();

			//On met a jour la pos de l'avion
			//receiver.updateMesh(); // GAME
		
			//On met à jour la pos et la rot de la caméra
			makeCockpit(camera, planeNode, core::vector3df(0, 0, -2)); // GAME

			getGraphicEngine()->frame();
		} else {
			device->yield();
		}
	}
	cout << "Quitting ..." << endl;

	//Logique pour quitter le jeu:
	//TODO: quitter le jeu proprement (destructeurs des engines ?)

	return 0;
}
