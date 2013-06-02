#include "events.h"
#include "utils.h"
  
CtrlPlaneReceiver::CtrlPlaneReceiver(irr::scene::IAnimatedMeshSceneNode* Nmodele)
{
	//On pointe le mesh passe en parametre.
	plane = Nmodele;

	for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
}


bool CtrlPlaneReceiver::OnEvent(const irr::SEvent &event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}
  
  
void CtrlPlaneReceiver::updateMesh()
{
	//On vérifie que le pointeur est ok
	if(plane != 0)
	{
		//Qu'il s'agit de la flèche du haut
		if (IsKeyDown(irr::KEY_UP))
		{
			//Plonger vers le bas
			rotateNodeInLocalSpace(plane, 1.f, irr::core::vector3df(1,0,0));
		}

		//Qu'il s'agit de la flèche du bas
		if (IsKeyDown(irr::KEY_DOWN))
		{
			//Redresser
			rotateNodeInLocalSpace(plane, -1.f, irr::core::vector3df(1,0,0));
		}

		//Qu'il s'agit de la flèche de gauche
		if (IsKeyDown(irr::KEY_LEFT))
		{
			//Tonneau à gauche
			rotateNodeInLocalSpace(plane, 1.f, irr::core::vector3df(0,0,1));
		}

		//Qu'il s'agit de la flèche de droite
		if (IsKeyDown(irr::KEY_RIGHT))
		{
			//Tonneau à droite
			rotateNodeInLocalSpace(plane, -1.f, irr::core::vector3df(0,0,1));
		}

		//Qu'il s'agit de la touche Z
		if (IsKeyDown(irr::KEY_KEY_Z))
		{
			//On avance
			moveNodeInLocalSpace(plane, irr::core::vector3df(0,0,1), 0.5f);
			
		}
	}
}