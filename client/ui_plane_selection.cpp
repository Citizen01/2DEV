#include "ui_windows.h"
#include "app.h"
#include "utils.h"
#include "GLOBALS.h"
#include <CEGUI.h>
#include <vector>

using namespace std;
using namespace CEGUI;
using namespace constants;

////////////////// CLICS HANDLERS //////////////////

//Bouton Play de la fenêtre de selection d'avion
bool handleBtnPlay (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	MultiColumnList* tabl = (MultiColumnList*)wmgr.getWindow("PS_SelectYurPlan/Plane_colum");
	ListboxItem* selectedItem = tabl->getFirstSelectedItem();

	if (selectedItem != NULL)
	{
		string planeName = selectedItem->getText().c_str();
		App::getSingleton()->getNetworkEngine()->askForLocalPlane(planeName);
	}
	return true;
}

//Croix de la fenêtre
bool handleClosePlaneSelection(const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	show_plane_selection(false);

	return true;
}

//Met à jour l'image de l'avion en fonction de l'avion selectionné
bool update_plane_preview (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();
	MultiColumnList* tabl = (MultiColumnList*) wmgr.getWindow("PS_SelectYurPlan/Plane_colum");
	ListboxItem* item = tabl->getFirstSelectedItem();
	string planeName = "none";
	if (item)
	{
		planeName = item->getText().c_str();
		DefaultWindow* planeImage = (DefaultWindow*)wmgr.getWindow("PS_SelectYurPlan/PlaneImg");
		planeImage->setProperty("Image", "set:plane_thumb_" + planeName + " image:full_image");
	}
	return true;
}

void create_plane_selection()
{
	//// Getting the WindowManager and the root Window ////
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* root = wmgr.getWindow("root");
	///////////////////////////////////////////////////////

	// Load Team Join
	Window* planeSelecWindow = wmgr.loadWindowLayout("PlaneSelection.layout", "PS_");
	root->addChildWindow( planeSelecWindow );
	planeSelecWindow->setVisible(false);
	planeSelecWindow->setProperty("AlwaysOnTop", "True");
	//Btn Play
	PushButton* playBtn = (PushButton*)wmgr.getWindow("PS_SelectYurPlan/Play");
	playBtn->subscribeEvent(PushButton::EventClicked, handleBtnPlay);

	//Add Column
	MultiColumnList* JtTbl = (MultiColumnList*)wmgr.getWindow("PS_SelectYurPlan/Plane_colum");
	JtTbl->addColumn("Name", 0, UDim(0.9f, 0));
	JtTbl->subscribeEvent(MultiColumnList::EventSelectionChanged, update_plane_preview);

	//Image:
	DefaultWindow* planeImage = (DefaultWindow*)wmgr.getWindow("PS_SelectYurPlan/PlaneImg");
	planeImage->setProperty( "FrameEnabled", "False" );
	planeImage->setProperty( "BackgroundEnabled", "False" );

	//Croix de la fenêtre
	PushButton* cross = (PushButton*)wmgr.getWindow("PS_SelectYurPlan__auto_closebutton__");
	cross->subscribeEvent(PushButton::EventClicked, handleClosePlaneSelection);
	
}

void show_plane_selection(bool visible)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.getWindow("PS_SelectYurPlan")->setVisible(visible);
	showCursor(visible);
}

////// MANIPULATION DU TABLEAU //////

//Met à jour la liste des avions disponibles
void update_plane_selection(vector<string> values)
{
	vector<vector<string>> val;
	for(unsigned int i = 0; i < values.size(); i++)
	{
		vector<string> tmp;
		tmp.push_back(values[i]);
		val.push_back(tmp);
	}
	WindowManager& wmgr = WindowManager::getSingleton();
	MultiColumnList* JtTbl = (MultiColumnList*)wmgr.getWindow("PS_SelectYurPlan/Plane_colum");

	updateTable(JtTbl, val);
}