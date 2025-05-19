#pragma once
#include "body.h"
#include "raylib.h"
#include <vector>

using bodies_t = std::vector<Body*>;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0,-9.81f }, size_t poolsize = 30);

	Body* CreateBody(const Vector2& position, float size,const Color& color);
	void Step(float timeStep);
	void Draw(const class Scene& scene);

	void DestroyAll();

	bodies_t& GetBodies() { return m_bodies; }

	void UpdateBodies(float mass, float size, float damping, float gravityscale, int type);

	static Vector2 gravity;

private:
	bodies_t m_bodies;
};