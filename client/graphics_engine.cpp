//#include "graphics_engine.h"

#include "game.h"
#include "plane.h"

graphics_engine::graphics_engine(game* g) : engine(g)
{
	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;
    if (driverType==video::EDT_COUNT)
        return;

    // cr�e un device avec des param�tres sp�cifiques
    // on pourra rajouter des param�tres comme la v-sync, l'anti-aliasing etc
    irr::SIrrlichtCreationParameters params; //Liste des param�tres � pass� lors de la cr�ation du device
	/////////////////// CONFIG ///////////////////
	//Param�tres indispensables:
    params.DriverType = driverType; //Doit �tre r�cup depuis le fichier de config
    params.WindowSize = core::dimension2d<u32>(1024, 768);//Doit �tre r�cup depuis le fichier de config
	//Param�tres suppl�mentaires ici:

	//////////////////////////////////////////////

	//Cr�ation de l'objet device (Base d'Irrlicht)
    device = createDeviceEx(params);

    if (device == 0)
        return; // could not create selected driver.

	//Shortcut pour les 2 objets les + utilis�s
	driver = device->getVideoDriver();
    smgr = device->getSceneManager();

	//Gui environnement (soon)
    //env = device->getGUIEnvironment();

	//Force le driver a cr�er les textures au format 32bits
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
}


graphics_engine::~graphics_engine(void)
{
}

//Impl�mentation de la m�thode virtuelle pure h�rit�e de la classe engine
void graphics_engine::frame()
{
	//Do stuff

	
}

Map graphics_engine::loadMap(std::string mapname)
{
	Map map(parent, mapname);
	return map;
}

Plane graphics_engine::loadPlane(std::string modelname)
{
	Plane plane(parent, modelname);
	return plane;
}