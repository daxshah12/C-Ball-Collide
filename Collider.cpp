#include "Collider.h"
#include "VMath.h"
#include <stdio.h>
#include <iostream>
using namespace MATH;

Collider::Collider()
{
}


Collider::~Collider()
{
}

//Moving the Ball
void Collider::SimpleNewtonMotion(GameObject &model, const float deltaTime)
{
	model.position += model.velocity * deltaTime + 0.5f * model.accel * deltaTime * deltaTime;
	model.velocity += model.accel * deltaTime;
}

//checking if the the ball hit the plan or not
bool Collider::PlanSphereCollision(const GameObject & model, const Plane &p) 
{
	float dist = VMath::distance(model.position, p);
	printf("dist = *=%f\n", dist);
	if (dist <= 0.0f)
	{
		return true;
	}
	return false;
}

//Checking if the collision happend or not
bool Collider::SphereSphereCollision(const GameObject &model1, const GameObject &model2)
{
	float distance = VMath::distance(model1.position, model2.position);
	if (distance < model1.radius + model2.radius)
	{
		return true;
	}
	return false;
}

//if the collision happend then it collides back
void Collider::SphereSphereCollisionResponse(GameObject &model1, GameObject &model2)
{
	

	float e = 1.0f;
	Vec3 lineOfAction = model1.position - model2.position;
	Vec3 normalizedLineOfAction = VMath::normalize(lineOfAction);
	float v1projected = VMath::dot(normalizedLineOfAction, model1.velocity);
	float v2projected = VMath::dot(normalizedLineOfAction, model2.velocity);

	float new1projected = (((model1.mass - e * model2.mass) * v1projected) +
		((1.0f + e) * model2.mass * v2projected)) / (model1.mass + model2.mass);

	float new2projected = (((model2.mass - e * model1.mass) * v2projected) +
		((1.0f + e) * model1.mass * v1projected)) / (model1.mass + model2.mass);

	model1.velocity = model1.velocity + (new1projected - v1projected) * normalizedLineOfAction;
	model2.velocity = model2.velocity + (new2projected - v2projected) * normalizedLineOfAction;

}

//  if the ball hit the plane then it collides back
void Collider::SpherePlaneCollisionResponse(GameObject &model1, const Plane &p)
{


	Plane plane = Plane(p);

	Vec3 intialVelocity = model1.velocity;
	
	plane.normalize();
	
	Vec3 normal = plane;

	float dot = intialVelocity.Dot(normal); 
	float  mag = pow(normal.Mag(), 2.0f);
	float some = dot / mag;

	Vec3 finalvelocity =  (some * normal) + intialVelocity;

	model1.velocity = finalvelocity;

	









	//std::cout << p.x <<"," <<  p.y << "," << p.z << std::endl; ;

	//Vec3 normal = Vec3(p.x, p.y, p.z);

//	std::cout << normal.x << "," << normal.y << "," << normal.z << std::endl;

	//VMath::normalize(normal);

//	float dot = VMath::dot(-model1.velocity, normal);
//	std::cout << dot;

	//Vec3 P = normal * dot;
//	model1.velocity += P * 2;

//	std::cout << model1.velocity.x << "," << model1.velocity.y << "," << model1.velocity.z << std::endl;
}