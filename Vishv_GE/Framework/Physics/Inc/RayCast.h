#ifndef INCLUDED_VISHV_PHYSICS_RAY_CAST
#define INCLUDED_VISHV_PHYSICS_RAY_CAST

#include "Ray.h"

namespace Vishv::Physics
{
	class Raycast
	{
	public:
		static bool IsColliding(Ray& ray, float length, Math::Shapes::Cuboid& cuboid, Math::Vector3& collisionPoint);
		static bool IsColliding(Ray& ray, float length, Math::Shapes::Sphere& sphere, Math::Vector3& collisionPoint);
	};
}


#endif // !INCLUDED_VISHV_PHYSICS_RAY_CAST

