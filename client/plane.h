#pragma once

#include <string>
#include <irrlicht.h>

using namespace irr;

class Plane
{

private:
	std::string _name; //nom du model de l'avion
	scene::IAnimatedMeshSceneNode* _model;
	core::vector3df _position;
	core::vector3df _rotation;

	int MaxEnginePower;
	int FuelConsumption; // at defferent engine RPM
	int MaxFuelLoad;
	int MaxMissileLoad;
	int MaxCountermeasureLoad;
	int StallSpeed;
	int strength; // force de l'armure - vie
	
public:
	Plane(std::string);
	~Plane(void);

	void loadMesh();

	//// GETTERS AND SETTERS ////
	inline std::string getName() { return _name; }
	inline scene::IAnimatedMeshSceneNode* getMesh() { return _model; }
	inline core::vector3df getPosition() { return _position; }
	inline core::vector3df getRotation() { return _rotation; }

	int getMaxEP();
	int setMaxEP(int MaxEnginePower);

	int getFuelConsumption();
	int setFuelConsumption(int FuelConsumption);

	int getMaxFuelLoad();
	int setMaxFuelLoad(int MaxFuelLoad);

	int getMaxMissileLoad();
	int setMaxMissileLoad(int MaxMissileLoad);

	int getMaxCountermeasureLoad();
	int setMaxCountermeasureLoad(int MaxCountermeasureLoad);

	int getStrength();
	int setStrength(int strength);

	int getStallSpeed();
	int setStallSpeed(int StallSpeed);
};

