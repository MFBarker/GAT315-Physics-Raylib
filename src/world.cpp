#include "world.h"
#include "body.h"

Vector2 World::gravity{0,-9.81f};

World::~World()
{
}

void World::Initialize(Vector2 gravity, size_t poolsize)
{
    //m_gravity = gravity;
    World::gravity = gravity;
    m_bodies.reserve(poolsize);
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{
    Body* body = new Body(position, size, color);
    m_bodies.push_back(body);

    return body;
}

void World::Step(float timeStep)
{
    for (auto body : m_bodies)
    {
        body->Step(timeStep);
        body->ClearForce();
    }
}

void World::Draw(const Scene& scene)
{
    for (auto body : m_bodies)
    {
        body->Draw(scene);
    }
}

void World::DestroyAll()
{
    for (auto body : m_bodies)
    {
        delete body;
    }
    m_bodies.clear();
}

void World::UpdateBodies(float mass, float size, float damping, float gravityscale, int type)
{
    for (auto body : m_bodies)
    {
        body->mass = mass;
        body->size = size;
        body->damping = damping;
        body->gravityScale = gravityscale;
        body->type = body->IntToType(type);
    }
}

