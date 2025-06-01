#include "collision.h"
#include "math_utils.h"
#include "raymath.h"

void CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyB = bodies[j];
			if (bodyA->type != Body::Type::Dynamic && bodyB->type != Body::Type::Dynamic) continue; //<both bodies are not dynamic>

			if (Intersects(bodyA, bodyB))
			{
				Contact contact;
				contact.bodyA = bodyA;
				contact.bodyB = bodyB;

				Vector2 direction = Vector2Subtract(bodyB->position,bodyA->position); //<direction vector from bodyB to bodyA>
				float distanceSqr = Vector2LengthSqr(direction); //<get Vector2 Length Squared of direction>
				if (distanceSqr <= EPSILON)
				{
					direction = Vector2{ randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
					distanceSqr = Vector2LengthSqr(direction);
				}

				float distance = sqrtf(distanceSqr); //<get distance from squared distance>
				float radius = bodyA->size + bodyB->size; //<add size of bodyA and bodyB>
				contact.depth = ((bodyA->size * 0.5f) + (bodyB->size * 0.5f)) - distance; // <calculate penetration depth, see note above> //depth = (radiusA + radiusB) - distance
				contact.normal = Vector2Normalize(direction); //<normalize direction, can use normalize function or direction / distance>
				contact.restitution = (bodyA->restitution + bodyB->restitution) * 0.5f; //<get average restitution of both bodies> // *0.5 == /2

				contacts.push_back(contact);
			}
		}
	}
}
void SeparateContacts(contacts_t& contacts)
{
	for (auto contact : contacts)
	{
		float totalInverseMass = contact.bodyA->invMass + contact.bodyB->invMass; //<add inverse mass of both contact bodies>
		Vector2 separation = contact.normal * (contact.depth / totalInverseMass);
		contact.bodyA->position = contact.bodyA->position + (separation * contact.bodyA->invMass); //<contact bodyA position + (separation * contact bodyA inverse mass)>
		contact.bodyB->position = contact.bodyB->position - (separation * contact.bodyB->invMass); //<contact bodyB position - (separation * contact bodyB inverse mass)>
	}
}

bool Intersects(Body* bodyA, Body* bodyB)
{
	float distance = Vector2Distance(bodyA->position,bodyB->position); //<get distance between bodyA and bodyB, use Vector2Distance>
	float radius = bodyA->size + bodyB->size; //<add size of bodyA and BodyB>

	return (distance <= radius);
}