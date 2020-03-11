#include"Precompiled.h"
#include "QuadTree.h"

namespace
{
	Vishv::Physics::Collision::AABB GetBL(Vishv::Physics::Collision::AABB& aabb)
	{

	}
}

void Vishv::QuadTree::Initialize(const Vishv::Graphics::Mesh & mesh, size_t levels)
{
	VISHVASSERT(levels > 0, "No levels to make wrong value");

	mMesh = &mesh;
	
	//generate nodes
	Physics::Collision::AABB bound = Physics::Collision::AABB::Generate(mesh);
	GenerateNodeRecursive(mRoot, bound, levels);

	//assign triangles
	auto& vertices = mesh.mVertices;
	auto& indices = mesh.mIndices;
	for (size_t i = 0; i < indices.size(); ++i)
	{
		auto& a = vertices[i + 0].position;
		auto& b = vertices[i + 1].position;
		auto& c = vertices[i + 2].position;

		const float minX = Math::Min(Math::Min(a.x, b.x), c.x);
		const float minY = Math::Min(Math::Min(a.y, b.y), c.y);
		const float minZ = Math::Min(Math::Min(a.z, b.z), c.z);

		const float maxX = Math::Max(Math::Max(a.x, b.x), c.x);
		const float maxY = Math::Max(Math::Max(a.y, b.y), c.y);
		const float maxZ = Math::Max(Math::Max(a.z, b.z), c.z);

		auto aabb = Physics::Collision::AABB::FromMinMax({ minX, minY, minZ }, { maxX, maxY, maxZ });

		Visitor visitor = [a, b, c, aabb, i](Node* node)
		{
			if (!Physics::Collision::Collider::IsCollision(aabb, node->aabb))
				return false;

			if (!node->isLeaf)
				return true;

			//check triangle and aabb intersect
			if(true)
				node->indecies.push_back(i);
			return false;
		};

		Visit(visitor);
	}

}

void Vishv::QuadTree::Visit(Visitor & visitor)
{
	VisitRecursively(mRoot.get(), visitor);
}

bool Vishv::QuadTree::Intersect(const Physics::Ray & ray, float distance)
{
	if (mRoot == nullptr)
		return true;

	return IntrersectRecursively(mRoot.get(), ray, distance);
}

bool Vishv::QuadTree::IntrersectRecursively(Node * node, const Physics::Ray & ray, float distance)
{
	if (!Physics::Collision::Collider::IsCollision(ray, node->aabb, distance))
		return false;

	float dis;

	if (!node->isLeaf)
	{
		return IntrersectRecursively(node->children[0].get(), ray, dis) ||
			IntrersectRecursively(node->children[1].get(), ray, dis) ||
			IntrersectRecursively(node->children[2].get(), ray, dis) ||
			IntrersectRecursively(node->children[3].get(), ray, dis);
	}

	bool intersect = false;
	//check intersection with children and return if true

	return false;
}

void Vishv::QuadTree::VisitRecursively(Node * node, Visitor & visitor)
{
	if (visitor(node) && !node->isLeaf)
	{
		for (int i = 0; i < 4; ++i)
		{
			VisitRecursively(node->children[i].get(), visitor);
		}
	}
}

void Vishv::QuadTree::GenerateNodeRecursive(std::unique_ptr<Node>& node, Physics::Collision::AABB & aabb, size_t levels)
{
	node = std::make_unique<Node>();
	node->aabb = aabb;

	if (--levels == 0)
		node->isLeaf = true;
	else
	{
		auto extent = aabb.Extent() * 0.5f;
		auto center = aabb.GetPosition();

		Physics::Collision::AABB bl({ center.x - extent.x, center.y, center.z - extent.z }, extent);
		Physics::Collision::AABB br({ center.x + extent.x, center.y, center.z - extent.z }, extent);
		Physics::Collision::AABB tl({ center.x - extent.x, center.y, center.z + extent.z }, extent);
		Physics::Collision::AABB tr({ center.x + extent.x, center.y, center.z + extent.z }, extent);

		GenerateNodeRecursive(node->children[(int)Quadrant::BL], bl, levels);
		GenerateNodeRecursive(node->children[(int)Quadrant::BR], br, levels);
		GenerateNodeRecursive(node->children[(int)Quadrant::TL], tl, levels);
		GenerateNodeRecursive(node->children[(int)Quadrant::TR], tr, levels);
	}
}

