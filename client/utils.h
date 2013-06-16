#pragma once

#include <irrlicht.h>
#include <string>
#include <CEGUI.h>
#include <vector>
#include "GLOBALS.h"

/* Fonction qui permet de v�rifier si un dossier donn� existe.
 * @return bool - true si le dossier existe, false sinon.
 */
bool isDir(const std::string);

/* Fonction qui permet de v�rifier si un path existe.
 * @return bool - true si le path donn� existe, false sinon.
 */
bool isValidPath(const std::string);

/* Fonction qui permet de v�rifier si un fichier existe et qu'il est lisible.
 * @return bool - true si le fichier existe et acc�ssible en lecture, false sinon.
 */
bool isFile(const std::string);

//Permet de faire tourner, sur 3 axes, un node (~objet) selon un degr� donn� et selon le rep�re local du node.
void rotateNodeInLocalSpace(irr::scene::ISceneNode* node, irr::f32 degs, const irr::core::vector3df& axis);

//Permet de faire bouger, sur 3 axes, un node (~objet) selon une direction et selon le rep�re local du node.
void moveNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& dir, irr::f32 dist);

//Permet de positionner la cam�ra par rapport � un node (~objet) selon un offset donn�.
void makeCockpit(irr::scene::ICameraSceneNode *camera, irr::scene::ISceneNode *node, irr::core::vector3df offset);

/* Permet de traduire une touche sous forme de string en code EKEY_CODE d'irrlicht.
 * @return EKEY_CODE - Retourne le EKEY_CODE correspondant, EKEY_CODE::KEY_KEY_CODES_COUNT
 * si le code n'�xiste pas.
 */
irr::EKEY_CODE strToEkeyCode(std::string str);

/* Permet de traduire une touche sous forme de EKEY_CODE en string.
 * @return string - Le nom de la touche, NULL si la touche n'�xiste pas.
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

//Cr�e une explosion � la position indiqu�es
void createExplosion(irr::core::vector3df position);

//Permet d'ajouter une ligne dans un tableau
void addTableRow(CEGUI::MultiColumnList* tabl, std::vector<std::string> row_datas);

//Permet de vider le tableau
void clearTable(CEGUI::MultiColumnList* tabl);

//Permet de mettre � jour le tableau
void updateTable(CEGUI::MultiColumnList* tabl, std::vector<std::vector<std::string>> table_datas);

//Permet de supprimer la "line"�me ligne du tableau
void removeRow(CEGUI::MultiColumnList* tabl, int line);

//Permet de trouver l'index de l'item sp�cifi� dans le tableau donn�
int findIndexOfItem(CEGUI::MultiColumnList* tabl, CEGUI::ListboxItem* item);

//Permet de r�cup�rer la liste des thumbnails des avions
std::vector<std::string> getPlaneThumbs();

//Cr�e un feu et renvoit un pointeur de IParticleSystemSceneNode
irr::scene::IParticleSystemSceneNode* createFire(irr::core::vector3df position);

//Cr�e de la fum�e et renvoit un pointeur de IParticleSystemSceneNode
irr::scene::IParticleSystemSceneNode* createSmoke(irr::core::vector3df position);
