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

	/* Charge le skin, cr�e la root window */
	bool init();

	/* Cr�e toutes les fen�tres etc, il ne restera plus qu'�
	 * afficher la fen�tre au moment souhait� */
	bool precache();

	//// GETTERS AND SETTERS ////
	std::string getSkin();
	bool setSkin(std::string skin);

	irr::IrrlichtDevice* getDevice();

	CEGUI::IrrlichtRenderer& getRenderer();
};

