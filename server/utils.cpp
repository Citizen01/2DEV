#include "utils.h"

#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <fstream>

using namespace std;
using namespace irr;

core::vector3df moveNodeInLocalSpace(scene::ISceneNode* node, const core::vector3df& dir, f32 dist)
{
	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df d = dir;
	m.rotateVect(d);
	d.normalize();
	
	core::vector3df pos = node->getAbsolutePosition() + d * dist;
	node->setPosition(pos);
	
	return pos;
}

core::vector3df rotateNodeInLocalSpace(scene::ISceneNode* node, const core::vector3df& axis, f32 degs)
{
	node->updateAbsolutePosition();
	core::matrix4 m2 = node->getAbsoluteTransformation();
	core::vector3df a = axis;
	m2.rotateVect(a);
	a.normalize();
 
	core::quaternion q;
	q.fromAngleAxis(degs * core::DEGTORAD, a);
	core::matrix4 m1 = q.getMatrix();
 
	core::matrix4 m = m1 * m2;
	node->setRotation(m.getRotationDegrees());

	return m.getRotationDegrees();
}

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