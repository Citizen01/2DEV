#include "plane.h"
#include "game.h"


Plane::Plane(game* g, std::string name)
{
	_game = g;
	//Cr�e un avion en fonction du nom de ce dernier
	_name = name;
	//Les 2 attributs suivants devront �tre assign� par le game engine
	//Qui les d�finira en fonctions des diff�rents spawns
	_position = core::vector3df(0.f, 0.f, 0.f);
	_rotation = core::vector3df(0.f, 0.f, 0.f);
	loadMesh(); //Chargement du mod�le 3d
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
  
    //On met l'auto-�clairage (debug)
	_model->setMaterialFlag(irr::video::EMF_LIGHTING, false);	
}