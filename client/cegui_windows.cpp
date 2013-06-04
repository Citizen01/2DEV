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
	QuickConnect->setPosition( UVector2( UDim( 0.2f, 0.0f), UDim( 0.2f, 0.0f ) ) );
	QuickConnect->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );

	// ServerList 
	PushButton* ServerList = (PushButton*)wmgr.createWindow("TaharezLook/Button", "Server list");
	MenuBackground->addChildWindow( ServerList );
	ServerList->setPosition( UVector2( UDim( 0.2f, 0.0f), UDim( 0.4f, 0.0f ) ) );
	ServerList->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );

	// About 
	PushButton* About = (PushButton*)wmgr.createWindow("TaharezLook/Button", "About");
	MenuBackground->addChildWindow( About );
	About->setPosition( UVector2( UDim( 0.2f, 0.0f), UDim( 0.6f, 0.0f ) ) );
	About->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );

	// Exit
	PushButton* Exit = (PushButton*)wmgr.createWindow("TaharezLook/Button", "Exit");
	MenuBackground->addChildWindow( Exit );
	Exit->setPosition( UVector2( UDim( 0.2f, 0.0f), UDim( 0.8f, 0.0f ) ) );
	Exit->setSize( UVector2( UDim( 0.4f, 0.0f ), UDim( 0.08f, 0.0f ) ) );
}