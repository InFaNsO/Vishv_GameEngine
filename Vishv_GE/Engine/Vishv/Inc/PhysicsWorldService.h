#ifndef INCLUDED_VISHV_PHYSICS_WORLD_SERVICE_H
#define INCLUDED_VISHV_PHYSICS_WORLD_SERVICE_H
#pragma once

#include "Service.h"

namespace Vishv
{
	class GameObject;

	namespace Components
	{
		class Rigidbody;
	}

	class PhysicsSystem : public Service
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Terminate() override;

		void Update() override;
		void Render() override;
		void DebugUI() override;

		void Register(Components::Rigidbody& object);
		void SetGravity(const Math::Vector3& gravity);

	private:
		int mMaxObjectsInWorld = 100000;
		int mMaxObjectsProcessedByThread = 10;

		Math::Vector3 mGravity;
		Physics::PhysicsWorld mWorld;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_WORLD_SERVICE_H


