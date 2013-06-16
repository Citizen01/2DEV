#include "Cgui.h"
#include "ui_windows.h"
#include "GLOBALS.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include "dirent.h"

using namespace CEGUI;
using namespace irr;
using namespace std;
using namespace constants;

Cgui::Cgui(IrrlichtDevice* device, App* a) : irrRenderer(IrrlichtRenderer::bootstrapSystem( *device ))
{
	this->device = device;
	app = a;
	setSkin(app->settings["skin"]);

	init();
	precache();
}

Cgui::~Cgui(void)
{
}

bool Cgui::init()
{
	try{
		// initialise the required dirs for the DefaultResourceProvider
		DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>
			(System::getSingleton().getResourceProvider());

		string skins_path = PATH_TO_MEDIA + "/CEGUI/skins/";
		
		rp->setResourceGroupDirectory("schemes", string(skins_path+skin+"/schemes/").c_str());
		rp->setResourceGroupDirectory("imagesets", string(skins_path+skin+"/imagesets/").c_str());
		rp->setResourceGroupDirectory("fonts", string(skins_path+skin+"/fonts/").c_str());
		rp->setResourceGroupDirectory("layouts", string(skins_path+skin+"/layouts/").c_str());
		rp->setResourceGroupDirectory("looknfeels", string(skins_path+skin+"/looknfeel/").c_str());
		rp->setResourceGroupDirectory("schemas", "../Media/cegui/xml_schemas/");

		// set the default resource groups to be used
		Imageset::setDefaultResourceGroup("imagesets");
		Font::setDefaultResourceGroup("fonts");
		Scheme::setDefaultResourceGroup("schemes");
		WidgetLookManager::setDefaultResourceGroup("looknfeels");
		WindowManager::setDefaultResourceGroup("layouts");
		// setup default group for validation schemas
		XMLParser* parser = System::getSingleton().getXMLParser();
		if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
			parser->setProperty("SchemaDefaultResourceGroup", "schemas");

		SchemeManager::getSingleton().create( "cegui.scheme" );

		FontManager::getSingleton().create("Commonwealth-10.font");

		System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );
		device->getCursorControl()->setVisible(false); //Permet de cacher la souris de l'os

		Window* rootWindow = WindowManager::getSingleton().createWindow( "DefaultWindow", "root" );
		System::getSingleton().setGUISheet( rootWindow );

		cout << "CEGUI initialised !" << endl;

		return true;
	}
	catch (CEGUI::Exception &e)
	{
		string error = e.getMessage().c_str();
		MessageBoxA(0, error.c_str(), "CEGUI Initialisation error",	MB_ICONERROR);
		exit(5);
	}
}


bool Cgui::precache()
{
	cout << "[CEGUI] Precaching all windows for the game ..." << endl;

	create_main_menu(); //Menu principal du jeu
	create_team_selection(); //Fenêtre de selection d'une team
	create_plane_selection(); //Fenêtre de selection d'un avion
	create_ingame_menu(); //Menu lors d'une partie

	cout << "[CEGUI] Successfully precached all windows for the game !" << endl;

	//Chargement des thumbnails des avions
	cout << "[CEGUI] Precaching all images for the game ..." << endl;

	ImagesetManager& imgr = ImagesetManager::getSingleton();
	vector<string> thumbs = getPlaneThumbs();
	vector<string> planes;
	for (unsigned int i=0; i < thumbs.size(); i++)
	{
		string planename = "unknown";
		unsigned int pos1 = thumbs[i].find("thumb_");
		unsigned int pos2 = thumbs[i].find(".png");
		if (pos1 != string::npos && pos2 != string::npos)
		{
			planename = thumbs[i].substr(pos1+6, pos2-(pos1+6));
		}

		if (planename != "unknown")
		{
			planes.push_back(planename);
			imgr.createFromImageFile("plane_thumb_"+planename, "thumbs/"+thumbs[i], "imagesets");
			cout << "[INFO] " << thumbs[i] << " loaded !" << endl;
		}
	}

	cout << "[CEGUI] Successfully precached all images for the game !" << endl;

	update_plane_selection(planes);


	return true;
}


//// GETTERS AND SETTERS ////
std::string Cgui::getSkin()
{
	return skin;
}

bool Cgui::setSkin(std::string skin)
{
	//TODO: Checker si le dossier skin existe, sinon on met le default
	if (true)
	{
		this->skin = skin;
		return true;
	}
	else
	{
		this->skin = "default";
		return false;
	}
}

irr::IrrlichtDevice* Cgui::getDevice()
{
	return device;
}

CEGUI::IrrlichtRenderer& Cgui::getRenderer()
{
	return irrRenderer;
}

vector<string> Cgui::getPlaneThumbs()
{
	vector<string> planeThumbs;

	DIR *dir;
	struct dirent *ent;
	string skin = app->settings["skin"];
	string thumbs_path = "..\\Media\\CEGUI\\skins\\" + skin + "\\imagesets\\thumbs\\";
	if ((dir = opendir(thumbs_path.c_str())) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
		string filename = ent->d_name;
		if ( filename != "." && filename != "..")
			planeThumbs.push_back(ent->d_name);
	  }
	  closedir(dir);
	}
	return planeThumbs;
}