#include "cegui_windows.h"
#include <CEGUI.h>
#include "GLOBALS.h"

using namespace CEGUI;
using namespace constants;

void create_main_menu()
{
	//// Getting the WindowManager and the root Window ////
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* root = wmgr.getWindow("root");
	///////////////////////////////////////////////////////

	//FrameWindow* fWnd = static_cast<FrameWindow*>(
	//wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

	//root->addChildWindow( fWnd );

	//// position a quarter of the way in from the top-left of parent.
	//fWnd->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );
	//// set size to be half the size of the parent
	//fWnd->setSize( UVector2( UDim( 0.5f, 0 ), UDim( 0.5f, 0 ) ) );

	//fWnd->setText( "Hello World!" );

	// Menu Background
	ImagesetManager::getSingleton().createFromImageFile("plane", "plane.jpg");
	Window* MenuBackground = wmgr.createWindow("TaharezLook/StaticImage", "plane");
	root->addChildWindow( MenuBackground );
	MenuBackground->setPosition( UVector2( UDim( 0.0f, 0.0f ), UDim( 0.0f, 0.0f) ) );
	MenuBackground->setSize( UVector2( UDim( 1.0f, 0.0f ), UDim( 1.0f, 0.0f ) ) );  // full screen
	MenuBackground->setProperty( "Image", "set:plane image:full_image" );
	MenuBackground->setProperty( "FrameEnabled", "False" );




	
	// QuickConnect 
	PushButton* QuickConnect = (PushButton*)wmgr.createWindow("TaharezLook/Button", "Quick connect");
	MenuBackground->addChildWindow( QuickConnect );
	QuickConnect->setPosition( UVector2( UDim( 0.5f, 0.0f), UDim( 0.2f, 0.0f ) ) );
	QuickConnect->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
	QuickConnect->setText("Quick Conect");

	// ServerList 
	PushButton* ServerList = (PushButton*)wmgr.createWindow("TaharezLook/Button", "Server list");
	MenuBackground->addChildWindow( ServerList );
	ServerList->setPosition( UVector2( UDim( 0.5f, 0.0f), UDim( 0.4f, 0.0f ) ) );
	ServerList->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
	ServerList->setText("Server List");

	// About 
	PushButton* About = (PushButton*)wmgr.createWindow("TaharezLook/Button", "About");
	MenuBackground->addChildWindow( About );
	About->setPosition( UVector2( UDim( 0.5f, 0.0f), UDim( 0.6f, 0.0f ) ) );
	About->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
	About->setText("About");

	// Exit
	PushButton* Exit = (PushButton*)wmgr.createWindow("TaharezLook/Button", "Exit");
	MenuBackground->addChildWindow( Exit );
	Exit->setPosition( UVector2( UDim( 0.5f, 0.0f), UDim( 0.8f, 0.0f ) ) );
	Exit->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
	Exit->setText("Exit");

	//Fenetre Quick Connect
	FrameWindow* Wquick = static_cast<FrameWindow*>(
	wmgr.createWindow( "TaharezLook/FrameWindow", "QuickWin" ));

	root->addChildWindow( Wquick );


	//// position a quarter of the way in from the top-left of parent.
	Wquick->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );
	//// set size to be half the size of the parent
	Wquick->setSize( UVector2( UDim( 0.5f, 0 ), UDim( 0.2f, 0 ) ) );

	Wquick->setProperty("SizingEnabled", "False");

	Wquick->setText( "Quick Connect" );

	/* Editbox ip */
	Editbox* Ip = (Editbox*)wmgr.createWindow("TaharezLook/Editbox", "Editbox");
	Wquick->addChildWindow( Ip );
	//Editbox* editbox = static_cast<Editbox*>(wmgr.getWindow("Editbox"));
	Ip->setText("IP Address");
	//Ip->setMaxTextLength(13); // The trailing 's' will not be displayed
	Ip->setReadOnly(false);
	Ip->setPosition( UVector2( UDim( 0.1f, 0.0f), UDim( 0.2f, 0.0f ) ) );
	Ip->setSize( UVector2( UDim( 0.6f, 0.0f ), UDim( 0.25f, 0.0f ) ) );
	//Editbox->setTextMasked(false);
	//Editbox->setMaskCodePoint(0x002A); // *
	//String valueEditbox = Editbox->getText("Editbox"); // Retrieve the text

	/* Editbox port */
	Editbox* Port = (Editbox*)wmgr.createWindow("TaharezLook/Editbox", "Port");
	Wquick->addChildWindow( Port );
	Port->setText("Port");
	Port->setReadOnly(false);
	Port->setPosition( UVector2( UDim( 0.7f, 0.0f), UDim( 0.2f, 0.0f ) ) );
	Port->setSize( UVector2( UDim( 0.2f, 0.0f ), UDim( 0.25f, 0.0f ) ) );
	
	// Btn Connect 
	PushButton* BtnCon = (PushButton*)wmgr.createWindow("TaharezLook/Button", "BtnCon");
	Wquick->addChildWindow( BtnCon );
	BtnCon->setPosition( UVector2( UDim( 0.3f, 0.0f), UDim( 0.6f, 0.0f ) ) );
	BtnCon->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.25f, 0.0f ) ) );
	BtnCon->setText("Connect");

	// Load a layout
	//Window* guiLayout = wmgr.loadWindowLayout("Quicked.layout");
	//MenuBackground->addChildWindow(guiLayout);
 


}