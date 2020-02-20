#ifndef INCLUDED_VISHV_PHYSICS_PHYSICS_WORLD
#define INCLUDED_VISHV_PHYSICS_PHYSICS_WORLD

#include "SphereCollider.h"

namespace Vishv::Physics
{
	class PhysicsWorld
	{
	public:
		int Register(SphereCollider& collider);
		std::optional<std::vector<SphereCollider*>> IsColliding(int tag, SphereCollider& other);

		void Update(float deltaTime);

	private:
		std::vector<SphereCollider*> mSphereColliders;
	};
}



#endif // !INCLUDED_VISHV_PHYSICS_PHYSICS_WORLD


