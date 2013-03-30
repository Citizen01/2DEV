#include "plane.h"
#include "game.h"


Plane::Plane(game* g, std::string name)
{
	_game = g;
	//Crée un avion en fonction du nom de ce dernier
	_name = name;
	//Les 2 attributs suivants devront être assigné par le game engine
	//Qui les définira en fonctions des différents spawns
	_position = core::vector3df(0.f, 0.f, 0.f);
	_rotation = core::vector3df(0.f, 0.f, 0.f);
	loadMesh(); //Chargement du modèle 3d
}


Plane::~Plane(void)
{
}


void Plane::loadMesh()
{
	video::IVideoDriver* driver = _game->getGraphicEngine()->getDriver();
	scene::ISceneManager* smgr = _game->getGraphicEngine()->getSceneManager();
	std::string modefile = PATH_TO_MEDIA + "/planes/SU 25/SU 25.3DS";
    _model = smgr->addAnimatedMeshSceneNode(smgr->getMesh(modefile.c_str()));
    
	/*irr::scene::IAnimatedMeshSceneNode* Nmodele =
    smgr->addAnimatedMeshSceneNode(_model);*/
  
    //On met l'auto-éclairage (debug)
	_model->setMaterialFlag(irr::video::EMF_LIGHTING, false);	
}