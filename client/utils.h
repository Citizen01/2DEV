#include <irrlicht.h>
#include <string>

/* Fonction qui permet de v�rifier si un
 * chemin donn� est valide (= s'il existe) */
bool isDir(const std::string);

/* Fonction qui permet de v�rifier si un dossier
 * existe en fonction du chemin donn� */
bool isValidPath(const std::string);

/* Fonction qui permet de v�rifier si un
 * fichier existe et qu'il est readable */
bool isFile(const std::string);

void rotateNodeInLocalSpace(irr::scene::ISceneNode* node, irr::f32 degs, const irr::core::vector3df& axis);

void moveNodeInLocalSpace(irr::scene::ISceneNode* node, const irr::core::vector3df& dir, irr::f32 dist);

void makeCockpit(irr::scene::ICameraSceneNode *camera, irr::scene::ISceneNode *node, irr::core::vector3df offset);
