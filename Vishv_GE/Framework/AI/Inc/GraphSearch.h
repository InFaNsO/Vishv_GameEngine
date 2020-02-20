#ifndef INCLUDED_VISHV_AI_GRAPH_SEARCH_H
#define INCLUDED_VISHV_AI_GRAPH_SEARCH_H

namespace Vishv::AI
{
	class Graph;
	struct Node;

	using NodeID = uint32_t;

	class GraphSearch
	{
	public:
		struct SearchNode
		{
			META_CLASS_DECLARE
			Node* node;
			SearchNode* parent = nullptr;
			float g = 0.0f;
			float h = 0.0f;
			bool opened = false;
			bool closed = false;
		};

		META_CLASS_DECLARE

		enum class SearchType
		{
			BreathFirstSearch = 1,
			DepthFirstSearch = 2,
			Dijkstra = 3,
			AStar = 4,

			max = 5
		};



		using CostFunc = std::function<float(Node&, Node&)>;
		using HeuristicFunc = std::function<float(Node&, Node&)>;

		size_t GetNodeID(int row, int col, int maxCol) { return col + (row * (maxCol + 1)); }
		void SetGraph(Graph& graph);
		const std::vector<Math::Vector3>& GetPath(bool calculate = true);
		std::vector<Math::Vector3>&& GetPathMoved(bool calculate = true);		//to move the path vector

		//Searches
		bool RunBreathFirstSearch(Math::Vector3& start, Math::Vector3& end, bool isExact = false);		//the exact value if true will be more efficient
		bool RunBreathFirstSearch(NodeID start, NodeID end);

		bool RunDepthFirstSearch(Math::Vector3& start, Math::Vector3& end, bool isExact = false);
		bool RunDepthFirstSearch(NodeID start, NodeID end);

		bool RunDijkstra(Math::Vector3& start, Math::Vector3& end, CostFunc costFunction, bool isExact = false);
		bool RunDijkstra(NodeID start, NodeID end, CostFunc costFunction);

		bool RunAStar(const Math::Vector3& start, const Math::Vector3& end, CostFunc costFunction, HeuristicFunc heuristicFunction, bool isExact = false);
		bool RunAStar(NodeID start, NodeID end, CostFunc costFunction, HeuristicFunc heuristicFunction);

		std::vector<Math::Vector3>& GetClosedList();
		SearchNode* GetNode(Math::Vector3& pos); 
		std::vector<Math::Vector3>& RPath();

	private:
		void UnInformedChecker(SearchNode& parent, SearchNode& child);
		void Reset();
		Graph* mGraph;

		std::vector<std::unique_ptr<SearchNode>> mNodes;

		std::list<SearchNode*> mOpenList;
		std::list<SearchNode*> mClosedList;

		std::vector<Math::Vector3> path;
		std::vector<Math::Vector3> pathClosed;

	};
}


#endif // !INCLUDED_VISHV_AI_GRAPH_SEARCH_H


#pragma once
