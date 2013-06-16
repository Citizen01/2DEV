#include "graphics_engine.h"
#include "MainEventListener.h"
#include "app.h"
#include <iostream>

using namespace std;
using namespace CEGUI;
using namespace irr;

graphics_engine::graphics_engine(App* a) : engine(a)
{
	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;
	if (driverType==video::EDT_COUNT)
		return;

	// cr�e un device avec des param�tres sp�cifiques
	// on pourra rajouter des param�tres comme la v-sync, l'anti-aliasing etc
	irr::SIrrlichtCreationParameters params; //Liste des param�tres � pass� lors de la cr�ation du device
	/////////////////// CONFIG ///////////////////
	//Param�tres indispensables:
	params.DriverType = driverType;
	params.WindowSize = core::dimension2d<u32>(1024, 768);//Doit �tre r�cup depuis le fichier de config
	//Param�tres suppl�mentaires ici:
	params.Fullscreen = false;
	//////////////////////////////////////////////

	//Cr�ation de l'objet device (Base d'Irrlicht)
	device = createDeviceEx(params);

	if (device == 0)
		return; // could not create selected driver.

	//Shortcut pour les 2 objets les + utilis�s
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	//Force le driver a cr�er les textures au format 32bits
	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	///////// Cr�ation de CEGUI avec le skin default /////////
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

//Impl�mentation de la m�thode virtuelle pure h�rit�e de la classe engine
void graphics_engine::frame()
{
	driver->beginScene(true, true, 0 ); // GRAPHICS

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