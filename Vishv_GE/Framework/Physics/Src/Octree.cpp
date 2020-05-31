#include "Precompiled.h"
#include "Octree.h"
#include "RigidBody.h"

using namespace Vishv;
using namespace Physics;


namespace
{
	enum class Quadrant { BBL, BBR, BTL, BTR, FBL, FBR, FTL, FTR };

	IntData::AABBInt Bounds(Quadrant q, IntData::AABBInt& bounds)
	{
		IntData::AABBInt box;

		IntData::Vector3Int half;
		IntData::Vector3Int c = bounds.center;

		half.x = (bounds.max.x - bounds.min.x) >> 1;
		half.y = (bounds.max.y - bounds.min.y) >> 1;
		half.z = (bounds.max.z - bounds.min.z) >> 1;


		switch (q)
		{
		case Quadrant::BBL:
			c -= half;
			break;
		case Quadrant::BBR:
			c.z -= half.z;
			c.y -= half.y;
			c.x += half.x;
			break;
		case Quadrant::BTL:
			c.z -= half.z;
			c.y += half.y;
			c.x -= half.x;
			break;
		case Quadrant::BTR:
			c.z -= half.z;
			c.y += half.y;
			c.x += half.x;
			break;
		case Quadrant::FBL:
			c.z += half.z;
			c.y -= half.y;
			c.x -= half.x;
			break;
		case Quadrant::FBR:
			c.z += half.z;
			c.y -= half.y;
			c.x += half.x;
			break;
		case Quadrant::FTL:
			c.z += half.z;
			c.y += half.y;
			c.x -= half.x;
			break;
		case Quadrant::FTR:
			c += half;
			break;
		}

		box.Set(c, half);
		return box;
	}

}

void Vishv::Physics::Octree::Initialzie(const Math::Vector3& center, const Math::Vector3& half, int maxObjectsInleaf, int maxObjects)
{
	mMaxObj = maxObjects;
	mMaxObjsInLeaf = maxObjectsInleaf;

	mRoot = std::make_unique<Node>();

	mLeafs.emplace_back(mRoot.get());

	bounds.Set({ static_cast<int>(center.x), static_cast<int>(center.y), static_cast<int>(center.z) }, { static_cast<int>(half.x), static_cast<int>(half.y), static_cast<int>(half.z) });

	LenX = bounds.max.x - bounds.min.x;
	LenY = bounds.max.y - bounds.min.y;
	LenZ = bounds.max.z - bounds.min.z;
}

bool Vishv::Physics::Octree::Add(RigidBody& object)
{
	if (totalObjects < mMaxObj)
	{
		AddRecursive(mRoot.get(), object, bounds);
		++totalObjects;
		return true;
	}
	return false;
}

void Vishv::Physics::Octree::AddRecursive(Node* node, RigidBody& data, IntData::AABBInt& bounds)
{
	//check collisions 
	//and insert in correct leaf

	if (node->isLeaf)
	{
		//if leaf is full
		if (node->objects.size() >= static_cast<size_t>(mMaxObjsInLeaf))
		{
			SplitLeaf(node, bounds);
			AddRecursive(node, data, bounds);
			return;
		}

		//add data
		node->objects.emplace_back(&data);
		data.myNode = node;

		return;
	}

	for (int i = 0; i < 8; ++i)
	{
		auto bound = Bounds((Quadrant)i, bounds);

		int x = static_cast<int>(data.myTransform->Position().x) - bound.center.x;
		int y = static_cast<int>(data.myTransform->Position().y) - bound.center.y;
		int z = static_cast<int>(data.myTransform->Position().z) - bound.center.z;

		if (x > bound.min.x && y > bound.min.y&& z > bound.min.z&&
			x < bound.max.x && y < bound.max.y && z < bound.max.z)
		{
			//it is in this child
			AddRecursive(node->children[i].get(), data, bound);
			return;
		}
	}

	//if it reaches here then the object was out of bounds
}

void Vishv::Physics::Octree::SplitLeaf(Node* node, IntData::AABBInt& bounds)
{
	node->isLeaf = false;

	for (int i = 0; i < 8; ++i)
	{
		node->children[i] = std::make_unique<Node>();
		node->children[i]->parent = node;
		node->children[i]->level = node->level + 1;
		node->children[i]->center = Bounds((Quadrant)i, bounds).center;
	}

	for (auto data : node->objects)
	{
		AddRecursive(node, *data, bounds);
	}

	node->objects.clear();
}

void Vishv::Physics::Octree::RemoveStaleLeaf()
{
	for (auto it = mLeafs.begin(); it != mLeafs.end();)
	{
		auto n = it._Ptr->_Myval;

		if (!n->isLeaf)
		{
			AddChildrenLeafs(n);
			it = mLeafs.erase(it);
			continue;
		}
		++it;
	}
}

void Vishv::Physics::Octree::AddChildrenLeafs(Node* node)
{
	if (node->isLeaf)
	{
		mLeafs.emplace_back(node);
		return;
	}
	else
	{
		for (int i = 0; i < 8; ++i)
		{
			AddChildrenLeafs(node->children[i].get());
		}
	}
}

void Vishv::Physics::Octree::Update()
{
	//check all the objects position and update their leafs
	for (auto it : mLeafs)
	{
		for (auto objIt = it->objects.begin(); objIt != it->objects.end();)
		{
			auto obj = objIt._Ptr->_Myval;

			if (obj->mIsStatic || !obj->mIsActive)
				continue;

			uint32_t x = static_cast<uint32_t>(static_cast<int>(Vishv::Math::Abs(obj->myTransform->Position().x)) - it->center.x);
			uint32_t y = static_cast<uint32_t>(static_cast<int>(Vishv::Math::Abs(obj->myTransform->Position().y)) - it->center.y);
			uint32_t z = static_cast<uint32_t>(static_cast<int>(Vishv::Math::Abs(obj->myTransform->Position().z)) - it->center.z);

			if (x >= (LenX >> it->level) ||
				y >= (LenY >> it->level) ||
				z >= (LenX >> it->level))
			{
				auto node = it->parent->parent;
				IntData::AABBInt b;
				b.Set(node->center, { static_cast<int>(LenX) >> node->level , static_cast<int>(LenY) >> node->level, static_cast<int>(LenZ) >> node->level });
				AddRecursive(it->parent->parent, *obj, b);

				objIt = it->objects.erase(objIt);
				continue;
			}
			objIt++;
		}
	}
}


