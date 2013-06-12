#pragma once

#include <irrlicht.h>
#include <string>
#include "GLOBALS.h"

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

//Permet de faire tourner, sur 3 axes, un node (~objet) selon un degré donné et selon le repère local du node.
void rotateNodeInLocalSpace(irr::scene::ISceneNode* node, irr::f32 degs, const irr::core::vector3df& axis);

//Permet de faire bouger, sur 3 axes, un node (~objet) selon une direction et selon le repère local du node.
void moveNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& dir, irr::f32 dist);

//Permet de positionner la caméra par rapport à un node (~objet) selon un offset donné.
void makeCockpit(irr::scene::ICameraSceneNode *camera, irr::scene::ISceneNode *node, irr::core::vector3df offset);

/* Permet de traduire une touche sous forme de string en code EKEY_CODE d'irrlicht.
 * @return EKEY_CODE - Retourne le EKEY_CODE correspondant, EKEY_CODE::KEY_KEY_CODES_COUNT
 * si le code n'éxiste pas.
 */
irr::EKEY_CODE strToEkeyCode(std::string str);

/* Permet de traduire une touche sous forme de EKEY_CODE en string.
 * @return string - Le nom de la touche, NULL si la touche n'éxiste pas.
 */
std::string ekeyCodeToStr(irr::EKEY_CODE code);


/*
 * 
 */
constants::ACTION_CODE strToActionCode(std::string str);

/*
 * 
 */
std::string actionCodeToStr(constants::ACTION_CODE);

//Crée une explosion à la position indiquées
void createExplosion(irr::core::vector3df position);

//Crée un feu et renvoit un pointeur de IParticleSystemSceneNode
irr::scene::IParticleSystemSceneNode* createFire(irr::core::vector3df position);

//Crée de la fumée et renvoit un pointeur de IParticleSystemSceneNode
irr::scene::IParticleSystemSceneNode* createSmoke(irr::core::vector3df position);
