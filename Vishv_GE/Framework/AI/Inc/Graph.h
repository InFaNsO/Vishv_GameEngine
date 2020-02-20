#ifndef INCLUDED_VISHV_AI_GRAPH_H
#define INCLUDED_VISHV_AI_GRAPH_H

namespace Vishv::AI
{
	class GraphSearch;

	using NodeID = uint32_t;

	struct Node
	{
		META_CLASS_DECLARE

		Node() = default;
		uint32_t mID = -1;
		Math::Vector3 mCoordinate;
		std::vector<Node*> mChildren;
		bool isBlocked = false;

		constexpr bool operator== (const Node& other) const
		{
			return this->mID == other.mID;
		}
		constexpr bool operator!= (const Node& other) const
		{
			return this->mID != other.mID;
		}
	};

	class Graph
	{
	public:
		META_CLASS_DECLARE

		void Initialize(size_t numberNodes, size_t maxChildrens = 0);	//leave 0 if not known
		void InitializeGrid2D(const Math::Vector3& startPos, size_t columns = 5, size_t rows = 5, float columnThickness = 10.0f, float rowThickness = 10.0f);		//makes a grid graph on a plane

		//get nearest node & get node ID
		NodeID GetNearestNodeID(const Math::Vector3& coord);	//returns nearest node ID from a given vector3
		Node* GetNearestNode(const Math::Vector3& coord);	//returns weak pointer to the nearest node from vector3

		Node* GetNode(NodeID nodeID);	//returns weak pointer for the node ID
		Node* GetNode(const Math::Vector3& coord);	//returns a weak pointer for the node coordinate

		void ConnectNoCheck(float radius);				// Goes through all the nodes does a radius check and connect them, doesnt check the line of site

		bool IsInitalized() { return mIsInitialized; }

		std::vector<std::unique_ptr<Node>>& GetNodes() { return mGraph; }

		Node* AddNode();
	private:
		friend class GraphSearch;
		bool mIsInitialized = false;
		std::vector<std::unique_ptr<Node>> mGraph;
		size_t mNumberOfNodes = 0;
	};
}

#endif // !INCLUDED_VISHV_AI_GRAPH_H


