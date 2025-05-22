#pragma once
#include "body.h"
#include "spring.h"
#include "raylib.h"
#include <vector>

using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0,-9.81f }, size_t poolsize = 30);
	void DestroyAll();

	void Step(float timeStep);
	void Draw(const class Scene& scene);

	//   BODY
	Body* CreateBody(const Vector2& position, float size,const Color& color);
	Body* CreateBody(Body::Type type, const Vector2& position, float mass, float size,const Color& color);
	bodies_t& GetBodies() { return m_bodies; }
	void UpdateBodies(float mass, float size, float damping, float gravityscale, int type);

	//   SPRING
	Spring* CreateSpring(struct Body* bodyA, struct Body* bodyB, float restLength, float stiffness);

	inline static Vector2 gravity{ 0,-9.81f };
	inline static float gravitation = 0;
	inline static float springStiffnessMultiplier = 1;
	inline static bool simulate = true;

private:
	bodies_t m_bodies;
	springs_t m_springs;
};