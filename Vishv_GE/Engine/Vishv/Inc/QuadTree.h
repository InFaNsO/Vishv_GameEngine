#pragma once
#ifndef INCLUDED_VISHV_QUAD_TREE_H
#define INCLUDED_VISHV_QUAD_TREE_H

namespace Vishv
{
	class QuadTree
	{
	public:
		struct Node
		{
			std::array<std::unique_ptr<Node>, 4> children;
			std::vector<size_t> indecies;
			Physics::AABB aabb;
			bool isLeaf = false;

		};

		using Visitor = std::function<bool(Node*)>;

	public:
		QuadTree() = default;

		void Initialize(const Vishv::Graphics::Mesh& mesh, size_t levels);
		void Visit(Visitor& visitor);

		bool Intersect(const Physics::Ray& ray, float distance);

	private:
		enum class Quadrant {BL, BR, TL, TR};

		void GenerateNodeRecursive(std::unique_ptr<Node>& node, Physics::Collision::AABB&, size_t levels);
		void VisitRecursively(Node* node, Visitor& visitor);
		bool IntrersectRecursively(Node* node, const Physics::Ray& ray, float distance);

		const Vishv::Graphics::Mesh* mMesh = nullptr;
		std::unique_ptr<Node> mRoot = nullptr;

	};
}


#endif // !INCLUDED_VISHV_QUAD_TREE_H



