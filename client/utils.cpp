#include "utils.h"
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <iostream>
#include <fstream>
#include <irrlicht.h>

bool isDir(const std::string sDir)
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

bool isValidPath(const std::string path)
{
	return isDir(path);
}

bool isFile(const std::string file)
{
	std::ifstream ifile(file.c_str());
	return (bool)ifile;
}

void rotateNodeInLocalSpace(irr::scene::ISceneNode* node, irr::f32 degs, const irr::core::vector3df& axis)
{
    node->updateAbsolutePosition();
    irr::core::matrix4 m2 = node->getAbsoluteTransformation();
    irr::core::vector3df a = axis;
    m2.rotateVect(a);
    a.normalize();
 
    irr::core::quaternion q;
    q.fromAngleAxis(degs*irr::core::DEGTORAD, a);
    irr::core::matrix4 m1 = q.getMatrix();
 
    irr::core::matrix4 m = m1*m2;
    node->setRotation(m.getRotationDegrees());
}

void moveNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& dir, irr::f32 dist)
{
    node->updateAbsolutePosition();
    irr::core::matrix4 m = node->getAbsoluteTransformation();
    irr::core::vector3df d = dir;
    m.rotateVect(d);
    d.normalize();
    
    irr::core::vector3df pos = node->getAbsolutePosition() + d * dist;
    node->setPosition(pos);
}

void makeCockpit(irr::scene::ICameraSceneNode *camera, //camera
                irr::scene::ISceneNode *node, //scene node (plane)
                irr::core::vector3df offset) //relative position of camera to node (ship)
{
    //get rotation matrix of node - Zeuss must be getRotation not getRelativeTransformation
   irr::core::matrix4 m;
   m.setRotationDegrees(node->getRotation());
   
    // transform forward vector of camera
    irr::core::vector3df frv = irr::core::vector3df (0.0f, 0.0f, 1.0f);
    m.transformVect(frv);
   
    // transform upvector of camera
    irr::core::vector3df upv = irr::core::vector3df (0.0f, 1.0f, 0.0f);
    m.transformVect(upv);

    // transform camera offset (thanks to Zeuss for finding it was missing)
    m.transformVect(offset);
   
    // set camera
    camera->setPosition(node->getPosition() + offset); //position camera in front of the ship
    camera->setUpVector(upv); //set up vector of camera >> Zeuss - tested with +node->getPostion() and it didnt work, but this works fine.
    camera->setTarget(node->getPosition() + frv); //set target of camera (look at point) >> Zeuss - Dont forget to add the node positiob
} 