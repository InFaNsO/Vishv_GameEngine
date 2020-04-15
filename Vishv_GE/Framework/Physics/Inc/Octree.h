#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_OCTREE_H
#define INCLUDED_VISHV_PHYSICS_OCTREE_H

#include "AxisAlignedBoundingBox.h"
#include "AABBInt.h"

namespace Vishv::Physics
{
	class RigidBody;

	class Octree
	{
	public:
		class Node
		{
		public:
			Node* parent = nullptr;
			std::array<std::unique_ptr<Node>, 8> children;
			int level = 1;
			IntData::Vector3Int center;
			bool isLeaf = true;
			std::list<RigidBody*> objects;

			//AABB bounds;		//will calculate it on the fly since it is simple to make it and less cache misses
		};

	public:
		Octree() = default;
		void Initialzie(const Math::Vector3& center, const Math::Vector3& half, int maxObjectsInleaf = 10, int maxObjects = 10000);
		bool Add(RigidBody& object);
		void Update();

		
		std::list<Node*>& GetChunks() { return mLeafs; };
		const std::list<Node*>& GetChunks() const { return mLeafs; };

	private:
		void AddRecursive(Node* node, RigidBody& data, IntData::AABBInt& bounds);
		
		void SplitLeaf(Node* node, IntData::AABBInt& bounds);
		void RemoveStaleLeaf();
		void AddChildrenLeafs(Node* node);
	
	private:

		std::unique_ptr<Node> mRoot;
		std::list<Node*> mLeafs;

		int mMaxObjsInLeaf = 10;
		int mMaxObj = 100;

		int totalObjects = 0;

		IntData::AABBInt bounds;

		uint32_t LenX = 0;
		uint32_t LenY = 0;
		uint32_t LenZ = 0;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_OCTREE_H
