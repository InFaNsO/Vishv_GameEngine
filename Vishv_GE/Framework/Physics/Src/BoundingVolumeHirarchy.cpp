#include "Precompiled.h"
#include "BoundingVolumeHirarchy.h"
#include "RigidBody.h"
#include "World.h"
/*
using namespace Vishv; 
using namespace Vishv::Physics;

int BoundingVolumeHirarchy::BVHNode::GetPotentialContacts(std::vector<PotentialContact>& contacts, int limit)
{
	if (IsLeaf() || limit == 0)
		return 0;

	return mChildren[0]->GetPotentialContactsWith(mChildren[1], contacts, limit);
}

int Vishv::Physics::BoundingVolumeHirarchy::BVHNode::GetPotentialContactsWith(std::shared_ptr<BVHNode> other, std::vector<PotentialContact>& contacts, int limit)
{
	VolumeType type;

	if (mVolumeCube)
	{
		if (limit == 0 || Math::Shapes::IsColliding(*mVolumeCube.get(), *other->mVolumeCube.get())) return 0;
		type = VolumeType::Cube;
	}
	if (mVolumeCuboid)
	{
		if (limit == 0 || Math::Shapes::IsColliding(*mVolumeCuboid.get(), *other->mVolumeCuboid.get())) return 0;
		type = VolumeType::Cuboid;
	}
	if (mVolumeSphere)
	{
		if (limit == 0 || Math::Shapes::IsColliding(*mVolumeSphere.get(), *other->mVolumeSphere.get())) return 0;
		type = VolumeType::Sphere;
	}

	if (IsLeaf() && other.get()->IsLeaf())
	{
		contacts.push_back(std::make_pair(mObject, other.get()->mObject));
		return 1;
	}

	bool doIt = false;

	switch (type)
	{
	case VolumeType::Sphere:
		if (other->IsLeaf() ||
			(!IsLeaf() && mVolumeSphere->GetVolume() >= other->mVolumeSphere->GetVolume()))
		{
			doIt = true;
		}
		break;
	case VolumeType::Cube:
		if (other->IsLeaf() ||
			(!IsLeaf() && mVolumeCube->GetVolume() >= other->mVolumeCube->GetVolume()))
		{
			doIt = true;
		}
		break;
	case VolumeType::Cuboid:
		if (other->IsLeaf() ||
			(!IsLeaf() && mVolumeCuboid->GetVolume() >= other->mVolumeCuboid->GetVolume()))
		{
			doIt = true;
		}
		break;
	default:
		return 0;
		break;
	}

	if (doIt)
	{
		int count = mChildren[0]->GetPotentialContactsWith(other, contacts, limit);
		if (limit > count)
			return count + mChildren[1]->GetPotentialContactsWith(other, contacts, limit - count);
		else
		{
			return count;
		}
	}
	else
	{
		int count = GetPotentialContactsWith(other->mChildren[0], contacts, limit);
		if (limit > count)
			return count + GetPotentialContactsWith(other->mChildren[1], contacts, limit - count);
		else
		{
			return count;
		}
	}
}

void Vishv::Physics::BoundingVolumeHirarchy::BVHNode::Insert(Vishv::Physics::RigidBodyID body, Math::Shapes::Sphere & sphere)
{
	VolumeType type = VolumeType::Sphere;

	if (IsLeaf())
	{
		mChildren[0]->mParent = mParent;
		mChildren[0]->mObject = mObject;
		mObject = 0;
		mChildren[0]->mVolumeSphere = std::move(mVolumeSphere);

		mChildren[1]->mParent = mParent;
		mChildren[1]->mObject = body;
		mChildren[1]->mVolumeSphere = std::make_unique<Math::Shapes::Sphere>(sphere);

		mVolumeSphere.release();
		Math::Shapes::Sphere s(*mChildren[0]->mVolumeSphere.get(), *mChildren[1]->mVolumeSphere.get());
		mVolumeSphere = std::make_unique<Math::Shapes::Sphere>(s);
		return;
	}
	
	Math::Shapes::Sphere s1(*mChildren[0]->mVolumeSphere.get(), sphere);
	Math::Shapes::Sphere s2(*mChildren[1]->mVolumeSphere.get(), sphere);

	if (s1.GetVolume() - mChildren[0]->mVolumeSphere->GetVolume() <
		s2.GetVolume() - mChildren[1]->mVolumeSphere->GetVolume())
	{
		mChildren[0]->Insert(body, sphere);
	}
	else
	{
		mChildren[1]->Insert(body, sphere);
	}
}

void Vishv::Physics::BoundingVolumeHirarchy::BVHNode::Insert(Vishv::Physics::RigidBodyID body, Math::Shapes::Cube & cube)
{
	if (IsLeaf())
	{
		mChildren[0]->mParent = mParent;
		mChildren[0]->mObject = mObject;
		mObject = 0;
		mChildren[0]->mVolumeCube = std::move(mVolumeCube);

		mChildren[1]->mParent = mParent;
		mChildren[1]->mObject = body;
		mChildren[1]->mVolumeCube = std::make_unique<Math::Shapes::Cube>(cube);

		mVolumeCube.release();
		Math::Shapes::Cube s(*mChildren[0]->mVolumeCube.get(), *mChildren[1]->mVolumeCube.get());
		mVolumeCube = std::make_unique<Math::Shapes::Cube>(s);
		return;
	}

	Math::Shapes::Cube s1(*mChildren[0]->mVolumeCube.get(), cube);
	Math::Shapes::Cube s2(*mChildren[1]->mVolumeCube.get(), cube);

	if (s1.GetVolume() - mChildren[0]->mVolumeCube->GetVolume() <
		s2.GetVolume() - mChildren[1]->mVolumeCube->GetVolume())
	{
		mChildren[0]->Insert(body, cube);
	}
	else
	{
		mChildren[1]->Insert(body, cube);
	}
}

void Vishv::Physics::BoundingVolumeHirarchy::BVHNode::Insert(Vishv::Physics::RigidBodyID body, Math::Shapes::Cuboid & cuboid)
{
	if (IsLeaf())
	{
		mChildren[0]->mParent = mParent;
		mChildren[0]->mObject = mObject;
		mObject = 0;
		mChildren[0]->mVolumeCuboid = std::move(mVolumeCuboid);

		mChildren[1]->mParent = mParent;
		mChildren[1]->mObject = body;
		mChildren[1]->mVolumeCuboid = std::make_unique<Math::Shapes::Cuboid>(cuboid);

		mVolumeCuboid.release();
		Math::Shapes::Cuboid s(*mChildren[0]->mVolumeCuboid.get(), *mChildren[1]->mVolumeCuboid.get());
		mVolumeCuboid = std::make_unique<Math::Shapes::Cuboid>(s);
		return;
	}

	Math::Shapes::Cuboid s1(*mChildren[0]->mVolumeCuboid.get(), cuboid);
	Math::Shapes::Cuboid s2(*mChildren[1]->mVolumeCuboid.get(), cuboid);

	if (s1.GetVolume() - mChildren[0]->mVolumeCuboid->GetVolume() <
		s2.GetVolume() - mChildren[1]->mVolumeCuboid->GetVolume())
	{
		mChildren[0]->Insert(body, cuboid);
	}
	else
	{
		mChildren[1]->Insert(body, cuboid);
	}
}

void Vishv::Physics::BoundingVolumeHirarchy::BVHNode::Remove()
{
	if (mParent)
	{
		std::shared_ptr<BVHNode> sibling;
		if (mParent->mChildren[0].get() == this)
		{
			sibling = mParent->mChildren[1];
		}
		else
			sibling = mParent->mChildren[0];

		if (sibling == nullptr)
		{
			mParent->mChildren[0] = nullptr;
			mParent->mChildren[1] = nullptr;
			return;
		}

		int parentNum = -1;
		if (mParent->mParent->mChildren[0].get() == mParent.get())
			mParent->mParent->mChildren[1] = sibling;
		else
			mParent->mParent->mChildren[0] = sibling;
		sibling->mParent = mParent->mParent;


		if (mVolumeCube)
		{
			sibling->mParent->mVolumeCube = std::make_unique<Math::Shapes::Cube>();
			Math::Shapes::Cube c(*sibling->mVolumeCube.get(), *sibling->mParent->mVolumeCube.get());

			*sibling->mParent->mVolumeCube = c;
		}
		if (mVolumeCuboid)
		{
			sibling->mParent->mVolumeCuboid = std::make_unique<Math::Shapes::Cuboid>();
			Math::Shapes::Cuboid c(*sibling->mVolumeCuboid.get(), *sibling->mParent->mVolumeCuboid.get());

			*sibling->mParent->mVolumeCuboid = c;
		}
		if (mVolumeCube)
		{
			sibling->mParent->mVolumeSphere = std::make_unique<Math::Shapes::Sphere>();
			Math::Shapes::Sphere s(*sibling->mVolumeSphere.get(), *sibling->mParent->mVolumeSphere.get());

			*sibling->mParent->mVolumeSphere = s;
		}
	}

	if (mChildren[0])
		mChildren[0].reset();
	if (mChildren[1])
		mChildren[1].reset();
}

void Vishv::Physics::BoundingVolumeHirarchy::Initialize(BoundingVolumeHirarchy::VolumeType type)
{
	mHead = std::make_unique<BVHNode>();
	mVolumeType = type;
}
*/

