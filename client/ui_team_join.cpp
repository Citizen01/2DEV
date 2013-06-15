#include "ui_windows.h"
#include "app.h"
#include "utils.h"
#include <CEGUI.h>
#include <vector>

using namespace std;
using namespace CEGUI;
using namespace constants;

////////////////// CLICS HANDLERS //////////////////
//Bouton Add de la fenêtre Server List
bool handleTeamJoinBtnJoin (const CEGUI::EventArgs &e)
{
	WindowManager& wmgr = WindowManager::getSingleton();

	MultiColumnList* tabl = (MultiColumnList*)wmgr.getWindow("Tj_JoinTeam");
	ListboxItem* selectedItem = tabl->getFirstSelectedItem();

	if (selectedItem != NULL)
	{
		string factionName = selectedItem->getText().c_str();
		//TODO: 

	}

	return true;
}

//Croix de la fenêtre join
bool handleTeamJoinClose (const EventArgs&e)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.getWindow("Tj_JoinTeam")->setVisible(false);
	return true;
}

void create_team_join()
{
	//// Getting the WindowManager and the root Window ////
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* root = wmgr.getWindow("root");
	///////////////////////////////////////////////////////

	// Load Team Join
	Window* TeamJoin = wmgr.loadWindowLayout("TeamJoin.layout", "Tj_");
	root->addChildWindow( TeamJoin );
	//TeamJoin->setVisible (false);
	TeamJoin->setProperty("AlwaysOnTop", "True");
	//Btn Join
	PushButton* JoinBtn = (PushButton*)wmgr.getWindow("Tj_JoinTeam/Join");
	JoinBtn->subscribeEvent(PushButton::EventClicked, handleTeamJoinBtnJoin);
	//Croix close TeamJoin
	PushButton* QuickClose = (PushButton*)wmgr.getWindow("Tj_JoinTeam__auto_closebutton__");
	QuickClose->subscribeEvent(PushButton::EventClicked,Event::Subscriber(handleTeamJoinClose));

	//Add Columns
	MultiColumnList* JtTbl = (MultiColumnList*)wmgr.getWindow("Tj_JoinTeam/TeamChoise");
	JtTbl->addColumn("Name", 0, UDim(0.5f, 0));
	JtTbl->addColumn("Players", 1, UDim(0.4f, 0));
	
}

void show_team_join(bool visible)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.getWindow("Tj_JoinTeam")->setVisible(visible);
}


////// MANIPULATION DU TABLEAU //////

void team_join_updateTeams(vector<vector<string>> values)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	MultiColumnList* JtTbl = (MultiColumnList*)wmgr.getWindow("Tj_JoinTeam/TeamChoise");

	updateTable(JtTbl, values);
}