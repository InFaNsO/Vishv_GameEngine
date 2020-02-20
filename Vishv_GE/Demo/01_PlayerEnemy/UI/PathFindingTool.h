#pragma once

#include "Vishv/Inc/Vishv.h"

namespace Vishv::UI
{
	class PathFindingTool
	{
	public:
		void Initialize(Vishv::AI::Graph& urGraph, Vishv::AI::GraphSearch& urSearch);

		void DrawUI();

		void SimpleDraw();
	
		std::vector<Math::Vector3>& GetPath() { return *path; }

	private:
		bool drawGraph = false;
		bool drawClosedList = false;
		bool hasPath = false;

		int searchType = 0;

		std::vector<Vishv::Math::Vector3>* path;

		Vishv::AI::Graph* yourGraph = nullptr;
		Vishv::AI::GraphSearch* yourGraphSearch = nullptr;

		int maxRow = 10;
		int maxCol = 10;
		float rowThick = 10.0f;
		float colThick = 10.0f;

		int startRow = 5;
		int startCol = 6;

		int endRow = 0;
		int endCol = 0;

		Vishv::Math::Vector3 startPosition;
	};
}
