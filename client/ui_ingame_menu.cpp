#include "ui_windows.h"
#include "app.h"
#include "utils.h"
#include <CEGUI.h>

using namespace std;
using namespace CEGUI;


////////////////// CLICS HANDLERS //////////////////

//Bouton Back to game et la croix de la fenêtre
bool handleCloseIGMenu(const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	show_ingame_menu(false);

	return true;
}

//Bouton Change faction
bool handleChangeFaction(const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();
	
	show_ingame_menu(false);
	show_team_selection(true);

	return true;
}

//Bouton Change plane
bool handleChangePlane(const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	show_ingame_menu(false);
	show_plane_selection(true);

	return true;
}

//Bouton Leave game
bool handleLeaveGame(const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	show_ingame_menu(false);
	/* TODO: 
	App::getSingleton()->disconnect();
		ou
	App::getSingleton()->getGameEngine()->getGame()->leave();
	*/

	return true;
}
////////////////// FIN CLICS HANDLERS //////////////////


void create_ingame_menu()
{
	//// Getting the WindowManager and the root Window ////
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* root = wmgr.getWindow("root");
	///////////////////////////////////////////////////////

	// Load ingame menu
	Window* ingameMenu = wmgr.loadWindowLayout("IngameMenu.layout", "IGM_");
	root->addChildWindow( ingameMenu );
	ingameMenu->setVisible (false);
	ingameMenu->setProperty("AlwaysOnTop", "True");

	//Btn Back to Game
	PushButton* backToGameBtn = (PushButton*)wmgr.getWindow("IGM_IngameMenu/Back_Game");
	backToGameBtn->subscribeEvent(PushButton::EventClicked, handleCloseIGMenu);

	//Croix de la fenêtre
	PushButton* cross = (PushButton*)wmgr.getWindow("IGM_IngameMenu__auto_closebutton__");
	cross->subscribeEvent(PushButton::EventClicked, handleCloseIGMenu);

	//Btn change plane
	PushButton* changePlaneBtn = (PushButton*)wmgr.getWindow("IGM_IngameMenu/Change_Plane");
	changePlaneBtn->subscribeEvent(PushButton::EventClicked, handleChangePlane);
	
	//Btn change Faction
	PushButton* changeFactionBtn = (PushButton*)wmgr.getWindow("IGM_IngameMenu/Change_Faction");
	changeFactionBtn->subscribeEvent(PushButton::EventClicked, handleChangeFaction);

	//Btn leave game
	PushButton* leaveGameBtn = (PushButton*)wmgr.getWindow("IGM_IngameMenu/Leave_Game");
	leaveGameBtn->subscribeEvent(PushButton::EventClicked, handleLeaveGame);
	
}

void show_ingame_menu(bool visible)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.getWindow("IGM_IngameMenu")->setVisible(visible);
	showCursor(visible);
}

void toggle_ingame_menu()
{
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* ig_menu = (Window*)wmgr.getWindow("IGM_IngameMenu");
	bool visible = ig_menu->isVisible();
	ig_menu->setVisible(!visible);
	showCursor(visible);
}