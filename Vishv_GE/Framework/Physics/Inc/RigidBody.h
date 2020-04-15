#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_RIGIDBODY_H
#define INCLUDED_VISHV_PHYSICS_RIGIDBODY_H

#include "PhysicsObject.h"
#include "Octree.h"

namespace Vishv::Physics
{
	class PhysicsWorld;
	class Collider;

	class RigidBody : public PhysicsObject
	{
	public:
		META_CLASS_DECLARE

		void ApplyForceOnPoint(const Math::Vector3& force, const Math::Vector3& point);
		void Update(float deltaTime = 0.33f) override;

		void HandleCollision(RigidBody* other);

	public:
		friend class PhysicsWorld;
		friend class Octree;


		Math::Quaternion* Orientation;
		Math::Vector3 AngularVelocity;
		Math::Vector3 AngularAcceleration;

		Collider* myCollider;

		float AngularResistance = 1.0f;

	private:
		Math::Vector3 prvAngleVel;
		Math::Vector3 accumilatedTorque;
		
		Octree::Node* myNode;
	};
}


#endif // !INCLUDED_VISHV_PHYSICS_RIGIDBODY_H


