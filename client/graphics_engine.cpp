//#include "graphics_engine.h"

#include "game.h"
#include "plane.h"

graphics_engine::graphics_engine(game* g) : engine(g)
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

	//////////////////////////////////////////////

	//Création de l'objet device (Base d'Irrlicht)
    device = createDeviceEx(params);

    if (device == 0)
        return; // could not create selected driver.

	//Shortcut pour les 2 objets les + utilisés
	driver = device->getVideoDriver();
    smgr = device->getSceneManager();

	//Gui environnement (soon)
    //env = device->getGUIEnvironment();

	//Force le driver a créer les textures au format 32bits
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
}


graphics_engine::~graphics_engine(void)
{
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
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