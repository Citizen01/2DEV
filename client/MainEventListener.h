#pragma once
#include "Cgui.h"
#include <irrlicht.h>
#include <RendererModules\Irrlicht\CEGUIIrrlichtRenderer.h>
#include "GameEventListener.h"
#include "SoundEventListener.h"

class MainEventListener : public irr::IEventReceiver
{
private:
	CEGUI::IrrlichtRenderer* renderer;	//graphics
	GameEventListener* gListener;		//game
	SoundEventListener* sListener;		//sound
	//network ??

public:
	MainEventListener();
	~MainEventListener(void);

	/* Méthode qui réceptionne tous les events (clavier/souris)
	   et les propage aux event receivers interessés */
	virtual bool OnEvent(const irr::SEvent& event);

	bool subscribeCEGUI(CEGUI::IrrlichtRenderer* renderer);

	bool subscribeGameEngine(GameEventListener* gListener);

	bool subscribeSoundEngine(SoundEventListener* sListener);
	
};

