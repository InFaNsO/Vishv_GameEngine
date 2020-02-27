#include "Precompiled.h"
#include "PhysicsWorld.h"

#include "ShapeCollision.h"

int Vishv::Physics::PhysicsWorld::Register(SphereCollider & collider)
{
	mSphereColliders.emplace_back(&collider);
	return static_cast<int>(mSphereColliders.size()) - 1;
}

std::optional<std::vector<Vishv::Physics::SphereCollider*>> Vishv::Physics::PhysicsWorld::IsColliding(int tag, SphereCollider& other)
{
	std::vector<SphereCollider*> collisions;

	collisions.reserve(mSphereColliders.size());

	for (SphereCollider* collider : mSphereColliders)
	{
		if (collider->mTag != tag && tag != -1)
			continue;

		if (Collision::Collider::IsCollision(collider->mSphere, other.mSphere))
			collisions.emplace_back(collider);
	}

	return std::move(collisions);
}

void Vishv::Physics::PhysicsWorld::Update(float deltaTime)
{
	//move objects and resolve collisions
}

