
#include <irrlicht.h>
#include <irrKlang.h>
#include "game.h"


game::game()
{
	//Crée et store les différents modules
	g = new game_engine(this);
	gfx = new graphics_engine(this);
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
}


game::~game()
{
	delete g;
	delete gfx;
	delete n;
	delete s;
}

void game::play(std::string mapname)
{
	Map theMap = gfx->loadMap(mapname);
	Plane thePlane = gfx->loadPlane("SU 25");
	
	/// Cette partie reste là le temps des tests ///
	IrrlichtDevice* device = getGraphicEngine()->getDevice();
	video::IVideoDriver* driver = getGraphicEngine()->getDriver();
	scene::ISceneManager* smgr = getGraphicEngine()->getSceneManager();

	// add camera
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0,100.0f,5.2f);

	//On attache l'avion à la camera
	scene::IAnimatedMeshSceneNode* planeNode = smgr->addAnimatedMeshSceneNode(thePlane.getMesh());
	planeNode->setPosition(core::vector3df(0,-3,15));
	planeNode->setParent(camera);

	//Need to add an event receiver here

    camera->setPosition(core::vector3df(50000,20000,50000));
    //camera->setTarget(core::vector3df(5001, 1000, 5001));
    camera->setFarValue(420000.0f); //Distance d'affichage

    // disable mouse cursor
    device->getCursorControl()->setVisible(false);

	int lastFPS = -1;
	while(device->run())
    if (device->isWindowActive())
    {
        driver->beginScene(true, true, 0 );

        smgr->drawAll();

		//Gui (soon)
        //env->drawAll();

        driver->endScene();

        // display frames per second in window title
        int fps = driver->getFPS();
        if (lastFPS != fps)
        {
            core::stringw str = L"2DEV - Irrlicht Engine [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;
            // Also print the current camera position
			scene::ITerrainSceneNode* terrain = theMap.getTerrain();
            str += " Position: ";
            str += camera->getAbsolutePosition().X;
			str += ", ";
			str += camera->getAbsolutePosition().Y;
			str += ", ";
			str += camera->getAbsolutePosition().Z;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
    }
}
