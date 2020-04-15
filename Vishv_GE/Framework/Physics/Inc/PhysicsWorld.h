#ifndef INCLUDED_VISHV_PHYSICS_PHYSICS_WORLD
#define INCLUDED_VISHV_PHYSICS_PHYSICS_WORLD

#include "Octree.h"

namespace Vishv::Physics
{
	class RigidBody;

	class PhysicsWorld
	{
	public:
		void Initialize(int maxObjects = 100000, int maxObjInLeaf = 10);
		//void SetGravity(const Math::Vector3& gravity) { mGravity = gravity; }

		void Register(RigidBody& body);
		void Update(float deltaTime);

		//static Math::Vector3 mGravity;
	private:
		Octree mTree;
	};
}



#endif // !INCLUDED_VISHV_PHYSICS_PHYSICS_WORLD


