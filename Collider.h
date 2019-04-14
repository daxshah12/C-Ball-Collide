#pragma once

#include "GameObject.h"
#include "Plane.h"

class Collider
{
public:
	Collider();
	~Collider();

	static void SimpleNewtonMotion(GameObject &model, const float deltaTime);
	static bool PlanSphereCollision(const GameObject &model, const Plane &p);
	static bool SphereSphereCollision(const GameObject &model1, const GameObject &model2);
	static void SphereSphereCollisionResponse(GameObject &model1, GameObject &model2);
	static void SpherePlaneCollisionResponse(GameObject &model1,  const Plane &p);

};



