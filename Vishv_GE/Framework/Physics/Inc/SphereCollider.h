#ifndef INCLUDED_VISHV_PHYSICS_SHEPRECOLLIDER_H
#define INCLUDED_VISHV_PHYSICS_SHEPRECOLLIDER_H

namespace Vishv::Physics
{
	class SphereCollider
	{
	public:
		int mTag;
		Vishv::Math::Shapes::Sphere mSphere;
		int objectID;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_SHEPRECOLLIDER_H

