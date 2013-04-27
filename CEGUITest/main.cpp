#include <CEGUI.h>
#include <irrlicht.h>
#include <RendererModules\Irrlicht\CEGUIIrrlichtRenderer.h>
#include <string>
#include <iostream>

using namespace irr;
using namespace CEGUI;
using namespace std;

//Nom du skin à utiliser (correspond au nom du dossier dans Media\cegui\skins)
#define SKIN_NAME "default"

class MyEventReceiver : public IEventReceiver
{
private:
	IrrlichtRenderer* rend;
public:
	MyEventReceiver(IrrlichtRenderer *renderer)
	{
		rend = renderer;
	}

    virtual bool OnEvent(const SEvent& event)
	{
		rend->injectEvent(event);

        return false;
    }
};

int main(int argc, char *argv[])
{
	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;
    if (driverType==video::EDT_COUNT)
        return 0;

    // crée un device avec des paramètres spécifiques
    // on pourra rajouter des paramètres comme la v-sync, l'anti-aliasing etc
    SIrrlichtCreationParameters params; //Liste des paramètres à passé lors de la création du device
	/////////////////// CONFIG ///////////////////
	//Paramètres indispensables:
    params.DriverType = driverType; //Doit être récup depuis le fichier de config
    params.WindowSize = core::dimension2d<u32>(1024, 768);//Doit être récup depuis le fichier de config
	//Paramètres supplémentaires ici:

	//////////////////////////////////////////////

	//Création de l'objet device (Base d'Irrlicht)
    IrrlichtDevice *device = createDeviceEx(params);

    if (device == 0)
        return 0 ; // could not create selected driver.

	//Shortcut pour les 2 objets les + utilisés
	video::IVideoDriver *driver = device->getVideoDriver();
	scene::ISceneManager *smgr = device->getSceneManager();

	// Bootstrap System with an IrrlichtRenderer object, an Irrlicht based
	// ResourceProvider, and an Irrlicht based ImageCodec.
	IrrlichtRenderer& myRenderer =
		IrrlichtRenderer::bootstrapSystem( *device );

	MyEventReceiver receiver(&myRenderer);
    device->setEventReceiver(&receiver);

	//Set the skin to use
	String skin = SKIN_NAME; 

	cout << endl << "Utilisation du skin: " << skin << endl;

	// initialise the required dirs for the DefaultResourceProvider
	DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>
		(System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("schemes", "../Media/cegui/skins/"+skin+"/schemes/");
	rp->setResourceGroupDirectory("imagesets", "../Media/cegui/skins/"+skin+"/imagesets/");
	rp->setResourceGroupDirectory("fonts", "../Media/cegui/skins/"+skin+"/fonts/");
	rp->setResourceGroupDirectory("layouts", "../Media/cegui/skins/"+skin+"/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "../Media/cegui/skins/"+skin+"/looknfeel/");
	rp->setResourceGroupDirectory("schemas", "../Media/cegui/xml_schemas/");

	// set the default resource groups to be used
	Imageset::setDefaultResourceGroup("imagesets");
	Font::setDefaultResourceGroup("fonts");
	Scheme::setDefaultResourceGroup("schemes");
	WidgetLookManager::setDefaultResourceGroup("looknfeels");
	WindowManager::setDefaultResourceGroup("layouts");
	// setup default group for validation schemas
	XMLParser* parser = System::getSingleton().getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");

	SchemeManager::getSingleton().create( "cegui.scheme" );

	FontManager::getSingleton().create("Commonwealth-10.font");

	System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );
	device->getCursorControl()->setVisible(false); //Permet de cacher la souris de l'os

	WindowManager& winMgr = WindowManager::getSingleton();

	Window* sheet = winMgr.createWindow( "DefaultWindow", "root" );
	System::getSingleton().setGUISheet( sheet );


	// Load a layout
	Window* guiLayout = winMgr.loadWindowLayout("AllWidgets.layout");
	sheet->addChildWindow(guiLayout);
 
 
 
	/* Tooltip */
	System::getSingleton().setDefaultTooltip("TaharezLook/Tooltip"); // Set the name of the default tooltip
	Tooltip* tooltip = System::getSingleton().getDefaultTooltip();
	tooltip->setHoverTime(0.5f); // Display the tooltip after the mouse has been hovering over the widget for half a second
	tooltip->setDisplayTime(10.0f); // Display for 15 seconds then disappear
	tooltip->setFadeTime(1.0f); // Duration of the transition between fully visible and fully invisible
	// To set the tooltip text for a window simply call setTooltipText()   see staticText for an example
 
	/* StaticText */
	DefaultWindow* staticText = static_cast<DefaultWindow*>(winMgr.getWindow("StaticText"));
	staticText->setText("Red Static Text");
	// Colours are specified as aarrggbb in Hexadecimal
	// Where aa is alpha, rr is red, gg is green, and bb is blue 
	// tl: top left,  tr: top right,  bl: bottom left,  br: bottom right
	staticText->setProperty("TextColours", "tl:FFFF0000 tr:FFFF0000 bl:FFFF0000 br:FFFF0000");
	staticText->setProperty("VertFormatting", "VertCentred"); // TopAligned, BottomAligned, VertCentred
	staticText->setProperty("HorzFormatting", "HorzCentred"); // LeftAligned, RightAligned, HorzCentred
		// HorzJustified, WordWrapLeftAligned, WordWrapRightAligned, WordWrapCentred, WordWrapJustified
	staticText->setTooltipText("This is a StaticText widget");
 
	/* StaticImage */
	ImagesetManager::getSingleton().createFromImageFile("ImageForStaticImage", "GPN-2000-001437.tga");
	DefaultWindow* staticImage = static_cast<DefaultWindow*>(winMgr.getWindow("StaticImage"));
	staticImage->setProperty("Image", "set:ImageForStaticImage image:full_image"); // "full_image" is a default name from CEGUIImageset::Imageset()
 
	/* ProgressBar */
	ProgressBar* progressBar = static_cast<ProgressBar*>(winMgr.getWindow("ProgressBar"));
	progressBar->setProgress(0.25f); // Initial progress of 25%
	progressBar->setStepSize(0.10f); // Calling step() will increase the progress by 10%
	progressBar->step(); // Advance the progress by the size specified in setStepSize()
	progressBar->adjustProgress(-0.05f); // Adjust the progress by a delta value rather than setting a new value through setProgress
	float valueProgressBar = progressBar->getProgress(); // initial 0.25f + step 0.10f - adjustment 0.05f = 0.30f
 
	/* Button */
	PushButton* btnClose = static_cast<PushButton*>(winMgr.getWindow("btnClose"));
	btnClose->setText("Exit");
 
	/* ScrollablePane */
	ScrollablePane* scrollablePane = static_cast<ScrollablePane*>(winMgr.getWindow("ScrollablePane"));
	ImagesetManager::getSingleton().createFromImageFile("ImageForScrollablePane", "GPN-2000-001437.tga");
	DefaultWindow* staticImageInScrollablePane = static_cast<DefaultWindow*>(winMgr.createWindow("TaharezLook/StaticImage", "StaticImageInScrollablePane"));
		staticImageInScrollablePane->setProperty("Image", "set:ImageForScrollablePane image:full_image"); // "full_image" is a default name from CEGUIImageset::Imageset()
		staticImageInScrollablePane->setPosition(UVector2(UDim(0.0f, 0.0f), UDim(0.0f, 0.0f))); // Start in the upper left corner
		staticImageInScrollablePane->setWidth(UDim(2.0f, 0.0f)); // Twice the width of the parent, the ScrollablePane
		staticImageInScrollablePane->setHeight(UDim(2.0f, 0.0f)); // Twice the height of the parent, the ScrollablePane
		scrollablePane->addChildWindow(staticImageInScrollablePane); // Add the image to the // Twice the width of the parent, the ScrollablePane
	Editbox* editboxInScrollablePane = static_cast<Editbox*>(winMgr.createWindow("TaharezLook/Editbox", "EditboxInScrollablePane"));
		editboxInScrollablePane->setPosition(UVector2(UDim(0.0f, 0.0f), UDim(2.1f, 0.0f))); // Start below the image
		editboxInScrollablePane->setWidth(UDim(2.0f, 0.0f)); 
		editboxInScrollablePane->setHeight(UDim(0.3f, 0.0f));
		scrollablePane->addChildWindow(editboxInScrollablePane);
 
	/* Check box */
	Checkbox* checkbox = static_cast<Checkbox*>(winMgr.getWindow("Checkbox"));
	checkbox->setSelected( true );
	bool valueCheckbox = checkbox->isSelected(); // Retrieve whether it is checked
 
	/* Spinner */
	Spinner* spinner = static_cast<Spinner*>(winMgr.getWindow("Spinner"));
	spinner->setTextInputMode(Spinner::FloatingPoint); // FloatingPoint, Integer, Hexadecimal, Octal
	spinner->setMinimumValue(-10.0f);
	spinner->setMaximumValue(10.0f);
	spinner->setStepSize(0.2f);
	spinner->setCurrentValue(5.2f);
	float valueSpinner = spinner->getCurrentValue(); // Retrieve the value
 
	/* Editbox */
	Editbox* editbox = static_cast<Editbox*>(winMgr.getWindow("Editbox"));
	editbox->setText("Editbox values");
	editbox->setMaxTextLength(13); // The trailing 's' will not be displayed
	editbox->setReadOnly(false);
	editbox->setTextMasked(false);
	editbox->setMaskCodePoint(0x002A); // *
	String valueEditbox = editbox->getText(); // Retrieve the text
 
	/* Slider */
	Slider* slider = static_cast<Slider*>(winMgr.getWindow("Slider"));
	slider->setMaxValue(100.0f);
	slider->setClickStep(10.0f);
	slider->setCurrentValue(20.0f);
	float valueSlider = slider->getCurrentValue(); // Retrieve the value
 
	/* Scrollbar (Horizontal) */
	Scrollbar* scrollbarHorizontal = static_cast<Scrollbar*>(winMgr.getWindow("HorizontalScrollbar"));
	scrollbarHorizontal->setDocumentSize(100.0f);
	scrollbarHorizontal->setPageSize(10.0f);
	scrollbarHorizontal->setStepSize(1.0f);
	scrollbarHorizontal->setScrollPosition(75.0f);
	float valueScrollbarHorizontal = scrollbarHorizontal->getScrollPosition(); // Retrieve the scroll position
 
	/* Scrollbar (Vertical) */
	Scrollbar* scrollbarVertical = static_cast<Scrollbar*>(winMgr.getWindow("VerticalScrollbar"));
	scrollbarVertical->setDocumentSize(100.0f);
	scrollbarVertical->setPageSize(10.0f);
	scrollbarVertical->setStepSize(1.0f);
	scrollbarVertical->setScrollPosition(25.0f);
	float valueScrollbarVertical = scrollbarVertical->getScrollPosition(); // Retrieve the scroll position
 
	/* MultiLineEditbox */
	MultiLineEditbox* multiLineEditbox = static_cast<MultiLineEditbox*>(winMgr.getWindow("MultiLineEditbox"));
	multiLineEditbox->setText("MultiLineEditbox value");
	multiLineEditbox->setReadOnly(false);
	multiLineEditbox->setWordWrapping(true);
	String valueMultiLineEditbox = multiLineEditbox->getText(); // Retrieve the text
 
	/* RadioButton */
	RadioButton* radioButton = static_cast<RadioButton*>(winMgr.getWindow("RadioButton_A"));
		radioButton->setGroupID(1);
		radioButton->setID(101);
		radioButton->setSelected(true);
	radioButton = static_cast<RadioButton*>(winMgr.getWindow("RadioButton_B"));
		radioButton->setGroupID(1);
		radioButton->setID(102);
	radioButton = static_cast<RadioButton*>(winMgr.getWindow("RadioButton_C"));
		radioButton->setGroupID(1);
		radioButton->setID(103);
	radioButton = static_cast<RadioButton*>(winMgr.getWindow("RadioButton_1"));
		radioButton->setGroupID(2);
		radioButton->setID(201);
		radioButton->setSelected(true);
	radioButton = static_cast<RadioButton*>(winMgr.getWindow("RadioButton_2"));
		radioButton->setGroupID(2);
		radioButton->setID(202);
	radioButton = static_cast<RadioButton*>(winMgr.getWindow("RadioButton_3"));
		radioButton->setGroupID(2);
		radioButton->setID(203);
	radioButton = static_cast<RadioButton*>(winMgr.getWindow("RadioButton_A")); // Get handle of one radio button from the group
	uint valueRadioButtonLetters = radioButton->getSelectedButtonInGroup()->getID(); // Get selected ID
	radioButton = static_cast<RadioButton*>(winMgr.getWindow("RadioButton_3")); // Can obtain the handle of any radio button in the group
	uint valueRadioButtonNumbers = radioButton->getSelectedButtonInGroup()->getID();
	radioButton->setSelected(true); // Specify which button should appear selected by default
 
	/* Listbox */
	Listbox* listbox = static_cast<Listbox*>(winMgr.getWindow("Listbox"));
	listbox->setMultiselectEnabled(false);
	ListboxTextItem* itemListbox = new ListboxTextItem("Value A", 1);
		itemListbox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		listbox->addItem(itemListbox);
	itemListbox = new ListboxTextItem("Value B", 2);
		itemListbox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		listbox->addItem(itemListbox);
	itemListbox = new ListboxTextItem("Value C", 3);
		itemListbox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		listbox->addItem(itemListbox);
	itemListbox = new ListboxTextItem("Value D", 4);
		itemListbox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		listbox->addItem(itemListbox);
	listbox->setItemSelectState(itemListbox, true);
	listbox->ensureItemIsVisible(itemListbox);
	uint valueListbox = listbox->getFirstSelectedItem()->getID(); // Retrieve the ID of the selected listbox item
 
	/* Combobox */
	Combobox* combobox = static_cast<Combobox*>(winMgr.getWindow("Combobox"));
	combobox->setReadOnly(true);
	ListboxTextItem* itemCombobox = new ListboxTextItem("Value 1", 1);
		itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		combobox->addItem(itemCombobox);
	itemCombobox = new ListboxTextItem("Value 2", 2);
		itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		combobox->addItem(itemCombobox);
		itemCombobox->setSelected(true); // Select this item
		combobox->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
	itemCombobox = new ListboxTextItem("Value 3", 3);
		itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		combobox->addItem(itemCombobox);
	itemCombobox = new ListboxTextItem("Value 4", 4);
		itemCombobox->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		combobox->addItem(itemCombobox);
	String valueCombobox = combobox->getText(); // Retrieve the displayed text
	uint idCombobox = combobox->getSelectedItem()->getID(); // Retrieve the ID of the selected combobox item
 
	/* MultiColumnList */
	MultiColumnList* multiColumnList = static_cast<MultiColumnList*>(winMgr.getWindow("MultiColumnList"));\
	multiColumnList->addColumn("Col A", 0, UDim(0.32f, 0));
	multiColumnList->addColumn("Col B", 1, UDim(0.32f, 0));
	multiColumnList->addColumn("Col C", 2, UDim(0.32f, 0));
	multiColumnList->setSelectionMode(MultiColumnList::RowSingle); // MultiColumnList::RowMultiple
	ListboxTextItem* itemMultiColumnList;
	multiColumnList->addRow();
	itemMultiColumnList = new ListboxTextItem("A1", 101);
		itemMultiColumnList->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		multiColumnList->setItem(itemMultiColumnList, 0, 0); // ColumnID, RowID
	itemMultiColumnList = new ListboxTextItem("B1", 102);
		//itemMultiColumnList->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		// By commenting the line above a cell does not specify a selection indicator
		//  selecting that line will show a "gap" in the selection.
		multiColumnList->setItem(itemMultiColumnList, 1, 0); // ColumnID, RowID
	itemMultiColumnList = new ListboxTextItem("C1", 103);
		itemMultiColumnList->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		multiColumnList->setItem(itemMultiColumnList, 2, 0); // ColumnID, RowID
	multiColumnList->addRow();
	itemMultiColumnList = new ListboxTextItem("A2", 201);
		itemMultiColumnList->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		multiColumnList->setItem(itemMultiColumnList, 0, 1); // ColumnID, RowID
	itemMultiColumnList = new ListboxTextItem("B2", 202);
		itemMultiColumnList->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		multiColumnList->setItem(itemMultiColumnList, 1, 1); // ColumnID, RowID
	itemMultiColumnList = new ListboxTextItem("C2", 203);
		itemMultiColumnList->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		multiColumnList->setItem(itemMultiColumnList, 2, 1); // ColumnID, RowID
	MCLGridRef grid_ref(1, 0); // Select according to a grid reference; second row
	multiColumnList->setItemSelectState(grid_ref, true);
	ListboxItem* listboxItem = multiColumnList->getFirstSelectedItem();
	uint valueColumnA = listboxItem->getID(); // Retrieve the value of the selected item from column A
	listboxItem = multiColumnList->getNextSelected(listboxItem);
	uint valueColumnB = listboxItem->getID(); // Retrieve the value of the selected item from column B
	listboxItem = multiColumnList->getNextSelected(listboxItem);
	uint valueColumnC = listboxItem->getID(); // Retrieve the value of the selected item from column C
 
	/* TabControl */
	TabControl* winTabControl = static_cast<TabControl*>(winMgr.getWindow("TabControl"));
	winTabControl->setTabHeight(UDim(0.15f, 0.0f)); // Make the tab buttons a little bigger
	Window* tabPage = winMgr.getWindow("TabPane1");
		tabPage->setText("Page 1");
		tabPage->setSize(UVector2(UDim(1.0f, 0.0f), UDim(1.0f, 0.0f))); // Size to 100% of its parent, the TabControl
		tabPage->setPosition(UVector2(UDim(0.0f, 0.0f), UDim(0.0f, 0.0f))); // Move to the upper left corner of its parent
		winTabControl->addTab(tabPage);
	tabPage = winMgr.getWindow("TabPane2");
		tabPage->setText("Page 2");
		tabPage->setSize(UVector2(UDim(1.0f, 0.0f), UDim(1.0f, 0.0f))); 
		tabPage->setPosition(UVector2(UDim(0.0f, 0.0f), UDim(0.0f, 0.0f))); 
		winTabControl->addTab(tabPage);

	// draw everything
	while(device->run())
	{
		// draw only if the window is active
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, video::SColor(150,50,50,50));
			//draw scene
			smgr->drawAll();
			// draw gui
			System::getSingleton().renderGUI();

			driver->endScene();
		}
	}

	return 0;
}