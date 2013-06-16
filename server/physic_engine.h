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
		ContactSensorCallback(btRigidBody* body, void* pointer, int& objectType) : btCollisionWorld::ContactResultCallback(), body(body), object(pointer), objectType(objectType) { }
	
		btRigidBody* body;
		void* object;
		int& objectType;

	public:

		virtual btScalar addSingleResult(btManifoldPoint& contactPoint, const btCollisionObject* object0, int partId0, int index0, const btCollisionObject* object1, int partId1, int index1)
		{
			btVector3 point;

			if(object0 == body)
			{
				point = contactPoint.m_localPointA;
			}
			else
			{
				assert(object1 == body && "body does not match either collision object");
				point = contactPoint.m_localPointB;
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

