#include "Precompiled.h"
#include "OrientedBoundingBox.h"

using namespace Vishv;
using namespace Vishv::Physics;

META_DERIVED_BEGIN(OBB, Collider)
	META_FIELD_BEGIN
		META_FIELD(mExtent, "Extent")
		META_FIELD(mOrientation, "Orientation")
	META_FIELD_END
META_CLASS_END

Collider::MinMax Vishv::Physics::OBB::GetBounds()
{
	Math::Vector3 min = - mExtent;
	Math::Vector3 max =   mExtent;

	min = min * mOrientation;
	max = max * mOrientation;

	return {min, max};
}

Math::Vector3 Vishv::Physics::OBB::ClosestPointFrom(const Math::Vector3& pos)
{
	auto dir = (pos - myTransform->Position()).Normalized();
	auto orExt = mExtent * mOrientation;

	return (dir * orExt) + myTransform->Position();

	return Math::Vector3();
}

Math::Vector3 Vishv::Physics::OBB::ClosestPointOnBoundsFrom(const Math::Vector3& pos)
{
	auto dir = (pos - myTransform->Position()).Normalized();

	Math::Vector3 min(std::numeric_limits<float>::max());
	Math::Vector3 max(std::numeric_limits<float>::min());

	for (auto p : Points())
	{
		if (p.x < min.x)
			min.x = p.x;
		else if (p.x > max.x)
			max.x = p.x;

		if (p.y < min.y)
			min.y = p.y;
		else if (p.y > max.y)
			max.y = p.y;

		if (p.z < min.z)
			min.z = p.z;
		else if (p.z > max.z)
			max.z = p.z;
	}

	Math::Vector3 ext(max.x - min.x, max.y - min.y, max.z - min.z);

	return myTransform->Position() + (dir * ext);
}

std::vector<Math::Vector3>& Vishv::Physics::OBB::Points()
{
	if (mPoints.size() > 0 && !mIsActive)
		return mPoints;

	auto center = myTransform->Position();
	auto orExt = mExtent * mOrientation;
	
	//BBL BBR BTL BTR FBL FBR FTL FTR

	mPoints.clear();
	mPoints.emplace_back(center - orExt);						//BBL
	mPoints.emplace_back(Math::Vector3(	center.x + orExt.x,
										center.y - orExt.y,
										center.z - orExt.z ));	//BBR
	mPoints.emplace_back(Math::Vector3(	center.x - orExt.x,
										center.y + orExt.y,
										center.z - orExt.z));	//BTL
	mPoints.emplace_back(Math::Vector3(center.x + orExt.x,
										center.y + orExt.y,
										center.z - orExt.z));	//BTR
	mPoints.emplace_back(Math::Vector3(center.x - orExt.x,
										center.y - orExt.y,
										center.z + orExt.z));	//FBL
	mPoints.emplace_back(Math::Vector3(center.x + orExt.x,
										center.y - orExt.y,
										center.z + orExt.z));	//FBR
	mPoints.emplace_back(Math::Vector3(center.x - orExt.x,
										center.y + orExt.y,
										center.z + orExt.z));	//FTL

	mPoints.emplace_back((center + orExt));						//FTR

	return mPoints;

}