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

extern map<string,irr::EKEY_CODE> KEYMAP;

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

void createExplosion(irr::core::vector3df position){
		IrrlichtDevice* device =  App::getSingleton()->getGraphicEngine()->getDevice();
		scene::ISceneManager* smgr = device->getSceneManager();
		scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode(false);
		video::IVideoDriver* driver = App::getSingleton()->getGraphicEngine()->getDriver();
	
		//create a particle
		scene::IParticleSphereEmitter* em = ps->createSphereEmitter
			(position,
			100.00f,
			core::vector3df(0.3f,0.3f,0.3f),
			5,
			10,
			video::SColor(255, 0, 0,0),
			video::SColor(255,255,255,255),
			2000,
			40000,
			0,
			core::dimension2df(5.0f, 5.0f),
			core::dimension2df(50.0f, 50.0f));
		
		ps->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it
		scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
		
		ps->addAffector(paf); // same goes for the affector
		paf->drop(); 

		ps->setPosition(position);
		ps->setScale(core::vector3df(2,2,2));
		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, driver->getTexture((PATH_TO_MEDIA + "/test/fire.bmp").c_str()));
		ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

void addTableRow(MultiColumnList* tabl, vector<char*> row_datas)
{	
	uint rownum = tabl->addRow();
	for (unsigned int i=0; i < tabl->getColumnCount(); i++)
	{
		ListboxTextItem* list = new ListboxTextItem(row_datas[i]);
		tabl->setItem(list, i, rownum);
	}	
}

void clearTable(MultiColumnList* tabl)
{
		tabl->resetList();
}

void updateTable(MultiColumnList* tabl, vector<vector<char*>> table_datas)
{
	clearTable(tabl);
	for (unsigned int i = 0; i < table_datas.size(); i++)
		addTableRow(tabl, table_datas[i]);
}

void removeRow(MultiColumnList* tabl, int line)
{
	tabl->removeRow(line);
}