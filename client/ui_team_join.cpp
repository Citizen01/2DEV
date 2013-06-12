#include "ui_windows.h"
#include "app.h"
#include <CEGUI.h>

using namespace std;
using namespace CEGUI;
using namespace constants;


//TODO: faire les fonctions d'handle des events


void create_team_join()
{
	//// Getting the WindowManager and the root Window ////
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* root = wmgr.getWindow("root");
	///////////////////////////////////////////////////////

	//TODO: Charger le .layout, le setVisible(false) et lui faire un subscribeEvent(...)

}

void show_team_join(bool visible)
{
	//TODO: getWindow pour recup la fenêtre team join puis un ->setVisible(visible) (voir exemple dans ui_main_menu.cpp)

}