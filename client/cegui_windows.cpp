#include "cegui_windows.h"
#include <CEGUI.h>

using namespace CEGUI;

void create_main_menu()
{
	//// Getting the WindowManager and the root Window ////
	WindowManager& wmgr = WindowManager::getSingleton();
	Window* root = wmgr.getWindow("root");
	///////////////////////////////////////////////////////

	FrameWindow* fWnd = static_cast<FrameWindow*>(
	wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

	root->addChildWindow( fWnd );

	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition( UVector2( UDim( 0.0f, 0 ), UDim( 0.0f, 0 ) ) );
	// set size to be half the size of the parent
	fWnd->setSize( UVector2( UDim( 0.2f, 0 ), UDim( 0.2f, 0 ) ) );

	fWnd->setText( "Hello World!" );
}