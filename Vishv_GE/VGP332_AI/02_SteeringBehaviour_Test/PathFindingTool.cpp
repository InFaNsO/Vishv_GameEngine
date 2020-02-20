#include "PathFindingTool.h"

namespace
{
	std::string ToString(Vishv::AI::GraphSearch::SearchType type)
	{
		switch (type)
		{
		case Vishv::AI::GraphSearch::SearchType::BreathFirstSearch:
			return "BreathFirstSearch";
			break;
		case Vishv::AI::GraphSearch::SearchType::DepthFirstSearch:
			return "DepthFirstSearch";
			break;
		case Vishv::AI::GraphSearch::SearchType::Dijkstra:
			return "Dijkstra";
			break;
		case Vishv::AI::GraphSearch::SearchType::AStar:
			return "AStar";
			break;
		default:
			return "none";
			break;
		}
	}

	float CostFunction(Vishv::AI::Node & parent, Vishv::AI::Node & child)
	{
		return Vishv::Math::MagnitudeSqr(child.mCoordinate - parent.mCoordinate);
	}

	float HeuristicFunction(Vishv::AI::Node & child, Vishv::AI::Node & end)
	{
		return Vishv::Math::MagnitudeSqr(end.mCoordinate - child.mCoordinate);
	}
}


void Vishv::UI::PathFindingTool::Initialize(Vishv::AI::Graph & urGraph, Vishv::AI::GraphSearch& urSearch)
{
	yourGraph = &urGraph;
	yourGraphSearch = &urSearch;
}

void Vishv::UI::PathFindingTool::DrawUI()
{

	ImGui::Begin("Path Finding");

	if (!yourGraph->IsInitalized())
	{
		ImGui::Text("Graph Setup");
		ImGui::DragFloat3("Graph Start Position", &startPosition.x);
		ImGui::DragInt("Graph Row##PathFinding", &maxRow, 1.0f);
		ImGui::DragInt("Graph Col##PathFinding", &maxCol, 1.0f);

		ImGui::DragFloat("Row Thickness##PathFinding", &rowThick, 0.5f);
		ImGui::DragFloat("Col Thickness##PathFinding", &colThick, 0.5f);

		if (ImGui::Button("Initialize Graph"))
		{
			if (maxRow > 0 && maxRow > 0)
			{
				//mGraph.Initialize(10, 8);
				yourGraph->InitializeGrid2D(startPosition, (size_t)maxCol, (size_t)maxRow, colThick, rowThick);
				yourGraphSearch->SetGraph(*yourGraph);
			}
		}
	}
	else
	{
		ImGui::Checkbox("Draw Grid", &drawGraph);
		ImGui::Checkbox("Draw Closed List", &drawClosedList);

		ImGui::Text("Path finding");
		ImGui::SliderInt("Start Row##PathFinding", &startRow, 0, maxRow);
		ImGui::SliderInt("Start Col##PathFinding", &startCol, 0, maxCol);

		ImGui::SliderInt("End Row##PathFinding", &endRow, 0, maxRow);
		ImGui::SliderInt("End Col##PathFinding", &endCol, 0, maxCol);

		ImGui::SliderInt("Search Type", &searchType, 0, (int)AI::GraphSearch::SearchType::max - 1);
		ImGui::Text(ToString((AI::GraphSearch::SearchType)searchType).c_str());

		if (ImGui::Button("FindPath") && searchType != 0)
		{
			if (!(startCol == endCol && startRow == endRow))
			{
				hasPath = true;
				AI::GraphSearch::SearchType type = (AI::GraphSearch::SearchType)searchType;

				switch (type)
				{
				case Vishv::AI::GraphSearch::SearchType::BreathFirstSearch:
					yourGraphSearch->RunBreathFirstSearch((size_t)yourGraphSearch->GetNodeID(startRow, startCol, maxCol), (size_t)yourGraphSearch->GetNodeID(endRow, endCol, maxCol));
					break;
				case Vishv::AI::GraphSearch::SearchType::DepthFirstSearch:
					yourGraphSearch->RunDepthFirstSearch((size_t)yourGraphSearch->GetNodeID(startRow, startCol, maxCol), (size_t)yourGraphSearch->GetNodeID(endRow, endCol, maxCol));
					break;
				case Vishv::AI::GraphSearch::SearchType::Dijkstra:
					yourGraphSearch->RunDijkstra((size_t)yourGraphSearch->GetNodeID(startRow, startCol, maxCol), (size_t)yourGraphSearch->GetNodeID(endRow, endCol, maxCol), CostFunction);
					break;
				case Vishv::AI::GraphSearch::SearchType::AStar:
				{
					//to do member variables
						//auto func = [this]()
						//{
						//	CostFunction();
						//};
					yourGraphSearch->RunAStar((size_t)yourGraphSearch->GetNodeID(startRow, startCol, maxCol), (size_t)yourGraphSearch->GetNodeID(endRow, endCol, maxCol), CostFunction, HeuristicFunction);
				}
				break;
				case Vishv::AI::GraphSearch::SearchType::max:
					break;
				default:
					break;
				}

				path = &yourGraphSearch->RPath();
			}
		}
	}
	ImGui::End();
}

void Vishv::UI::PathFindingTool::SimpleDraw()
{
	if (!yourGraph->IsInitalized())
	{
		Graphics::SimpleDraw::AddSphere(startPosition, 2.0f, Graphics::Colors::Magenta);
		//draw plane		if time

		for (int i = 0; i <= maxRow; ++i)
		{
			for (int j = 0; j <= maxCol; ++j)
			{
				Graphics::SimpleDraw::AddLine({ startPosition.x + (i * rowThick), startPosition.y, startPosition.z }, {startPosition.x + (i * rowThick), startPosition.y, startPosition.z + (maxCol * colThick)}, Graphics::Colors::Aquamarine);
				Graphics::SimpleDraw::AddLine({ startPosition.x, startPosition.y, startPosition.z + (j * colThick) }, {startPosition.x + (maxRow * rowThick), startPosition.y, startPosition.z + (j * colThick)}, Graphics::Colors::Aquamarine);
			}
		}
		return;
	}
	//Draw Graph
	if (!hasPath || drawGraph)
	{
		for (auto& node : yourGraph->GetNodes())
		{
			Graphics::SimpleDraw::AddSphere(node->mCoordinate, 2.0f, Graphics::Colors::DarkGoldenrod, 5, 5);

			for (auto& child : node->mChildren)
			{
				Graphics::SimpleDraw::AddLine({ node->mCoordinate, Graphics::Colors::Red }, { {child->mCoordinate.x , child->mCoordinate.y + 0.5f, child->mCoordinate.z}, Graphics::Colors::Green });
			}
		}
	}
	Graphics::SimpleDraw::AddSphere(yourGraph->GetNode(yourGraphSearch->GetNodeID(startRow, startCol, maxCol))->mCoordinate, 4.0f, Vishv::Graphics::Colors::AliceBlue);
	Graphics::SimpleDraw::AddSphere(yourGraph->GetNode(yourGraphSearch->GetNodeID(endRow, endCol, maxCol))->mCoordinate, 4.0f, Vishv::Graphics::Colors::DarkOrange);

	//Draw Path
	if (!hasPath)
		return;

	auto cl = yourGraphSearch->GetClosedList();
	if (drawClosedList)
	{
		for (size_t i = 1; i < cl.size(); ++i)
		{
			Vishv::Math::Vector3 n = cl[i];
			AI::GraphSearch::SearchNode* p = yourGraphSearch->GetNode(n);
			if (p->parent == nullptr)
				continue;
			Graphics::SimpleDraw::AddSphere({ n.x, n.y + 4.0f, n.z }, 02.0f, Graphics::Colors::DarkRed, 5, 5);
			Graphics::SimpleDraw::AddLine({ {n.x, n.y + 4.0f, n.z}, Graphics::Colors::DarkRed }, { {p->parent->node->mCoordinate.x, p->parent->node->mCoordinate.y + 4.f, p->parent->node->mCoordinate.z}, Graphics::Colors::White });
		}
	}
	Math::Vector3 prv = { -1,-1,-1 };
	for (auto& coord : *path)
	{
		Graphics::SimpleDraw::AddSphere({ coord.x, coord.y + 4.0f, coord.z }, 5.0f, Graphics::Colors::LightCyan, 5, 5);

		if (prv != Math::Vector3(-1, -1, -1))
		{
			//drawLine
			Graphics::SimpleDraw::AddLine({ {coord.x, coord.y + 4.0f, coord.z}, Graphics::Colors::Orange }, { {prv.x, prv.y + 2.f, prv.z}, Graphics::Colors::Yellow });
		}
		prv = coord;
	}
}

