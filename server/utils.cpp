#include "utils.h"

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
	q.fromAngleAxis(degs*core::DEGTORAD, a);
	core::matrix4 m1 = q.getMatrix();
 
	core::matrix4 m = m1*m2;
	node->setRotation(m.getRotationDegrees());

	return m.getRotationDegrees();
}