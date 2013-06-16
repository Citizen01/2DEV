#include "ui_windows.h"
#include "GLOBALS.h"
#include "server_manager.h"
#include "app.h"
#include <CEGUI.h>
#include <iostream>
#include <sstream>
#include "utils.h"

using namespace CEGUI;
using namespace constants;
using namespace std;

//Bouton Quick Connect du menu principal
bool handleQuickConnectBtnWin (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	Window* QuickCoWin = wmgr.getWindow("QuickCo_Quick_connect");
	QuickCoWin->setVisible (true);

	return true;
}

//Bouton Server list du menu principal
bool handleSrvlBtnWin (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	Window* SrvlWin = wmgr.getWindow("Srvl_ServerList");
	update_server_list();
	SrvlWin->setVisible (true);

	return true;
}

//Bouton About du menu principal
bool handleAboutBtnWin (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	Window* AboutWin = wmgr.getWindow("Ab_AboutWin");
	AboutWin->setVisible (true);

	return true;
}

//Bouton Exit du menu principal
bool handleExitBtn (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	App::getSingleton()->stop();
	return true;
}

//Bouton Back et la croix de la fenêtre About
bool handleAboutBtnWinClose (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	Window* AboutWin = wmgr.getWindow("Ab_AboutWin");
	AboutWin->setVisible (false);

	return true;
}

//Bouton Connect de la fenêtre Quick Connect
bool handleQuickConnectBtnCo (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();
	
	WindowManager& wmgr = WindowManager::getSingleton();
	
	Editbox* champIp = (Editbox*) wmgr.getWindow("QuickCo_Quick_connect/IpAdress");
	string ip = champIp->getText().c_str();

	Editbox* portCase = (Editbox*) wmgr.getWindow("QuickCo_Quick_connect/PortCase");
	string portStr = portCase->getText().c_str();
	
	int port;
	std::istringstream ss(portStr);
	ss >> port;
	
	char *cstr = new char[ip.length() + 1];
	strcpy(cstr, ip.c_str());
	cout << cstr << endl;

	App::getSingleton()->getNetworkEngine()->connect(cstr, port);
	delete [] cstr;
	return true;
}

//Bouton Add de la fenêtre Server List
bool handleSrvlBtnAdd (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	Editbox* serverChamp = (Editbox*) wmgr.getWindow("Srvl_ServerList/Server_Name");
	string serverName = serverChamp->getText().c_str();
	
	
	Editbox* ipBare = (Editbox*) wmgr.getWindow("Srvl_ServerList/Ip_bare");
	string ipAdress = ipBare->getText().c_str();	

	size_t pos = 0;
	string token;
	vector<std::string> resultat;
	string delimiter = ":";
	string ip;
	string port;

	while((pos = ipAdress.find(delimiter)) != string::npos)
	{
		token = ipAdress.substr(0, pos);
		resultat.push_back(token);
		ipAdress.erase(0,pos + delimiter.length());
	}
	resultat.push_back(ipAdress);

	if (resultat.size() == 1)
	{
		ip = ipAdress;
		port = intToString(DEFAULT_SERVER_PORT);
	}
	else
	{
		ip = resultat[0];
		port = resultat[1];
	}
	
	string fullAddr = ip +":"+ port;
	
	bool success = server_manager::getSingleton()->addServer(serverName, ip, port);
	if(success) 
	{
		MultiColumnList* serverList = (MultiColumnList*) wmgr.getWindow("Srvl_ServerList/Server_list");
		vector<string> row;
		row.push_back(serverName);
		row.push_back(fullAddr);
		addTableRow(serverList, row);
	}
	
	return true;
}

//Bouton Delete de la fenêtre Server List
bool handleSrvlBtnDelete (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	MultiColumnList* serverList = (MultiColumnList*) wmgr.getWindow("Srvl_ServerList/Server_list");
	ListboxItem* item = serverList->getFirstSelectedItem();
	if (item)
	{
		string serverName = item->getText().c_str();
		
		cout << serverName << endl;
		bool success = server_manager::getSingleton()->removeServer(serverName);
		if (success)
		{
			MultiColumnList* deleteServerList = (MultiColumnList*) wmgr.getWindow("Srvl_ServerList/Delete");
			int line = findIndexOfItem(serverList, item);
			removeRow(serverList, line);
		}
	}
	return true;
}

//Bouton Connect de la fenêtre Quick Connect
bool handleSrvlBtnCo (const CEGUI::EventArgs &e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();

	MultiColumnList* serverList = (MultiColumnList*) wmgr.getWindow("Srvl_ServerList/Server_list");
	
	ListboxItem* serverNameItem = serverList->getFirstSelectedItem();
	string serverNameItemText = serverNameItem->getText().c_str();

	ListboxItem* adressItem = serverList->getNextSelected(serverNameItem);
	string adressItemText = adressItem->getText().c_str();

	size_t pos = 0;
	string token;
	vector<std::string> resultat;
	string delimiter = ":";
	string ip;
	string port;

	while((pos = adressItemText.find(delimiter)) != string::npos)
	{
		token = adressItemText.substr(0, pos);
		resultat.push_back(token);
		adressItemText.erase(0,pos + delimiter.length());
	}
	resultat.push_back(adressItemText);

	if (resultat.size() == 1)
	{
		ip = adressItemText;
		port = intToString(DEFAULT_SERVER_PORT);
	}
	else
	{
		ip = resultat[0];
		port = resultat[1];
	}
	
	int p;
	std::istringstream ss(port);
	ss >> p;
	
	char *ipChar = new char[ip.length() + 1];
	strcpy(ipChar, ip.c_str());

	server_manager::getSingleton()->loadServers();
	App::getSingleton()->getNetworkEngine()->connect(ipChar, p);
	return true;
}

//Croix de la fenêtre Quick Connect
bool handleQuickConnectClose (const EventArgs&e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.getWindow("QuickCo_Quick_connect")->setVisible(false);
	return true;
}

//Croix de la fenêtre Server List
bool handleSrvlBtnClose (const EventArgs&e)
{
	App::getSingleton()->getSoundEngine()->playClick();

	WindowManager& wmgr = WindowManager::getSingleton();
	wmgr.getWindow("Srvl_ServerList")->setVisible(false);
	return true;
}

void create_main_menu()
{
	//// Getting the WindowManager and the root Window ////
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* root = wmgr.getWindow("root");
	///////////////////////////////////////////////////////

	// Menu Background
	ImagesetManager::getSingleton().createFromImageFile("main_menu_bg", "main_menu_bg.jpg");
	Window* MenuBackground = wmgr.createWindow("TaharezLook/StaticImage", "main_menu");
	root->addChildWindow( MenuBackground );
	MenuBackground->setPosition( UVector2( UDim( 0.0f, 0.0f ), UDim( 0.0f, 0.0f) ) );
	MenuBackground->setSize( UVector2( UDim( 1.0f, 0.0f ), UDim( 1.0f, 0.0f ) ) );  // full screen
	MenuBackground->setProperty( "Image", "set:main_menu_bg image:full_image" );
	MenuBackground->setProperty( "FrameEnabled", "False" );

	MenuBackground->setVisible(false);
		
	// QuickConnect 
	PushButton* QuickConnect = (PushButton*)wmgr.createWindow("TaharezLook/Button", "Quick connect");
	MenuBackground->addChildWindow( QuickConnect );
	QuickConnect->setPosition( UVector2( UDim( 0.5f, 0.0f), UDim( 0.2f, 0.0f ) ) );
	QuickConnect->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
	QuickConnect->setText("Quick Connect");
	//Pop Quick Connect
	QuickConnect->subscribeEvent(PushButton::EventClicked, handleQuickConnectBtnWin);

	// ServerList 
	PushButton* ServerList = (PushButton*)wmgr.createWindow("TaharezLook/Button", "Server list");
	MenuBackground->addChildWindow( ServerList );
	ServerList->setPosition( UVector2( UDim( 0.5f, 0.0f), UDim( 0.4f, 0.0f ) ) );
	ServerList->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
	ServerList->setText("Server List");
	//Pop Server list
	ServerList->subscribeEvent(PushButton::EventClicked, handleSrvlBtnWin);

	// About 
	PushButton* About = (PushButton*)wmgr.createWindow("TaharezLook/Button", "About");
	MenuBackground->addChildWindow( About );
	About->setPosition( UVector2( UDim( 0.5f, 0.0f), UDim( 0.6f, 0.0f ) ) );
	About->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
	About->setText("About");
	//Pop About
	About->subscribeEvent(PushButton::EventClicked, handleAboutBtnWin);
	
	// Exit
	PushButton* Exit = (PushButton*)wmgr.createWindow("TaharezLook/Button", "Exit");
	MenuBackground->addChildWindow( Exit );
	Exit->setPosition( UVector2( UDim( 0.5f, 0.0f), UDim( 0.8f, 0.0f ) ) );
	Exit->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
	Exit->setText("Exit");
	Exit->subscribeEvent(PushButton::EventClicked, handleExitBtn);

	// Load a Quick Connect
	Window* QuickWin = wmgr.loadWindowLayout("QuickConnect.layout", "QuickCo_");
	MenuBackground->addChildWindow(QuickWin);
	QuickWin->setVisible (false);
	QuickWin->setProperty("AlwaysOnTop", "True");
	//Action Boutton Connect
	PushButton* ConnectBtn = (PushButton*)wmgr.getWindow("QuickCo_Quick_connect/ConnectBtn");
	ConnectBtn->subscribeEvent(PushButton::EventClicked, handleQuickConnectBtnCo);
	//Close
	PushButton* QuickClose = (PushButton*)wmgr.getWindow("QuickCo_Quick_connect__auto_closebutton__");
	QuickClose->subscribeEvent(PushButton::EventClicked,Event::Subscriber(handleQuickConnectClose));
	
	
	// Load a Server_list
	Window* Srvl = wmgr.loadWindowLayout("ServerList.layout", "Srvl_");
	MenuBackground->addChildWindow( Srvl );
	Srvl->setVisible (false);
	Srvl->setProperty("AlwaysOnTop", "True");
	//Action Boutton Add
	PushButton* AddBtnSrvl = (PushButton*)wmgr.getWindow("Srvl_ServerList/Add");
	AddBtnSrvl->subscribeEvent(PushButton::EventClicked, handleSrvlBtnAdd);
	//Action Boutton Delete
	PushButton* DeleteBtnSrvl = (PushButton*)wmgr.getWindow("Srvl_ServerList/Delete");
	DeleteBtnSrvl->subscribeEvent(PushButton::EventClicked, handleSrvlBtnDelete);
	//Action boutton Connect
	PushButton* ConnectBtnSrvl = (PushButton*)wmgr.getWindow("Srvl_ServerList/ConnectBtn");
	ConnectBtnSrvl->subscribeEvent(PushButton::EventClicked, handleSrvlBtnCo);
	//Close
	PushButton* SrvlClose = (PushButton*)wmgr.getWindow("Srvl_ServerList__auto_closebutton__");
	SrvlClose->subscribeEvent(PushButton::EventClicked,Event::Subscriber(handleSrvlBtnClose));
	

	//Add Colone
	MultiColumnList* SrvlTableau = (MultiColumnList*)wmgr.getWindow("Srvl_ServerList/Server_list");
	SrvlTableau->addColumn("Server name", 0, UDim(0.60f, 0));
	SrvlTableau->addColumn("Address", 1, UDim(0.38f, 0));
	SrvlTableau->setSelectionMode(MultiColumnList::SelectionMode::RowSingle);
	SrvlTableau->setProperty("SelectionMode", "0");

	// Load About
	Window* AboutWidget = wmgr.loadWindowLayout("About.layout", "Ab_");
	MenuBackground->addChildWindow( AboutWidget );
	MultiLineEditbox* AboutText = (MultiLineEditbox*)wmgr.getWindow("Ab_AboutWin/TextArea");
	AboutText->setProperty("Disabled", "True");
	AboutWidget->setVisible (false);

	AboutWidget->setProperty("AlwaysOnTop", "True");

	//Close About + btn Back
	PushButton* AboutBack = (PushButton*)wmgr.getWindow("Ab_AboutWin/Button");
	PushButton* AboutClose = (PushButton*)wmgr.getWindow("Ab_AboutWin__auto_closebutton__");
	AboutBack->subscribeEvent(PushButton::EventClicked, handleAboutBtnWinClose);
	AboutClose->subscribeEvent(PushButton::EventClicked,Event::Subscriber(handleAboutBtnWinClose));
}

void show_main_menu(bool visible)
{
	WindowManager& wmgr = WindowManager::getSingleton();
	if(visible) {
		App::getSingleton()->getSoundEngine()->playBackgroundMusic("menu.mp3");
	} else {
		App::getSingleton()->getSoundEngine()->stopBackgroundMusic();
	}
	wmgr.getWindow("main_menu")->setVisible(visible);
}

void update_server_list()
{
	WindowManager& wmgr = WindowManager::getSingleton();
	MultiColumnList* serverList = (MultiColumnList*) wmgr.getWindow("Srvl_ServerList/Server_list");
	server_manager* srvmgr = server_manager::getSingleton();
	vector<server> servers = srvmgr->getServerList();
	for (unsigned int i=0; i < servers.size(); i++)
	{
		server srv = servers[i];
		vector<string> row;
		row.push_back(srv.name);
		row.push_back(srv.ip+":"+srv.port);
		addTableRow(serverList, row);
	}
}