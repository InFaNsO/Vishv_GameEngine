#ifndef INCLUDED_VISHV_PHYSICS_RAY_CAST
#define INCLUDED_VISHV_PHYSICS_RAY_CAST

namespace Vishv::Physics
{
	struct Ray
	{
		Math::Vector3 origin;
		Math::Vector3 direction;
	};

	class Raycast
	{
	public:
		static bool IsColliding(Ray& ray, float length, Math::Shapes::Cuboid& cuboid, Math::Vector3& collisionPoint);
		static bool IsColliding(Ray& ray, float length, Math::Shapes::Sphere& sphere, Math::Vector3& collisionPoint);
	};
}


#endif // !INCLUDED_VISHV_PHYSICS_RAY_CAST

