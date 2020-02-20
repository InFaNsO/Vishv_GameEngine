#ifndef INCLUDED_VISHV_PHYSICS_BINARYSPACEPARTITIONING_H
#define INCLUDED_VISHV_PHYSICS_BINARYSPACEPARTITIONING_H

namespace Vishv::Physics {

	enum class BSPChildType
	{
		Node,
		Object
	};
	struct BSPChild
	{
		BSPChildType mType = BSPChildType::Node;
		std::shared_ptr<BSPChild> mChild = nullptr;
		std::vector<RigidBodyID> mObjects;				//this could be BoundingVolumeHirarchy and store more varried objects
	};

	struct BSPNode
	{
		Math::Shapes::Plane mPlane;
		BSPChild mFront;
		BSPChild mBack;
	};

class BinarySpacePartitioning
{
private:
	
};
}

#endif // !INCLUDED_VISHV_PHYSICS_BINARYSPACEPARTITIONING_H
