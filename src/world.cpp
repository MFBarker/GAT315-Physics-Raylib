#include "world.h"
#include "gravitation.h"
#include "collision.h"

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

Body* World::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color)
{
    Body* body = new Body(type, position, mass, size, color);
    m_bodies.push_back(body);

    return body;
}

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness,float damping)
{
    Spring* spring = new Spring(bodyA,bodyB,restLength, stiffness, damping);
    m_springs.push_back(spring);
    return spring;
}

void World::Step(float timeStep)
{
    if (!simulate) return;

    for (auto spring : m_springs)
    {
        spring->ApplyForce(springStiffnessMultiplier);
    }

    if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);


    for (auto body : m_bodies)
    {
        body->Step(timeStep);
        body->ClearForce();
    }

    // contact solver
    for (int i = 0; i < 5; i++)
    {
        CreateContacts(m_bodies, m_contacts);
        SeparateContacts(m_contacts);
        //ResolveContacts(m_contacts);
        m_contacts.clear();
    }
}

void World::Draw(const Scene& scene)
{
    for (auto spring : m_springs)
    {
        spring->Draw(scene);
    }

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



