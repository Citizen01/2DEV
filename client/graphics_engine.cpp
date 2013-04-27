//#include "graphics_engine.h"

#include "game.h"
#include "plane.h"
#include <CEGUIDefaultResourceProvider.h>

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

	///////// Initialisation de CEGUI /////////
	mRenderer = &CEGUI::IrrlichtRenderer::bootstrapSystem(*device);

	//initialise resource group directories
	CEGUI::DefaultResourceProvider* rp =
        static_cast<CEGUI::DefaultResourceProvider*>
            (CEGUI::System::getSingleton().getResourceProvider());
    
	string theme = "default"; //Nom du thème
    string CEGUIpath = PATH_TO_MEDIA + "/CEGUI/" + theme ;
	printf("CEGUIpath: %s\n", CEGUIpath);
    // for each resource type, set a resource group directory
    rp->setResourceGroupDirectory("schemes", CEGUIpath + "/schemes/");
	printf("1");
    rp->setResourceGroupDirectory("imagesets", CEGUIpath + "/imagesets/");
	printf("2");
    rp->setResourceGroupDirectory("fonts", CEGUIpath + "/fonts/");
	printf("3");
    rp->setResourceGroupDirectory("layouts", CEGUIpath + "/layouts/");
	printf("4");
    rp->setResourceGroupDirectory("looknfeels", CEGUIpath + "/looknfeel/");
	printf("5");
    //rp->setResourceGroupDirectory("schemas", CEGUIpath + "/xml_schemas/");
    //rp->setResourceGroupDirectory("animations", CEGUIpath + "/animations/");

	printf("GroupDirs loaded ! \n");

	//initialise default resource groups
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");

	printf("Default groups seted ! \n");

	CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("OgreTrayImages", "MouseArrow");
	CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());
}


graphics_engine::~graphics_engine(void)
{
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void graphics_engine::frame()
{
	//Rendering all CEGUI elements
		
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