#include "Precompiled.h"
#include "AIPathFinding.h"

namespace
{
	float CostFunction(Vishv::AI::Node & n1, Vishv::AI::Node & n2)
	{
		return Vishv::Math::MagnitudeSqr(n2.mCoordinate - n1.mCoordinate);
	}

	float HeuristicFunction(Vishv::AI::Node & n1, Vishv::AI::Node & n2)
	{
		return Vishv::Math::MagnitudeSqr(n2.mCoordinate - n1.mCoordinate);
	}
}

using namespace Vishv::Components;

META_DERIVED_BEGIN(AIPathFinding, Component)
	META_FIELD_BEGIN
		//META_FIELD(mGraph, "Graph")
		//META_FIELD(mGraphSearch, "Graph Search")
	META_FIELD_END
META_CLASS_END



void Vishv::Components::AIPathFinding::Initialize()
{
	mGraph.Initialize(1);
	mCurrentNode = mGraph.GetNode(0);
}


void Vishv::Components::AIPathFinding::Terminate()
{
}

void Vishv::Components::AIPathFinding::Update(float deltaTime)
{
}

void Vishv::Components::AIPathFinding::SimpleDraw()
{
	if (useGrid)
	{
		Graphics::SimpleDraw::AddSphere(mStartPos, 2.0f, Graphics::Colors::Magenta);

		for (int i = 0; i <= graphRow; ++i)
		{
			for (int j = 0; j <= graphCol; ++j)
			{
				Graphics::SimpleDraw::AddLine({ mStartPos.x + (i * rowThickness), mStartPos.y, mStartPos.z }, { mStartPos.x + (i * rowThickness), mStartPos.y, mStartPos.z + (graphCol * colThickness) }, Graphics::Colors::Aquamarine);
				Graphics::SimpleDraw::AddLine({ mStartPos.x, mStartPos.y, mStartPos.z + (j * colThickness) }, { mStartPos.x + (graphRow * rowThickness), mStartPos.y, mStartPos.z + (j * colThickness) }, Graphics::Colors::Aquamarine);
			}
		}
	}

	if (!mShowAll)
	{
		if (mCurrentNode == nullptr)
			return;

		Graphics::SimpleDraw::AddSphere(mCurrentNode->mCoordinate, radius, Graphics::Colors::DarkGoldenrod, 5, 5);

		for (auto& child : mCurrentNode->mChildren)
		{
			Graphics::SimpleDraw::AddSphere(child->mCoordinate, radius, Graphics::Colors::LightBlue, 5, 5);
			Graphics::SimpleDraw::AddLine({ mCurrentNode->mCoordinate, Graphics::Colors::Red }, { {child->mCoordinate.x , child->mCoordinate.y, child->mCoordinate.z}, Graphics::Colors::Green });
		}
	}
	else
	{
		for (auto& node : mGraph.GetNodes())
		{
			Graphics::SimpleDraw::AddSphere(node->mCoordinate, radius, Graphics::Colors::DarkGoldenrod, 5, 5);

			for (auto& child : node->mChildren)
			{
				Graphics::SimpleDraw::AddLine({ node->mCoordinate, Graphics::Colors::Red }, { {child->mCoordinate.x , child->mCoordinate.y + 0.5f, child->mCoordinate.z}, Graphics::Colors::Green });
			}
		}
	}
}

uint32_t Vishv::Components::AIPathFinding::GetNodeID(const Math::Vector3 & pos)
{
	return mGraph.GetNearestNodeID(pos);
}

void Vishv::Components::AIPathFinding::DebugUI()
{
	static std::vector<std::unique_ptr<AI::Node>>& nodes = mGraph.GetNodes();

	if (!ImGui::CollapsingHeader("Path Finding"))
		return;

	int min = 0;
	int max = (int)nodes.size() - 1;

	int currentId = mCurrentNode->mID;
	if (ImGui::SliderInt("Select Node", &currentId, min, max))
		mCurrentNode = nodes[currentId].get();


	if (ImGui::Button("Add Node"))
		mCurrentNode = mGraph.AddNode();

	if (mCurrentNode == nullptr)
		return;

	if (ImGui::CollapsingHeader("Node Settings"))
	{
		ImGui::DragFloat3("Position: ", &mCurrentNode->mCoordinate.x);
		static int childIndex = 0;
		ImGui::SliderInt("Children", &childIndex, min, max);
		
		if (childIndex != (int)mCurrentNode->mID)
		{
			bool exists = false;
			for (auto c : mCurrentNode->mChildren)
			{
				if ((int)c->mID == childIndex)
				{
					exists = true;
					break;
				}
			}

			if (ImGui::Button("Add Child") && !exists)
			{
				mCurrentNode->mChildren.push_back(nodes[childIndex].get());
				nodes[childIndex]->mChildren.push_back(mCurrentNode);
			}
		}
		

		ImGui::Checkbox("Is Blocked", &mCurrentNode->isBlocked);
	}
	if (ImGui::CollapsingHeader("Debug Draw"))
	{
		ImGui::DragFloat("Radius", &radius, 1.0f, 0.0f, 100.0f);
		ImGui::Checkbox("Show Graph", &mShowAll);
	}

	if (ImGui::CollapsingHeader("Grid Graph"))
	{
		ImGui::DragFloat3("Start Pos ", &mStartPos.x);
		ImGui::SliderInt("Number Row", &graphRow, 1, 30);
		ImGui::SliderInt("Number Col", &graphCol, 1, 30);
		ImGui::DragFloat("Row Thickness", &rowThickness, 1.0f, 10.0f, 100.0f);
		ImGui::DragFloat("Col Thickness", &colThickness, 1.0f, 10.0f, 100.0f);
		
		if(ImGui::Button("Set grid"))
		{
			mGraph.InitializeGrid2D(mStartPos, graphRow, graphCol, rowThickness, colThickness);
		}
	}


	if (ImGui::Button("Save"))
		Save();
	if (ImGui::Button("Load"))
		Load("AiGraph.vgraph");

	if (ImGui::Button("Finalize"))
		mGraphSearch.SetGraph(mGraph);
}

void Vishv::Components::AIPathFinding::Save()
{
	std::fstream file;
	file.open("AiGraph.vgraph");

	VISHVASSERT(file.is_open(), "Pathfinding cant load the graph");

	auto& nodes = mGraph.GetNodes();
	
	file.clear();

	file << "Size: " << nodes.size() << std::endl;

	for (auto& node : nodes)
	{
		file << "Position: " << node->mCoordinate.ToString() << std::endl;
		file << "NumChild: " << node->mChildren.size() << "\n";
		for (auto& child : node->mChildren)
			file << child->mID << " ";

		int blocked = (int)node->isBlocked;
		file << "\nBlocked: " << blocked << "\n";
	}

	file.close();
}

void Vishv::Components::AIPathFinding::Load(std::filesystem::path p)
{
	std::fstream file;
	file.open(p);

	VISHVASSERT(file.is_open(), "Pathfinding cant load the graph");

	std::string holder;
	int size;
	file >> holder >> size;
	if (size == 0)
	{
		file.close();
		return;
	}

	mGraph.Initialize(size);
	auto& nodes = mGraph.GetNodes();

	for (auto& node : nodes)
	{
		file >> holder >> node->mCoordinate.x >> node->mCoordinate.y >> node->mCoordinate.z;
		file >> holder >> size;
		node->mChildren.reserve(size);
		for (int i = 0; i < size; ++i)
		{
			int index;
			file >> index;
			node->mChildren.emplace_back(nodes[index].get());
		}

		int block;
		file >> holder >> block;
		node->isBlocked = (bool)block;
	}
	file.close();
	mGraphSearch.SetGraph(mGraph);
}

Vishv::Math::Vector3 Vishv::Components::AIPathFinding::GetRandomNodePos()
{
	float percent = Math::Random::ZeroToOne();
	int index = (int)(percent * mGraph.GetNodes().size());

	return mGraph.GetNodes()[index]->mCoordinate;
}

const std::vector<Vishv::Math::Vector3>& Vishv::Components::AIPathFinding::RunAStar(const Math::Vector3 & start, const Math::Vector3 & end)
{
	mGraphSearch.RunAStar(start, end, CostFunction, HeuristicFunction);
	return mGraphSearch.GetPath();
}

