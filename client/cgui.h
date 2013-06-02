#pragma once

#include <irrlicht.h>
#include <CEGUI.h>
#include <RendererModules\Irrlicht\CEGUIIrrlichtRenderer.h>
#include <string>

class Cgui
{
private:
	std::string skin;
	irr::IrrlichtDevice* device;
	CEGUI::IrrlichtRenderer& irrRenderer;

public:
	Cgui(irr::IrrlichtDevice* device, std::string skin);
	~Cgui(void);

	/* Charge le skin, crée la root window */
	bool init();

	/* Crée toutes les fenêtres etc, il ne restera plus qu'à
	 * afficher la fenêtre au moment souhaité */
	bool precache();

	//// GETTERS AND SETTERS ////
	std::string getSkin();
	bool setSkin(std::string skin);

	irr::IrrlichtDevice* getDevice();

	CEGUI::IrrlichtRenderer& getRenderer();
};

