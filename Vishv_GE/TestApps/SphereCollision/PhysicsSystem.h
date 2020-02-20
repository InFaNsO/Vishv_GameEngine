#pragma once
#include <Math/Inc/VishvMath.h>

struct PhysicsSystem
{
	Vishv::Math::Vector3 mPosition, mVelocity, mAcceleration, mRotationAxis{ 0.0f, 0.0f, 1.0f };
	float mRotationSpeed;
	float mMass{ 1.0f };

	float mRotation{ 0.0f }; // rotation angle arond orientation axis to orient the object in WCS.
};
