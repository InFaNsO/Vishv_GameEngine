#pragma once
#ifndef INCLUDEED_VISVH_PHYSICS_PHYSICSOBJECT_H
#define INCLUDEED_VISVH_PHYSICS_PHYSICSOBJECT_H

namespace Vishv::Physics
{
	class PhysicsObject
	{
	public:
		META_CLASS_DECLARE
		
		void ApplyForce(const Math::Vector3& force);
		virtual void Update(float deltaTime = 0.33f);

	public:
		bool mIsActive = true;
		bool mIsStatic = false;

		Math::Vector3 Velocity;
		Math::Vector3 Acceleration;

		std::unique_ptr<Math::Vector3> Gravity = nullptr;

		float InvMass = 1.0f;
		float Resistance = 1.0f;

		Math::Transform* myTransform;

	protected:
		Math::Vector3 prvVelocity = { 0.0f };
		Math::Vector3 accumilatedForce;

	};
}

#endif // !INCLUDEED_VISVH_PHYSICS_PHYSICSOBJECT_H
