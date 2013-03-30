
#include <irrlicht.h>

//Permet de controler un avion (mouvements, actions, ...)
class CtrlPlaneReceiver : public irr::IEventReceiver
{
  
public :
  
    //Le constructeur.
    CtrlPlaneReceiver(irr::scene::IAnimatedMeshSceneNode* Nmodele);

    //Capte automatiquement les events.
    virtual bool OnEvent(const irr::SEvent &event);
    
	inline bool IsKeyDown(irr::EKEY_CODE keyCode) { return KeyIsDown[keyCode]; }

	//Met à jour la position et la rotation du mesh en fonction des touches pressées.
    void updateMesh();
  
private :
  
    //Le modele qu'on va controler.
    irr::scene::IAnimatedMeshSceneNode* m_Nmodele;

	// We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};