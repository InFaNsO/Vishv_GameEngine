#ifndef INCLUDED_VISH_PHYSICS_BOUNDINGVOLUMEHIRACHY_H
#define INCLUDED_VISH_PHYSICS_BOUNDINGVOLUMEHIRACHY_H

namespace Vishv::Physics {
	
class RigidBody;

using RigidBodyID = size_t;
using ParticleID = size_t;

using Contact = std::pair<RigidBodyID, RigidBodyID>;
using PotentialContact = std::pair<RigidBodyID, RigidBodyID>;



class BoundingVolumeHirarchy
{
private:
	struct BVHNode
	{
		std::shared_ptr<BVHNode> mParent = nullptr;
		std::array<std::shared_ptr<BVHNode>, 2> mChildren = {nullptr};
		RigidBodyID mObject = 0;
		
		std::unique_ptr<Math::Shapes::Cuboid> mVolumeCuboid = nullptr;
		std::unique_ptr<Math::Shapes::Cube> mVolumeCube = nullptr;
		std::unique_ptr<Math::Shapes::Sphere> mVolumeSphere = nullptr;

		bool IsLeaf() { return mObject > 0; }

		int GetPotentialContacts(std::vector<PotentialContact>& contacts, int limit);
		int GetPotentialContactsWith(std::shared_ptr<BVHNode> other, std::vector<PotentialContact>& contacts, int limit);

		void Insert(Vishv::Physics::RigidBodyID body, Math::Shapes::Sphere& sphere);
		void Insert(Vishv::Physics::RigidBodyID body, Math::Shapes::Cube& cube);
		void Insert(Vishv::Physics::RigidBodyID body, Math::Shapes::Cuboid& cuboid);
		
		void Remove();

		BVHNode() = default;
		~BVHNode() { Remove(); }
	};

public:
	enum class VolumeType
	{
		Sphere,
		Cube,
		Cuboid
	};

	void Initialize(VolumeType type = VolumeType::Sphere);
	void Insert(RigidBodyID body, Math::Shapes::Sphere& sphere) { mHead->Insert(body, sphere); }
	void Insert(RigidBodyID body, Math::Shapes::Cube& cube) { mHead->Insert(body, cube); }
	void Insert(RigidBodyID body, Math::Shapes::Cuboid& cuboid) { mHead->Insert(body, cuboid); }

	int GetContacts(std::vector<PotentialContact>& contacts, int limit = 100) { mHead->GetPotentialContacts(contacts, limit); }

	BVHNode* GetHead() { return mHead.get(); }

private:
	std::unique_ptr<BVHNode> mHead;
	VolumeType mVolumeType;
};



}

#endif // !INCLUDED_VISH_PHYSICS_BOUNDINGVOLUMEHIRACHY_H
