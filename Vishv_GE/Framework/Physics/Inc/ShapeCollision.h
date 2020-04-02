#ifndef INCLUDED_VISHV_PHYSICS_SHAPES_COLLISION_H
#define INCLUDED_VISHV_PHYSICS_SHAPES_COLLISION_H

#include "AxisAlignedBoundingBox.h"

namespace Vishv::Physics::Collision
{
	struct Ray;
	struct CollisionData
	{
		size_t mIndex;	//used for ID
		Math::Shapes::Base::Shape3D* Shape1;
		Math::Shapes::Base::Shape3D* Shape2;

		bool Collided = false;
		Math::Vector3 PointOfCollisionShape1;
		Math::Vector3 PointOfCollisionShape2;
		float distanceSqr = 1.0f;
	};

	class ColliderCheck
	{
	public:
		//returns collision data
		static CollisionData IsColliding(Math::Shapes::Sphere& sphere, Math::Shapes::Sphere& sphere2);
		static CollisionData IsColliding(Math::Shapes::Sphere& sphere, AABB& aabb);
		static CollisionData IsColliding(AABB& aabb, AABB& aabb2);

		//return bool
		static bool IsCollision(Math::Shapes::Sphere& sphere, Math::Shapes::Sphere& sphere2);
		static bool IsCollision(Math::Shapes::Sphere& sphere, AABB& aabb);
		static bool IsCollision(const AABB& aabb, const AABB& aabb2);

		static bool IsCollision(const Ray& ray, const AABB& aabb, float maxDistance = 0.0f);


	private:
		std::vector<Math::Shapes::Cube*> mCube;
		std::vector<Math::Shapes::Cuboid*> mCuboid;
		std::vector<Math::Shapes::Sphere*> mSpheres;
		std::vector<Math::Shapes::Capsule*> mCapsule;

		std::vector<std::unique_ptr<CollisionData>> mCollisionData;

		static bool isRayBoxDistanceCollision(const Ray& ray, const AABB& aabb, float distance);
	};
	
}


#endif // !INCLUDED_VISHV_PHYSICS_SHAPES_COLLISION_H



