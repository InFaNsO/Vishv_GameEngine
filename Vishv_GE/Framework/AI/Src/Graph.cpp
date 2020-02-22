#include "Precompiled.h"
#include "Graph.h"

using namespace Vishv;
using namespace Vishv::AI;

META_CLASS_BEGIN(Node)
	META_FIELD_BEGIN
		META_FIELD(mID, "ID")
		META_FIELD(mCoordinate, "Coordinate")
		META_FIELD(mChildren, "Children")
		META_FIELD(isBlocked, "IsBlocked")
	META_FIELD_END
META_CLASS_END

META_CLASS_BEGIN(Graph)
	META_FIELD_BEGIN
		//META_FIELD(mGraph, "Nodes")
		META_FIELD(mNumberOfNodes, "NumberOfNodes")
	META_FIELD_END
META_CLASS_END


namespace
{
	bool IsInRange(const Math::Vector3& pos1, const Math::Vector3& pos2, float radius)
	{
		if (Math::Abs(Math::MagnitudeSqr(pos1 - pos2)) > radius * radius + radius * radius)
			return false;
		return true;
	}
}

void Vishv::AI::Graph::Initialize(size_t numberNodes, size_t maxChildrens)
{
	//VISHVASSERT(!mIsInitialized, "[AI::Graph::Initialize] Graph already initialized");
	mIsInitialized = true;
	mNumberOfNodes = numberNodes;

	mGraph.clear();
	mGraph.reserve(numberNodes);



	for (size_t i = 0; i < numberNodes; ++i)
	{
		std::unique_ptr<Node> n = std::make_unique<Node>();
		n->mID = (uint32_t)i;
		mGraph.emplace_back(std::move(n));
	}

	if (maxChildrens > 0)
	{
		for (size_t i = 0; i < numberNodes; ++i)
		{
			mGraph[i]->mChildren.reserve(maxChildrens);
		}
	}
}

void	Vishv::AI::Graph::InitializeGrid2D(const Vishv::Math::Vector3 & startPos, size_t columns, size_t rows, float columnThickness, float rowThickness)
{
	Initialize((rows + 1)* (columns + 1), 8);

	for (size_t i = 0; i <= rows; ++i)
	{
		for (size_t j = 0; j <= columns; ++j)
		{
			NodeID index = (NodeID)( j + (i * (columns + 1)));

			mGraph[index]->mCoordinate = { startPos.x + (j * columnThickness), startPos.y, startPos.z + (i * rowThickness) };

			for (int x = ((int)j) - 1; x <= (int)j + 1; ++x)
				for (int y = (int)i - 1; y <= (int)i + 1; ++y)
					if (x >= 0 && x < (int)columns + 1 && y >= 0 && y < (int)rows + 1)
						if(index != x + (y * (columns + 1)))
							mGraph[index]->mChildren.emplace_back(mGraph[x + (y * (columns + 1))].get());
		}
	}
}

NodeID	Vishv::AI::Graph::GetNearestNodeID(const Math::Vector3 & coord)
{
	VISHVASSERT(mIsInitialized, "[AI::Graph::Initialize] Graph already initialized");
	
	NodeID nearestID = 0;
	float nearestDistance = Math::Abs(Math::MagnitudeSqr(coord - mGraph[0]->mCoordinate));

	for (size_t i = 1; i < mGraph.size(); ++i)
	{
		float distance = Math::Abs(Math::MagnitudeSqr(coord - mGraph[i]->mCoordinate));
		if (nearestDistance > distance)
		{
			nearestDistance = distance;
			nearestID = mGraph[i]->mID;
		}
	}

	return nearestID;
}

Node *	Vishv::AI::Graph::GetNearestNode(const Math::Vector3 & coord)
{
	VISHVASSERT(mIsInitialized, "[AI::Graph::Initialize] Graph already initialized");

	NodeID nearestID = 0;
	float nearestDistance = Math::Abs(Math::MagnitudeSqr(coord - mGraph[0]->mCoordinate));

	for (size_t i = 1; i < mGraph.size(); ++i)
	{
		float distance = Math::Abs(Math::MagnitudeSqr(coord - mGraph[i]->mCoordinate));
		if (nearestDistance < distance)
		{
			nearestDistance = distance;
			nearestID = mGraph[i]->mID;
		}
	}

	return mGraph[nearestID].get();
}

Node *	Vishv::AI::Graph::GetNode(NodeID nodeID)
{
	VISHVASSERT(mIsInitialized, "[AI::Graph::Initialize] Graph already initialized");
	VISHVASSERT(nodeID < mNumberOfNodes, "[AI::Graph::Initialize] Node ID out of range");

	return mGraph[nodeID].get();
}

Node *	Vishv::AI::Graph::GetNode(const Math::Vector3& coord)
{
	VISHVASSERT(mIsInitialized, "[AI::Graph::Initialize] Graph already initialized");

	size_t ID = mNumberOfNodes;

	for (size_t i = 1; i < mGraph.size(); ++i)
	{
		if (mGraph[i]->mCoordinate == coord)
		{
			ID = mGraph[i]->mID;
		}
	}

	VISHVASSERT(ID != mNumberOfNodes, "[AI::GetNode] Coordinate doesnt belong to the graph.");

	return mGraph[ID].get();
}

Node* Vishv::AI::Graph::AddNode()
{
	auto node = mGraph.emplace_back(std::make_unique<Node>()).get();
	node->mID = (uint32_t)mGraph.size() - 1;
	mNumberOfNodes++;
	return node;
}

void	Vishv::AI::Graph::ConnectNoCheck(float radius)
{
	for (auto& node1 : mGraph)
	{
		for (auto& node2 : mGraph)
		{
			//is they are the same leave it
			if (node1->mID == node2->mID)
				continue;

			//check if it exist in the children
			bool exists = false;
			for (auto& child1 : node1->mChildren)
			{
				if (child1->mID == node2->mID)
				{
					exists = true;
					break;
				}
			}
			if (exists)
				continue;

			//if its in range add each other as children
			if (!IsInRange(node1->mCoordinate, node2->mCoordinate, radius))
				continue;

			node1->mChildren.emplace_back(node2.get());
			node2->mChildren.emplace_back(node1.get());
		}
	}
}


