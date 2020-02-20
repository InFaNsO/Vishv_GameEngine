#include "MainState.h"

using namespace Vishv;

namespace
{
	std::string ToString(AI::GraphSearch::SearchType type)
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

	float CostFunction(Vishv::AI::Node & n1, Vishv::AI::Node & n2)
	{
		return Vishv::Math::MagnitudeSqr(n2.mCoordinate - n1.mCoordinate);
	}

	float HeuristicFunction(Vishv::AI::Node & n1, Vishv::AI::Node & n2)
	{
		return Vishv::Math::MagnitudeSqr(n2.mCoordinate - n1.mCoordinate);
	}
}



void MainState::Initialize()
{
	scene.sceneCamera->transform.RotateX(-90.0f);
}

void MainState::Update(float deltaTime)
{
}

void MainState::RenderSimpleDraw()
{
	if (!mGraph.IsInitalized())
	{
		Graphics::SimpleDraw::AddSphere(startPosition, 2.0f, Graphics::Colors::Magenta);
		//draw plane		if time
		return;
	}
	//Draw Graph
	if (!hasPath || drawGraph)
	{
		for (auto& node : mGraph.GetNodes())
		{
			Graphics::SimpleDraw::AddSphere(node->mCoordinate, 2.0f, Graphics::Colors::DarkGoldenrod, 5, 5);

			for (auto& child : node->mChildren)
			{
				Graphics::SimpleDraw::AddLine({ node->mCoordinate, Graphics::Colors::Red }, { {child->mCoordinate.x , child->mCoordinate.y + 0.5f, child->mCoordinate.z}, Graphics::Colors::Green });
			}
		}
	}
	Graphics::SimpleDraw::AddSphere(mGraph.GetNode(mGraphSearch.GetNodeID(startRow, startCol, graphCol))->mCoordinate, 4.0f, Vishv::Graphics::Colors::AliceBlue);
	Graphics::SimpleDraw::AddSphere(mGraph.GetNode(mGraphSearch.GetNodeID(endRow, endCol, graphCol))->mCoordinate, 4.0f, Vishv::Graphics::Colors::DarkOrange);

	//Draw Path
	if (!hasPath)
		return;

	auto cl = mGraphSearch.GetClosedList();
	if (drawCL)
	{
		for (size_t i = 1; i < cl.size(); ++i)
		{
			Vishv::Math::Vector3 n = cl[i];
			AI::GraphSearch::SearchNode* p = mGraphSearch.GetNode(n);
			if (p->parent == nullptr)
				continue;
			Graphics::SimpleDraw::AddSphere({ n.x, n.y + 4.0f, n.z }, 02.0f, Graphics::Colors::DarkRed, 5, 5);
			Graphics::SimpleDraw::AddLine({ {n.x, n.y + 4.0f, n.z}, Graphics::Colors::DarkRed }, { {p->parent->node->mCoordinate.x, p->parent->node->mCoordinate.y + 4.f, p->parent->node->mCoordinate.z}, Graphics::Colors::White });
		}
	}
	Math::Vector3 prv = {-1,-1,-1};
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

void MainState::RenderDebugUI()
{
	ImGui::Begin("Path Finding");

	if (!mGraph.IsInitalized())
	{
		ImGui::Text("Graph Setup");
		ImGui::DragFloat3("Graph Start Position", &startPosition.x);
		ImGui::DragInt("Graph Row##PathFinding", &graphRow, 1.0f, 0, 10);
		ImGui::DragInt("Graph Col##PathFinding", &graphCol, 1.0f, 0, 10);

		ImGui::DragFloat("Row Thickness##PathFinding", &rowThick, 0.5f, 1.0f, 10.0f);
		ImGui::DragFloat("Col Thickness##PathFinding", &colThick, 0.5f, 1.0f, 10.0f);

		if (ImGui::Button("Initialize Graph"))
		{
			if (graphRow > 0 && graphCol > 0)
			{
				//mGraph.Initialize(10, 8);
				mGraph.InitializeGrid2D(startPosition, (size_t)graphRow, (size_t)graphCol, rowThick, colThick);
				mGraphSearch.SetGraph(mGraph);
			}
		}
	}
	else
	{
		ImGui::Checkbox("DrawGrid", &drawGraph);
		ImGui::Checkbox("DrawClosedList", &drawCL);

		ImGui::Text("Path finding");
		ImGui::SliderInt("Start Row##PathFinding", &startRow, 0, graphRow);
		ImGui::SliderInt("Start Col##PathFinding", &startCol, 0, graphCol);

		ImGui::SliderInt("End Row##PathFinding", &endRow, 0, graphRow);
		ImGui::SliderInt("End Col##PathFinding", &endCol, 0, graphCol);

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
					mGraphSearch.RunBreathFirstSearch(mGraphSearch.GetNodeID(startRow , startCol , graphCol), mGraphSearch.GetNodeID(endRow , endCol ,graphCol));
					break;
				case Vishv::AI::GraphSearch::SearchType::DepthFirstSearch:
					mGraphSearch.RunDepthFirstSearch(mGraphSearch.GetNodeID(startRow, startCol, graphCol), mGraphSearch.GetNodeID(endRow, endCol, graphCol));
					break;
				case Vishv::AI::GraphSearch::SearchType::Dijkstra:
					mGraphSearch.RunDijkstra((size_t)mGraphSearch.GetNodeID(startRow, startCol, graphCol), (size_t)mGraphSearch.GetNodeID(endRow, endCol, graphCol), CostFunction);
					break;
				case Vishv::AI::GraphSearch::SearchType::AStar:
					{
					//to do member variables
						//auto func = [this]()
						//{
						//	CostFunction();
						//};
					mGraphSearch.RunAStar(mGraphSearch.GetNodeID(startRow, startCol, graphCol), mGraphSearch.GetNodeID(endRow, endCol, graphCol), CostFunction, HeuristicFunction);
					}
					break;
				case Vishv::AI::GraphSearch::SearchType::max:
					break;
				default:
					break;
				}

				path = &mGraphSearch.RPath();
			}
		}
	}
	ImGui::End();
}


void MainState::Render()
{
}


void MainState::Terminate()
{
}




