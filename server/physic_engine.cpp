#include "physic_engine.h"

using namespace std;
using namespace irr;

//Initialisation de l'attribut static
physics_engine* physics_engine::m_Instance = NULL;

physics_engine::physics_engine(void)
{
	m_Broadphase = new btDbvtBroadphase();
	m_CollisionConfiguration = new btDefaultCollisionConfiguration();
	m_Dispatcher = new btCollisionDispatcher(m_CollisionConfiguration);
	m_Solver = new btSequentialImpulseConstraintSolver;
	
	m_DynamicsWorld = new btDiscreteDynamicsWorld(m_Dispatcher, m_Broadphase, m_Solver, m_CollisionConfiguration);
	m_DynamicsWorld->setGravity(btVector3(0, -10, 0));
	//m_DynamicsWorld->setGravity(btVector3(0, 0, 0));

	//Sol invisible à la hauteur 0
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	m_DynamicsWorld->addRigidBody(groundRigidBody);

	vector<btRigidBody*> m_RigidBodies;
}

physics_engine* physics_engine::getSingleton()
{
	if (!m_Instance)
	{
		m_Instance = new physics_engine();
	}
	return m_Instance;
}


physics_engine::~physics_engine(void)
{
	delete m_DynamicsWorld;
	delete m_Broadphase;
	delete m_CollisionConfiguration;
	delete m_Dispatcher;
	delete m_Solver;
}

void physics_engine::updatePhysics(u32 deltaTime)
{
	m_DynamicsWorld->stepSimulation(deltaTime * 0.001f, 60);

	// Relay the object's orientation to irrlicht
	for(unsigned int i = 0; i< m_RigidBodies.size(); i++)
	{
		updateIrrlichtNode(m_RigidBodies.at(i));
	}
}

// Passes bullet's orientation to irrlicht
void physics_engine::updateIrrlichtNode(btRigidBody* body)
{
	scene::ISceneNode* node = ((collidableObject*)body->getUserPointer())->getNode();

	// Set position
	btVector3 point = body->getCenterOfMassPosition();
	node->setPosition(core::vector3df((f32)point[0], (f32)point[1], (f32)point[2]));

	// Set rotation
	core::vector3df euler;
	const btQuaternion& bulletQuaternion = body->getOrientation();
	core::quaternion irrLichtQuaternion(bulletQuaternion.getX(), bulletQuaternion.getY(), bulletQuaternion.getZ(), bulletQuaternion.getW());
	irrLichtQuaternion.toEuler(euler);
	euler *= core::RADTODEG;
	node->setRotation(euler);
}


void physics_engine::addPlane(Plane* plane)
{
	std::string planeName = plane->getName();
	scene::IAnimatedMeshSceneNode* node = plane->getMesh();
	core::vector3df position = node->getPosition();
	core::vector3df rotation = node->getRotation();

	if (planeName == "SU25")
	{
		// Set the initial position of the object
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(position.X, position.Y, position.Z));
		transform.setRotation(btQuaternion(rotation.Y * core::DEGTORAD, rotation.X * core::DEGTORAD, rotation.Z * core::DEGTORAD));

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);

		// Create the shapes
		btVector3 halfExtentsBody(3 * 0.5f, 4.6 * 0.5f, 15 * 0.5f);
		btCollisionShape* bodyShape = new btBoxShape(halfExtentsBody);

		btVector3 halfExtentsWings(15 * 0.5f, 1 * 0.5f, 4 * 0.5f);
		btCollisionShape* wingsShape = new btBoxShape(halfExtentsWings);
		
		btTransform childTransform;
		childTransform.setIdentity();
		childTransform.setOrigin(btVector3(0, 0, 0));

		btCompoundShape* fullShape = new btCompoundShape();
		fullShape->addChildShape(childTransform, bodyShape);
		fullShape->addChildShape(childTransform, wingsShape);

		// Add mass
		btVector3 localInertia;
		fullShape->calculateLocalInertia(1000, localInertia);

		// Create the rigid body object
		btRigidBody* body = new btRigidBody(1000, motionState, fullShape, localInertia);

		body->setFriction(0);

		// Store a pointer to the irrlicht node so we can update it later
		body->setUserPointer((void*)(plane));

		// Add it to the world
		m_DynamicsWorld->addRigidBody(body);
		m_RigidBodies.push_back(body);

		plane->setBody(body);

		ContactSensorCallback callback;
		m_DynamicsWorld->contactTest(body, callback);
	}
	//else if à faire pour les autres types d'avion
}

void physics_engine::addProjectile(Projectile* projectile)
{
	std::string projectileType = projectile->getModelType().C_String();
	scene::IAnimatedMeshSceneNode* node = projectile->getMesh();
	core::vector3df position = node->getPosition();
	core::vector3df rotation = node->getRotation();
	core::vector3df box = node->getBoundingBox().getExtent();

	if (projectileType == "missile")
	{
		// Set the initial position of the object
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(position.X, position.Y, position.Z));

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);

		// Create the shapes
		btVector3 halfExtents(box.X * 0.5f, 0.f, box.Z * 0.5f);
		btCollisionShape* shape = new btCylinderShapeZ(halfExtents);

		// Add mass
		btVector3 localInertia;
		shape->calculateLocalInertia(10, localInertia);

		// Create the rigid body object
		btRigidBody* body = new btRigidBody(10, motionState, shape, localInertia);

		// Store a pointer to the irrlicht node so we can update it later

		body->setUserPointer((void*)(projectile));

		body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

		// Add it to the world
		m_DynamicsWorld->addRigidBody(body);
		m_RigidBodies.push_back(body);
		
		body->setFriction(0);
		body->setGravity(btVector3(0, 0, 0));

		projectile->setBody(body);

		btMatrix3x3 matrix = body->getWorldTransform().getBasis();

		btVector3 axis1 = btVector3(1, 0, 0);
		btScalar angle1 = btScalar(rotation.X * core::DEGTORAD);
		matrix *= btMatrix3x3(btQuaternion(axis1, angle1));

		btVector3 axis2 = btVector3(0, 1, 0);
		btScalar angle2 = btScalar(rotation.Y * core::DEGTORAD);
		matrix *= btMatrix3x3(btQuaternion(axis2, angle2));

		btVector3 axis3 = btVector3(0, 0, 1);
		btScalar angle3 = btScalar(rotation.Z * core::DEGTORAD);
		matrix *= btMatrix3x3(btQuaternion(axis3, angle3));

		body->getWorldTransform().setBasis(matrix);
		
		body->translate(body->getWorldTransform().getBasis().getColumn(2) * 10);

		body->setLinearVelocity(body->getWorldTransform().getBasis().getColumn(2) * projectile->getSpeed());

		ContactSensorCallback callback;
		m_DynamicsWorld->contactTest(body, callback);
	}
	//else if à faire pour les autres types d'avion
}

void physics_engine::rotate(btRigidBody* body, btVector3& axis, int angle)
{
	btScalar scalar = angle;
	body->activate(true);
	btMatrix3x3 matrix = body->getWorldTransform().getBasis();
	matrix *= btMatrix3x3(btQuaternion(axis, scalar * core::DEGTORAD));
	body->getWorldTransform().setBasis(matrix);

	//body->applyTorque(body->getInvInertiaTensorWorld().inverse() * (body->getWorldTransform().getBasis() * rotation));
}