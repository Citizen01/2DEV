#include "graphics_engine.h"
#include "MainEventListener.h"
#include <iostream>

using namespace std;
using namespace CEGUI;
using namespace irr;

graphics_engine::graphics_engine()
{
	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;
	if (driverType==video::EDT_COUNT)
		return;

	// crée un device avec des paramètres spécifiques
	// on pourra rajouter des paramètres comme la v-sync, l'anti-aliasing etc
	irr::SIrrlichtCreationParameters params; //Liste des paramètres à passé lors de la création du device
	/////////////////// CONFIG ///////////////////
	//Paramètres indispensables:
	params.DriverType = driverType; //Doit être récup depuis le fichier de config
	params.WindowSize = core::dimension2d<u32>(1024, 768);//Doit être récup depuis le fichier de config
	//Paramètres supplémentaires ici:
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
	cegui = new Cgui(device, "default");

	mainrcvr = new MainEventListener();
	device->setEventReceiver(&(*mainrcvr));
	cout << "[GraphicsE] Referenced MainEventListener as default event listener !" << endl;

	// disable mouse cursor
	device->getCursorControl()->setVisible(false); // GRAPHICS CONSTRUCTOR
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

	smgr->drawAll();

	//Rendering all CEGUI elements
	System::getSingleton().renderGUI();

	// display frames per second in window title
	//int fps = driver->getFPS();
	//if (lastFPS != fps)
	//{
	//	core::stringw str = L"2DEV - Irrlicht Engine [";
	//	str += driver->getName();
	//	str += "] FPS:";
	//	str += fps;
	//	// Also print the current camera position
	//	/*scene::ITerrainSceneNode* terrain = theMap.getTerrain();
	//	str += " Position: ";
	//	str += camera->getAbsolutePosition().X;
	//	str += ", ";
	//	str += camera->getAbsolutePosition().Y;
	//	str += ", ";
	//	str += camera->getAbsolutePosition().Z;*/

	//	device->setWindowCaption(str.c_str());
	//	lastFPS = fps;
	//}
	driver->endScene(); // GRAPHICS
}

bool graphics_engine::OnEvent(const irr::SEvent& event)
{
	//Injection de l'event au moteur de CEGUI
	cegui->getRenderer().injectEvent(event);

	//Handle events here:

	return false;
}

Map graphics_engine::loadMap(std::string mapname)
{
	Map map(mapname);
	return map;
}

Plane graphics_engine::loadPlane(std::string modelname)
{
	Plane plane(modelname);
	return plane;
}