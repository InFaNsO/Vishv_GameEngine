#include "Precompiled.h"
#include "AxisAlignedBoundingBox.h"

using namespace Vishv;
using namespace Physics;

META_DERIVED_BEGIN(AABB, Collider)
	META_FIELD_BEGIN
		META_FIELD(min, "Min")
		META_FIELD(max, "Max")
	META_FIELD_END
META_CLASS_END

//Constructors
Vishv::Physics::AABB::AABB(const Math::Vector3& Min, const Math::Vector3& Max, const Math::Vector3& center)
	:min(Min)
	,max(Max)
{
}
Vishv::Physics::AABB::AABB(const Math::Vector3& center, const Math::Vector3& extend)
	:min(Math::Vector3::Invert(extend))
	,max(extend)
{
}
Vishv::Physics::AABB::AABB(const Math::Vector3& extend)
	: min(Math::Vector3::Invert(extend))
	, max(extend) 
{
}

/////////////////////////////////////////////////////////
//Statics
AABB Vishv::Physics::AABB::Generate(const Vishv::Graphics::Mesh& mesh)
{
	VISHVASSERT(mesh.mVertices.size() != 0, "Mesh is empty");

	Math::Vector3 min = mesh.mVertices[0].position;
	Math::Vector3 max = mesh.mVertices[0].position;

	for (auto& vertex : mesh.mVertices)
	{
		min.x = min.x < vertex.position.x ? min.x : vertex.position.x;
		min.y = min.y < vertex.position.y ? min.y : vertex.position.y;
		min.z = min.z < vertex.position.z ? min.z : vertex.position.z;

		max.x = max.x < vertex.position.x ? max.x : vertex.position.x;
		max.y = max.y < vertex.position.y ? max.y : vertex.position.y;
		max.z = max.z < vertex.position.z ? max.z : vertex.position.z;
	}

	return AABB(min, max, {});
}
AABB Vishv::Physics::AABB::FromMinMax(const Math::Vector3& min, const Math::Vector3& max)
{
	return AABB(min, max, {});
}

/////////////////////////////////////////////////////////
//Overrides
Collider::MinMax Vishv::Physics::AABB::GetBounds()
{
	return { { GetMaxX(), GetMaxY(), GetMaxZ() }, { GetMinX(), GetMinY(), GetMinZ() } };
}
Math::Vector3 Vishv::Physics::AABB::ClosestPointFrom(const Math::Vector3& pos)
{
	auto dir = (pos - myTransform->Position()).Normalized();
	return myTransform->Position() + (dir * Extent());
}
Math::Vector3 Vishv::Physics::AABB::ClosestPointOnBoundsFrom(const Math::Vector3& pos)
{
	auto dir = (pos - myTransform->Position()).Normalized();
	return myTransform->Position() + (dir * Extent());
}

/////////////////////////////////////////////////////////
//Functions
void Vishv::Physics::AABB::SetAAABB(const Vishv::Math::Shapes::Cuboid& cuboid)
{
	min = { cuboid.GetLengthX() * -0.5f, cuboid.GetLengthY() * -0.5f, cuboid.GetLengthZ() * -0.5f };
	max = { cuboid.GetLengthX() * 0.5f, cuboid.GetLengthY() * 0.5f, cuboid.GetLengthZ() * 0.5f };
}

bool Vishv::Physics::AABB::IsPointInside(const Math::Vector3& pos)
{
	Math::Vector3 p = pos - myTransform->Position();

	if (p.x > min.x && p.y > min.y && p.z > min.z &&
		p.x < max.x && p.y < max.y && p.z < max.z)
	{
		return true;
	}

	return false;
}

