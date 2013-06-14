#pragma once

#include <irrlicht.h>
#include <string>
#include <CEGUI.h>
#include <vector>
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

void createExplosion(irr::core::vector3df position);

//Permet d'ajouter une ligne dans un tableau
void addTableRow(CEGUI::MultiColumnList* tabl, std::vector<char*> row_datas);

//Permet de vider le tableau
void clearTable(CEGUI::MultiColumnList* tabl);

//Permet de mettre à jour le tableau
void updateTable(CEGUI::MultiColumnList* tabl, std::vector<std::vector<char*>> table_datas);
