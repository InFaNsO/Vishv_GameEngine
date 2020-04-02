#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_RIGIDBODY_H
#define INCLUDED_VISHV_PHYSICS_RIGIDBODY_H

namespace Vishv::Physics
{
	class Collider;

	class RigidBody
	{
	public:

	public:
		bool mIsActive = true;
		bool mIsStatic = false;
		float mInvMass = 1.0f;

		Math::Vector3 mVelocity;
		Math::Vector3 mAcceleration;

		Math::Transform* myTransform;
		Collider* myCollider;
	};
}


#endif // !INCLUDED_VISHV_PHYSICS_RIGIDBODY_H


