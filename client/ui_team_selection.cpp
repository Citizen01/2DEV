#include "ui_windows.h"
#include "app.h"
#include "utils.h"
#include <CEGUI.h>
#include <vector>

using namespace std;
using namespace CEGUI;
using namespace constants;

////////////////// CLICS HANDLERS //////////////////
//Bouton Join de la fenêtre de selection de team
bool handleTeamJoinBtnJoin (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	MultiColumnList* tabl = (MultiColumnList*)wmgr.getWindow("TS_JoinTeam/TeamChoise");
	ListboxItem* selectedItem = tabl->getFirstSelectedItem();

	if (selectedItem != NULL)
	{
		string factionName = selectedItem->getText().c_str();
		//TODO: Ask for changing team

	}
	return true;
}

//Croix de la fenêtre join
bool handleCloseTeamSelection(const EventArgs&e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.getWindow("TS_JoinTeam")->setVisible(false);
	return true;
}

void create_team_selection()
{
	//// Getting the WindowManager and the root Window ////
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* root = wmgr.getWindow("root");
	///////////////////////////////////////////////////////

	// Load Team Join
	Window* TeamJoin = wmgr.loadWindowLayout("TeamSelection.layout", "TS_");
	root->addChildWindow( TeamJoin );
	TeamJoin->setVisible(false);
	TeamJoin->setProperty("AlwaysOnTop", "True");
	//Btn Join
	PushButton* JoinBtn = (PushButton*)wmgr.getWindow("TS_JoinTeam/Join");
	JoinBtn->subscribeEvent(PushButton::EventClicked, handleTeamJoinBtnJoin);
	//Croix close TeamJoin
	PushButton* QuickClose = (PushButton*)wmgr.getWindow("TS_JoinTeam__auto_closebutton__");
	QuickClose->subscribeEvent(PushButton::EventClicked,Event::Subscriber(handleCloseTeamSelection));

	//Add Columns
	MultiColumnList* JtTbl = (MultiColumnList*)wmgr.getWindow("TS_JoinTeam/TeamChoise");
	JtTbl->addColumn("Name", 0, UDim(0.5f, 0));
	JtTbl->addColumn("Players", 1, UDim(0.4f, 0));
	
}

void show_team_selection(bool visible)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.getWindow("TS_JoinTeam")->setVisible(visible);
}


////// MANIPULATION DU TABLEAU //////

void update_team_selection(vector<vector<string>> values)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	MultiColumnList* JtTbl = (MultiColumnList*)wmgr.getWindow("TS_JoinTeam/TeamChoise");

	updateTable(JtTbl, values);
}