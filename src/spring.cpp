#include "spring.h"
#include "body.h"
#include "raymath.h"

void Spring::ApplyForce(float damping, float kMultiplier)
{
	//direction = bodyA <------- bodyB
	Vector2 direction = bodyA->position - bodyB->position;
	float lengthSqr = Vector2LengthSqr(direction);
	if (lengthSqr <= EPSILON) return;

	float length = sqrtf(lengthSqr);
	float displacement = length - restLength;
	float forceMagnitude = -(k * kMultiplier) * displacement;

	Vector2 ndirection = direction / length;
	Vector2 force = ndirection * forceMagnitude;
	
	//damp spring force to prevent oscillation
	Vector2 dv = bodyA->velocity - bodyB->velocity;
	float dampFactor = Vector2DotProduct(dv, ndirection) * damping;
	Vector2 dampingForce = ndirection * dampFactor;

	force -= dampingForce;

	//apply spring force
	bodyA->ApplyForce(force);
	bodyB->ApplyForce(Vector2Negate(force));
}

void Spring::ApplyForce(const Vector2& position, Body& body, float restLength, float k, float damping)
{
	//direction = position <--- bodyB
	Vector2 direction = position - body.position;
	float lengthSqr = Vector2LengthSqr(direction);
	if (lengthSqr <= EPSILON) return;

	//calculate spring force
	float length = sqrtf(lengthSqr);
	float displacement = length - restLength;
	float forceMagnitude = -k * displacement;

	Vector2 ndirection = direction / length;
	Vector2 force = ndirection * forceMagnitude;

	//damp spring force to prevent oscillation
	float dampFactor = Vector2DotProduct(body.velocity, ndirection) * damping;
	Vector2 dampingForce = ndirection * dampFactor;

	body.ApplyForce(force);
}

void Spring::Draw(const Scene& scene)
{
	scene.DrawLine(bodyA->position, bodyB->position, 3, WHITE);
}
