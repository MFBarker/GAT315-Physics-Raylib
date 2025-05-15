#include "body.h"
#include "raymath.h"
#include "integrator.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;

	//apply gravity
	force += (World::gravity * gravityScale) * mass;
	//compute acceleration
	acceleration = (force * invMass);

	SemiImplicitIntegrator(*this,dt);
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force)
{
	this->force += force;
}

Body::Type Body::IntToType(int val)
{
	switch (val) {
		case 0: return Type::Static;
		case 1: return Type::Kinematic;
		case 2: return Type::Dynamic;
		default: return Type::Dynamic;
	}
}
