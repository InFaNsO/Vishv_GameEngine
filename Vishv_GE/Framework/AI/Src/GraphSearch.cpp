#include "Precompiled.h"

#include "Graph.h"
#include "GraphSearch.h"



META_CLASS_BEGIN(Vishv::AI::GraphSearch::SearchNode)
	META_FIELD_BEGIN
		//META_FIELD(node, "Node")
		META_FIELD(parent, "Parent")
	META_FIELD_END
META_CLASS_END

META_CLASS_BEGIN(Vishv::AI::GraphSearch)
	META_FIELD_BEGIN
		//META_FIELD(mGraph, "memberGraph")
		//META_FIELD(mNodes, "memberSearchNodes")
		META_FIELD(path, "Path")
	META_FIELD_END
META_CLASS_END

using namespace Vishv;
using namespace Vishv::AI;

void Vishv::AI::GraphSearch::SetGraph(Graph & graph)
{
	mGraph = &graph;
	mNodes.clear();
	mOpenList.clear();
	mClosedList.clear();

	mNodes.reserve(mGraph->mNumberOfNodes);

	for (uint32_t i = 0; i < mGraph->mNumberOfNodes; ++i)
	{
		std::unique_ptr<SearchNode>sn = std::make_unique<SearchNode>();
		sn->node = mGraph->mGraph[i].get();
		mNodes.emplace_back(std::move(sn));
	}

}

const std::vector<Math::Vector3>& Vishv::AI::GraphSearch::GetPath(bool calculate)
{
	if (!calculate)
		return path;

	path.clear();
	path.reserve(mClosedList.size());

	SearchNode* current = mClosedList.back();
	SearchNode* start = mClosedList.front();

	while (current->node->mID != start->node->mID)
	{
		path.emplace_back(current->node->mCoordinate);
		current = current->parent;
	}

	return path;
}

Vishv::AI::GraphSearch::SearchNode* AI::GraphSearch::GetNode(Math::Vector3& pos)
{
	return mNodes[mGraph->GetNearestNodeID(pos)].get();
}

std::vector<Math::Vector3>& Vishv::AI::GraphSearch::GetClosedList()
{
	pathClosed.clear();
	pathClosed.reserve(mClosedList.size());

	for (auto& it : mClosedList)
	{
		pathClosed.emplace_back(it->node->mCoordinate);
	}

	return pathClosed;
}

std::vector<Vishv::Math::Vector3>& Vishv::AI::GraphSearch::RPath()
{
	GetPath(true);
	return path;
	// TODO: insert return statement here
}

std::vector<Math::Vector3>&& Vishv::AI::GraphSearch::GetPathMoved(bool calculate)
{
	GetPath(calculate);
	return std::move(path);
}

void Vishv::AI::GraphSearch::Reset()
{
	for (uint32_t i = 0; i < mNodes.size(); ++i)
	{
		mNodes[i]->g = 0.0f;
		mNodes[i]->h = 0.0f;
		mNodes[i]->opened = false;
		mNodes[i]->closed = false;
		mNodes[i]->parent = nullptr;
	}

	mOpenList.clear();
	mClosedList.clear();
}

void Vishv::AI::GraphSearch::UnInformedChecker(SearchNode & parent, SearchNode & child)
{
	if (!child.node->isBlocked && !child.opened && !child.closed)
	{
		child.opened = true;
		mOpenList.emplace_back(&child);
		child.parent = &parent;
	}
}


bool Vishv::AI::GraphSearch::RunBreathFirstSearch(Math::Vector3 & start, Math::Vector3 & end, bool isExact)
{
	NodeID startID = isExact ? mGraph->GetNode(start)->mID : mGraph->GetNearestNodeID(start);
	NodeID endID = isExact ? mGraph->GetNode(end)->mID : mGraph->GetNearestNodeID(end);

	return RunBreathFirstSearch(startID, endID);
}

bool Vishv::AI::GraphSearch::RunBreathFirstSearch(NodeID start, NodeID end)
{
	Reset();
	mOpenList.emplace_back(mNodes[start].get());
	mNodes[start]->opened = true;

	bool found = false;

	while (!found && !mOpenList.empty())
	{
		SearchNode* current = mOpenList.front();
		mOpenList.pop_front();
		if (current->node->mID == end)
		{
			found = true;
			mClosedList.push_back(current);
			continue;
		}

		for (size_t childCounter = 0; childCounter < current->node->mChildren.size(); ++childCounter)
		{
			UnInformedChecker(*current, *mNodes[current->node->mChildren[childCounter]->mID]);
		}
		mClosedList.push_back(current);
		current->closed = true;
	}

	return found;
}

bool Vishv::AI::GraphSearch::RunDepthFirstSearch(Math::Vector3 & start, Math::Vector3 & end, bool isExact)
{
	NodeID startID = isExact ? mGraph->GetNode(start)->mID : mGraph->GetNearestNodeID(start);
	NodeID endID = isExact ? mGraph->GetNode(end)->mID : mGraph->GetNearestNodeID(end);

	return RunDepthFirstSearch(startID, endID);
}

bool Vishv::AI::GraphSearch::RunDepthFirstSearch(NodeID start, NodeID end)
{
	Reset();
	mOpenList.emplace_back(mNodes[start].get());
	mNodes[start]->opened = true;

	bool found = false;

	while (!found && !mOpenList.empty())
	{
		SearchNode* current = mOpenList.back();
		mOpenList.pop_back();
		if (current->node->mID == end)
		{
			found = true;
			mClosedList.push_back(current);
			continue;
		}

		for (size_t childCounter = 0; childCounter < current->node->mChildren.size(); ++childCounter)
		{
			UnInformedChecker(*current, *mNodes[current->node->mChildren[childCounter]->mID]);
		}
		mClosedList.push_back(current);
		current->closed = true;
	}

	return found;
}

bool Vishv::AI::GraphSearch::RunDijkstra(Math::Vector3 & start, Math::Vector3 & end, CostFunc costFunction, bool isExact)
{
	NodeID startID = isExact ? mGraph->GetNode(start)->mID : mGraph->GetNearestNodeID(start);
	NodeID endID = isExact ? mGraph->GetNode(end)->mID : mGraph->GetNearestNodeID(end);

	return RunDijkstra(startID, endID, costFunction);
}

bool Vishv::AI::GraphSearch::RunDijkstra(NodeID start, NodeID end, CostFunc costFunction)
{
	Reset();
	mOpenList.emplace_back(mNodes[start].get());
	mNodes[start]->opened = true;

	bool found = false;

	while (!found && !mOpenList.empty())
	{
		SearchNode* current = mOpenList.front();
		mOpenList.pop_front();
		if (current->node->mID == end)
		{
			found = true;
			mClosedList.push_back(current);
			continue;
		}

		std::vector<Node*>& children = current->node->mChildren;
		for (auto child : children)
		{
			SearchNode* sChild = mNodes[child->mID].get();

			if (child->isBlocked)
				continue;
			float newG = costFunction(*current->node, *child) + sChild->g;

			if (!sChild->opened)
			{
				sChild->parent = current;
				sChild->g = newG;

				auto it = mOpenList.begin();
				for (; it != mOpenList.end(); ++it)
				{
					if (it._Ptr->_Myval->g > sChild->g)
						break;
				}

				mOpenList.insert(it, sChild);
				sChild->opened = true;
			}
			else if (!sChild->closed)
			{
				if (newG < sChild->g)
				{
					sChild->parent = current;
					sChild->g = newG;

					mOpenList.sort([this](const SearchNode* first, const SearchNode* second)
					{
						return first->g < second->g;
					}
					);
				}
			}
		}
		mClosedList.push_back(current);
		current->closed = true;
	}
	return found;
}

bool Vishv::AI::GraphSearch::RunAStar(const Math::Vector3 & start, const Math::Vector3 & end, CostFunc costFunction, HeuristicFunc heuristicFunction, bool isExact)
{
	NodeID startID = isExact ? mGraph->GetNode(start)->mID : mGraph->GetNearestNodeID(start);
	NodeID endID = isExact ? mGraph->GetNode(end)->mID : mGraph->GetNearestNodeID(end);

	return RunAStar(startID, endID, costFunction, heuristicFunction);
}

bool Vishv::AI::GraphSearch::RunAStar(NodeID start, NodeID end, CostFunc costFunction, HeuristicFunc heuristicFunction)
{
	Reset();
	mOpenList.emplace_back(mNodes[start].get());
	mNodes[start]->opened = true;

	bool found = false;

	while (!found && !mOpenList.empty())
	{
		SearchNode* current = mOpenList.front();
		mOpenList.pop_front();
		if (current->node->mID == end)
		{
			found = true;
			mClosedList.push_back(current);
			continue;
		}

		std::vector<Node*>& children = current->node->mChildren;
		for (auto child : children)
		{
			SearchNode* sChild = mNodes[child->mID].get();

			if (child->isBlocked)
				continue;
			float newG = costFunction(*current->node, *child) + sChild->g;

			if (!sChild->opened)
			{
				sChild->parent = current;
				sChild->g = newG;
				sChild->h = heuristicFunction(*mNodes[end].get()->node, *child);

				auto it = mOpenList.begin();
				for (; it != mOpenList.end(); ++it)
				{
					if ((it._Ptr->_Myval->g + it._Ptr->_Myval->h) > (sChild->g + sChild->h))
						break;
				}

				mOpenList.insert(it, sChild);
				sChild->opened = true;
			}
			else if (!sChild->closed)
			{
				if (newG < sChild->g)
				{
					sChild->parent = current;
					sChild->g = newG;

					mOpenList.sort([this](const SearchNode* first, const SearchNode* second)
					{
						return first->g + first->h < second->g + second->h;
					}
					);
				}
			}
		}
		mClosedList.push_back(current);
		current->closed = true;
	}
	return found;
}


