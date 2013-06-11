#include "Cgui.h"
#include "cegui_windows.h"
#include <iostream>
#include <windows.h>

using namespace CEGUI;
using namespace irr;
using namespace std;

Cgui::Cgui(IrrlichtDevice* device, string skin) : irrRenderer(IrrlichtRenderer::bootstrapSystem( *device ))
{
	this->device = device;
	setSkin(skin);

	init();
	//precache();
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

		string skins_path = "../Media/cegui/skins/";
		
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
	/* créer vos fonctions qui permettent de
	 * créer une fenêtre ou un ensemble de fenêtre
	 * dans cegui_windows.cpp, puis appellez les
	 * ci-dessous: */
	cout << "[CEGUI] Precaching all windows for the game ..." << endl;

	create_main_menu(); //Menu principal du jeu

	cout << "[CEGUI] Successfully precached all windows for the game !" << endl;
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