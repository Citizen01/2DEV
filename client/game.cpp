
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
	
	//Cette partie reste là le temps des tests
	IrrlichtDevice* device = getGraphicEngine()->getDevice();
	video::IVideoDriver* driver = getGraphicEngine()->getDriver();
	scene::ISceneManager* smgr = getGraphicEngine()->getSceneManager();

	// add camera
    scene::ICameraSceneNode* camera =
        smgr->addCameraSceneNodeFPS(0,100.0f,5.2f);

    camera->setPosition(core::vector3df(2700*2,255*2,2600*2));
    camera->setTarget(core::vector3df(2397*2,343*2,2700*2));
    camera->setFarValue(420000.0f);

    // disable mouse cursor
    device->getCursorControl()->setVisible(false);

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
            // Also print terrain height of current camera position
            // We can use camera position because terrain is located at coordinate origin
			scene::ITerrainSceneNode* terrain = theMap.getTerrain();
            str += " Height: ";
            str += terrain->getHeight(camera->getAbsolutePosition().X,
                    camera->getAbsolutePosition().Z);

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
    }
}
