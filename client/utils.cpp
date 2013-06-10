#include "utils.h"
#include "GLOBALS.h"
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <iostream>
#include <fstream>

using namespace std;
using namespace irr;
using namespace constants;

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

void rotateNodeInLocalSpace(scene::ISceneNode* node, f32 degs, const core::vector3df& axis)
{
	node->updateAbsolutePosition();
	core::matrix4 m2 = node->getAbsoluteTransformation();
	core::vector3df a = axis;
	m2.rotateVect(a);
	a.normalize();
 
	core::quaternion q;
	q.fromAngleAxis(degs*core::DEGTORAD, a);
	core::matrix4 m1 = q.getMatrix();
 
	core::matrix4 m = m1*m2;
	node->setRotation(m.getRotationDegrees());
}

void moveNodeInLocalSpace(scene::ISceneNode* node, const core::vector3df& dir, f32 dist)
{
	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df d = dir;
	m.rotateVect(d);
	d.normalize();
	
	core::vector3df pos = node->getAbsolutePosition() + d * dist;
	node->setPosition(pos);
}

void makeCockpit(scene::ICameraSceneNode *camera, //camera
				scene::ISceneNode *node, //scene node (plane)
				core::vector3df offset) //relative position of camera to node
{
	//get rotation matrix of node
   core::matrix4 m;
   m.setRotationDegrees(node->getRotation());
   
	// transform forward vector of camera
	core::vector3df frv = core::vector3df (0.0f, 0.0f, 1.0f);
	m.transformVect(frv);
   
	// transform upvector of camera
	core::vector3df upv = core::vector3df (0.0f, 1.0f, 0.0f);
	m.transformVect(upv);

	// transform camera offset
	m.transformVect(offset);
   
	// set camera
	camera->setPosition(node->getPosition() + offset); //position camera in front of the ship
	camera->setUpVector(upv); //set up vector of camera
	camera->setTarget(node->getPosition() + frv); //set target of camera (look at point)
}

extern std::map<std::string,irr::EKEY_CODE> KEYMAP;

EKEY_CODE strToEkeyCode(string str)
{
	if (KEYMAP.find(str) != KEYMAP.end())
		return KEYMAP.at(str);
	else
		return KEYMAP.at("INVALID_KEY");
}

string ekeyCodeToStr(EKEY_CODE code)
{
	for (std::map<std::string,irr::EKEY_CODE>::iterator it=KEYMAP.begin(); it!=KEYMAP.end(); ++it)
	{
		if (it->second == code)
			return it->first;
	}
	return NULL;
}

extern std::map<std::string,ACTION_CODE> ACTIONMAP;

constants::ACTION_CODE strToActionCode(std::string str)
{
	if (ACTIONMAP.find(str) != ACTIONMAP.end())
		return ACTIONMAP.at(str);
	else
		return ACTIONMAP.at("INVALID_ACTION");
}

std::string actionCodeToStr(constants::ACTION_CODE code)
{
	for (std::map<std::string,constants::ACTION_CODE>::iterator it=ACTIONMAP.begin(); it!=ACTIONMAP.end(); ++it)
	{
		if (it->second == code)
			return it->first;
	}
	return NULL;
}