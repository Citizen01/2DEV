#pragma once

#include <string>

#include <irrlicht.h>

#include <btBulletDynamicsCommon.h>

//Permet de faire tourner, sur 3 axes, un node (~objet) selon un degré donné et selon le repère local du node.
irr::core::vector3df rotateNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& axis, irr::f32 degs);

//Permet de faire bouger, sur 3 axes, un node (~objet) selon une direction et selon le repère local du node.
irr::core::vector3df moveNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& dir, irr::f32 dist);

/* Fonction qui permet de vérifier si un dossier donné existe.
 * @return bool - true si le dossier existe, false sinon.
 */
bool isDir(const std::string);

/* Fonction qui permet de vérifier si un path existe.
 * @return bool - true si le path donné existe, false sinon.
 */
bool isValidPath(const std::string);

/* Fonction qui permet de vérifier si un fichier existe et qu'il est lisible.
 * @return bool - true si le fichier existe et accéssible en lecture, false sinon.
 */
bool isFile(const std::string);