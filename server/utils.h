#pragma once

#include <irrlicht.h>

//Permet de faire tourner, sur 3 axes, un node (~objet) selon un degré donné et selon le repère local du node.
irr::core::vector3df rotateNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& axis, irr::f32 degs);

//Permet de faire bouger, sur 3 axes, un node (~objet) selon une direction et selon le repère local du node.
irr::core::vector3df moveNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& dir, irr::f32 dist);
