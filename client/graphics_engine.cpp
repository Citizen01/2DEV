#include "graphics_engine.h"
#include "MainEventListener.h"
#include "app.h"
#include "particle_manager.h"
#include <iostream>

using namespace std;
using namespace CEGUI;
using namespace irr;

graphics_engine::graphics_engine(App* a) : engine(a)
{
	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;
	if (driverType==video::EDT_COUNT)
		return;

	// crée un device avec des paramètres spécifiques
	// on pourra rajouter des paramètres comme la v-sync, l'anti-aliasing etc
	irr::SIrrlichtCreationParameters params; //Liste des paramètres à passé lors de la création du device
	/////////////////// CONFIG ///////////////////
	//Paramètres indispensables:
	string ResolutionX = app->settings["resolution_x"];
	string ResolutionY = app->settings["resolution_y"];
	int x = atoi(ResolutionX.c_str());
	int y = atoi(ResolutionY.c_str());

	params.DriverType = driverType;
	params.WindowSize = core::dimension2d<u32>(x, y);
	
	//Paramètres supplémentaires ici:
	params.Fullscreen = false;

	if (app->settings["fullscreen"] == "true")
		params.Fullscreen = true;
	else
		params.Fullscreen = false;
	//////////////////////////////////////////////

	//Création de l'objet device (Base d'Irrlicht)
	device = createDeviceEx(params);

	if (device == 0)
		return; // could not create selected driver.

	//Shortcut pour les 2 objets les + utilisés
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	//Force le driver a créer les textures au format 32bits
	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	///////// Création de CEGUI avec le skin default /////////
	cegui = new Cgui(device, app);

	mainrcvr = new MainEventListener();
	device->setEventReceiver(&(*mainrcvr));
	cout << "[GraphicsE] Referenced MainEventListener as default event listener !" << endl;

	// disable mouse cursor
	device->getCursorControl()->setVisible(false);
}


graphics_engine::~graphics_engine(void)
{
	delete cegui;
	delete mainrcvr;
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void graphics_engine::frame()
{
	driver->beginScene(true, true, 0 ); // GRAPHICS

	particle_manager::getSingleton()->updateAll();
	smgr->drawAll();

	//Rendering all CEGUI elements
	System::getSingleton().renderGUI();

	driver->endScene(); // GRAPHICS
}

bool graphics_engine::OnEvent(const irr::SEvent& event)
{
	//Injection de l'event au moteur de CEGUI
	cegui->getRenderer().injectEvent(event);

	//Handle events here:

	return false;
}