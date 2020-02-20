#include "SteeringTool.h"

using namespace Vishv;
using namespace AI;
using namespace Graphics;

namespace
{
	std::string ToString(SteeringType type)
	{
		switch (type)
		{
		case Vishv::AI::SteeringType::base:
			return "Base";
			break;
		case Vishv::AI::SteeringType::Arrive:
			return "Arrive";
			break;
		case Vishv::AI::SteeringType::Evade:
			return "Evade";
			break;
		case Vishv::AI::SteeringType::Flee:
			return "Flee";
			break;
		case Vishv::AI::SteeringType::Flocking:
			return "Flocking";
			break;
		case Vishv::AI::SteeringType::ObstacleAvoidance:
			return "Obstacle Avoidance";
			break;
		case Vishv::AI::SteeringType::Pursuit:
			return "Pursuit";
			break;
		case Vishv::AI::SteeringType::Seek:
			return "Seek";
			break;
		case Vishv::AI::SteeringType::Wander:
			return "Wander";
			break;
		default:
			return "Invalid";
			break;
		}
	}
}

void Vishv::UI::SteeringTool::Initialize(Vishv::AI::Agent & agent, Vishv::AI::SteeringModule & sm)
{
	a = &agent;
	mModule = &sm;
	agent.path.push_back(mTarget);
}

void Vishv::UI::SteeringTool::ChangeBehaviour()
{
	SteeringType type = (SteeringType)mCurrentBehaviour;

	switch (type)
	{
	case Vishv::AI::SteeringType::base:
		return;
		break;
	case Vishv::AI::SteeringType::count:
		return;
		break;
	}

	mModule->Reset();

	mModule->SetBehaviour((SteeringType)mCurrentBehaviour, true);
}

void Vishv::UI::SteeringTool::DrawUI()
{
	ImGui::Begin("Steering Module");
	
	//if (ImGui::SliderInt("SteeringType", &mCurrentBehaviour, (int)SteeringType::base, (int)SteeringType::count))
	//	ChangeBehaviour();
	//ImGui::Text(ToString((SteeringType)mCurrentBehaviour).c_str());

	if (ImGui::Checkbox("Seek", &isSeek))
	{
		if(isSeek)
			mModule->SetBehaviour(SteeringType::Seek, true);
		else
			mModule->SetBehaviour(SteeringType::Seek, false);
	}
	if (ImGui::Checkbox("Arrive", &isArrive))
	{
		if (isArrive)
			mModule->SetBehaviour(SteeringType::Arrive, true);
		else
			mModule->SetBehaviour(SteeringType::Arrive, false);
	}
	if (ImGui::Checkbox("Wander", &isWander))
	{
		if (isWander)
			mModule->SetBehaviour(SteeringType::Wander, true);
		else
			mModule->SetBehaviour(SteeringType::Wander, false);
	}
	if (ImGui::Checkbox("Wander", &isWander))
	{
		if (isWander)
			mModule->SetBehaviour(SteeringType::Wander, true);
		else
			mModule->SetBehaviour(SteeringType::Wander, false);
	}

	if (isSeek)
		Seek();
	if (isArrive)
		Arrive();
	if (isWander)
		Wander();


	ImGui::End();
}

void Vishv::UI::SteeringTool::Seek()
{
	if (ImGui::DragFloat4("Target", &mTarget.x, 0.1f))
	{
		a->path.front() = mTarget;
	}
}

void Vishv::UI::SteeringTool::Arrive()
{
	if (ImGui::DragFloat4("Target", &mTarget.x, 0.1f))
	{
		a->path.front() = mTarget;
	}
}

void Vishv::UI::SteeringTool::Wander()
{
}

void Vishv::UI::SteeringTool::SimpleDraw()
{
	//target
	SimpleDraw::AddSphere(mTarget, 0.5f, Colors::BurlyWood, 6,6);


	SimpleDraw::AddSphere(a->transform.Position() + (a->transform.Forward() * (a->safeDistanceMin * a->safeDistanceSteps)), a->safeDistanceSteps * 4, Colors::Crimson, 5, 5);
	SimpleDraw::AddSphere(a->wanderTarget, 0.2f, Colors::CornflowerBlue, 3, 3);

}


