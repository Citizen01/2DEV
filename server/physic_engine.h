#pragma once

#include <vector>
#include <irrlicht.h>
#include <btBulletDynamicsCommon.h>

#include "plane.h"
#include "projectile.h"

class physics_engine
{
private:

	enum ObjectTypes
	{
		MAP,
		BASE,
		PLANE,
		PROJECTILE
	};	

	static physics_engine* m_Instance; // Contient la seule instance de physics_engine
	physics_engine(void); //Seulement appelé par getSingleton()

	btBroadphaseInterface* m_Broadphase;
	btDefaultCollisionConfiguration* m_CollisionConfiguration;
	btCollisionDispatcher* m_Dispatcher;
	btSequentialImpulseConstraintSolver* m_Solver;

	btDiscreteDynamicsWorld* m_DynamicsWorld;

	//Stocke tous les rigidBody ajoutés
	std::vector<btRigidBody*> m_RigidBodies;

public:

	struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback
	{
		ContactSensorCallback() : btCollisionWorld::ContactResultCallback() { }

		btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
		{
			int type0 = ((collidableObject*)((btRigidBody*)colObj0Wrap->getCollisionObject())->getUserPointer())->objectType;
			int type1 = ((collidableObject*)((btRigidBody*)colObj1Wrap->getCollisionObject())->getUserPointer())->objectType;

			switch(ObjectTypes(type0))
			{
			case MAP:
				break;
			case BASE:
				break;
			/*case PLANE:
				Plane* plane = (Plane*)((btRigidBody*)colObj0Wrap->getCollisionObject())->getUserPointer();
				if(type1 == MAP)
				{
					plane->takeDammage(-1);
				}
				if(type1 == BASE*/
			}
			return 0;
		}
	};

	static physics_engine* getSingleton(); //Récupère l'instance de physics_engine
	~physics_engine(void);

	void updatePhysics(irr::u32 deltaTime);

	//Met à jour la position et la rotation du node irrlicht correspondant au btRigidBody donné
	void updateIrrlichtNode(btRigidBody* body);
	
	//Ajoute un ISceneNode au moteur physique
	void addPlane(Plane* plane);
	void addProjectile(Projectile* projectile);

	void rotate(btRigidBody* body, btVector3& direction);
};

