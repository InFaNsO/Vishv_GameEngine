#ifndef INCLUDED_VISHV_COMPONENTS_RIGIDBODY_COMPONENT_H
#define INCLUDED_VISHV_COMPONENTS_RIGIDBODY_COMPONENT_H
#pragma once

#include "Component.h"

namespace Vishv
{
	class PhysicsSystem;
}

namespace Vishv::Components
{
	class Rigidbody : public Component
	{
	public:
		META_CLASS_DECLARE;

		void Initialize()override;
		void Update(float deltaTime) override;
		void DebugUI() override;
		void SimpleDraw() override;

		void SetCollider(Physics::Collider* coll);

	private:
		friend class PhysicsSystem;

		Physics::RigidBody mRigidBody;
	};
}


#endif // !INCLUDED_VISHV_COMPONENTS_RIGIDBODY_COMPONENT_H



