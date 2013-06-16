#include "utils.h"
#include "GLOBALS.h"
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <iostream>
#include <fstream>
#include "app.h"

using namespace std;
using namespace irr;
using namespace constants;
using namespace CEGUI;

bool isDir(const string sDir)
{
	if ( _access( sDir.c_str(), 0 ) == 0 )
	{
		struct stat status;
		stat( sDir.c_str(), &status );

		if ( status.st_mode & S_IFDIR )
			return true;
	}
	return false;
}

bool isValidPath(const string path)
{
	return isDir(path);
}

bool isFile(const string file)
{
	ifstream ifile(file.c_str());
	return (bool)ifile;
}

extern map<string,EKEY_CODE> KEYMAP;

EKEY_CODE strToEkeyCode(string str)
{
	if (KEYMAP.find(str) != KEYMAP.end())
		return KEYMAP.at(str);
	else
		return KEYMAP.at("INVALID_KEY");
	
}

string ekeyCodeToStr(EKEY_CODE code)
{
	for (map<string,irr::EKEY_CODE>::iterator it=KEYMAP.begin(); it!=KEYMAP.end(); ++it)
	{
		if (it->second == code)
			return it->first;
	}
	return NULL;
}

extern map<string,ACTION_CODE> ACTIONMAP;

constants::ACTION_CODE strToActionCode(string str)
{
	if (ACTIONMAP.find(str) != ACTIONMAP.end())
		return ACTIONMAP.at(str);
	else
		return ACTIONMAP.at("INVALID_ACTION");
}

string actionCodeToStr(constants::ACTION_CODE code)
{
	for (map<string,constants::ACTION_CODE>::iterator it=ACTIONMAP.begin(); it!=ACTIONMAP.end(); ++it)
	{
		if (it->second == code)
			return it->first;
	}
	return NULL;
}

scene::IParticleSystemSceneNode* createFire(irr::core::vector3df position){
		IrrlichtDevice* device =  App::getSingleton()->getGraphicEngine()->getDevice();
		scene::ISceneManager* smgr = device->getSceneManager();
		scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode(false);
		video::IVideoDriver* driver = App::getSingleton()->getGraphicEngine()->getDriver();

		//create a particle
		scene::IParticleEmitter* em = ps->createBoxEmitter(
		core::aabbox3d<f32>(-7,0,-7,7,1,7), // emitter size
		core::vector3df(0.0f,0.06f,0.0f),   // initial direction
		80,100,                             // emit rate
		video::SColor(0,255,255,255),       // darkest color
		video::SColor(0,255,255,255),       // brightest color
		800,2000,0,                         // min and max age, angle
		core::dimension2df(10.f,10.f),         // min size
		core::dimension2df(20.f,20.f));        // max size
		
		ps->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it
		scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
		
		ps->addAffector(paf); // same goes for the affector
		paf->drop();

		core::vector3df pl_pos = position;
		ps->setPosition(pl_pos);
		ps->setScale(core::vector3df(2,2,2));
		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, driver->getTexture("../Media/test/fire.bmp"));
		ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

		return ps;
}

void createExplosion(irr::core::vector3df position){

		scene::IParticleSystemSceneNode* ps = App::getSingleton()->getGraphicEngine()->getSceneManager()->addParticleSystemSceneNode(false);
		video::IVideoDriver* driver = App::getSingleton()->getGraphicEngine()->getDriver();

		//create a particle
		scene::IParticleEmitter* em = ps->createBoxEmitter(
		core::aabbox3d<f32>(0.1,0.1,0.1,0.1,0.1,0.1), // emitter size
		core::vector3df(0.01f,0.01f,0.01f),   // initial direction
		500,500,                             // emit rate
		video::SColor(0,255,255,255),       // darkest color
		video::SColor(0,255,255,255),       // brightest color
		1000,1000,360,                         // min and max age, angle
		core::dimension2df(6.f,6.f),         // min size
		core::dimension2df(6.f,6.f));        // max size
		
		ps->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it
		scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
		
		ps->addAffector(paf); // same goes for the affector
		paf->drop();

		core::vector3df pl_pos = position;
		ps->setPosition(pl_pos);
		//ps->setScale(core::vector3df(2,2,2));
		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, driver->getTexture("../Media/test/fire.bmp"));
		ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

void addTableRow(MultiColumnList* tabl, vector<string> row_datas)
{	
	if(!tabl || row_datas.size() <= 0)
		return;

	uint rownum = tabl->addRow();
	for (unsigned int i=0; i < tabl->getColumnCount(); i++)
	{
		ListboxTextItem* list = new ListboxTextItem(row_datas[i]);
		tabl->setItem(list, i, rownum);
		list->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		//tabl->setItemSelectState(list, true);
	}
}

void clearTable(MultiColumnList* tabl)
{
	if(!tabl)
		return;

	tabl->resetList();
}


void updateTable(CEGUI::MultiColumnList* tabl, std::vector<std::vector<string>> table_datas)
{
	if(!tabl || table_datas.size() <= 0)
		return;

	clearTable(tabl);
	for (unsigned int i = 0; i < table_datas.size(); i++)
		addTableRow(tabl, table_datas[i]);
}

void removeRow(MultiColumnList* tabl, int line)
{
	if(!tabl)
		return;

	ListboxItem* selectedItem = tabl->getFirstSelectedItem();
	int index = findIndexOfItem(tabl, selectedItem);
	if (index != -1)
	{
		tabl->removeRow(line);
	}
}

int findIndexOfItem(MultiColumnList* tabl, ListboxItem* item)
{
	if(!tabl || !item)
		return -1;

	for (unsigned int i=0; i < tabl->getRowCount(); i++)
			if (tabl->isListboxItemInRow(item, i))
				return i;
	return -1;
}

string intToString(int number)
{
	std::ostringstream ostr;
	ostr << number; 
	return ostr.str();
}