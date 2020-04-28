#include "Precompiled.h"
#include "AISteering.h"

#include "TransformComponent.h"
#include "AIAgent.h"

#include "SteeringBehaviour_Arrive.h"
#include "SteeringBehaviour_Evade.h"
#include "SteeringBehaviour_Flee.h"
#include "SteeringBehaviour_Flocking.h"
#include "SteeringBehaviour_ObstacleAvoidance.h"
#include "SteeringBehaviour_Pursuit.h"
#include "SteeringBehaviour_Seek.h"
#include "SteeringBehaviour_Wander.h"


using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(AISteering, Component)
META_FIELD_BEGIN
		//META_FIELD(mSteeringModule, "SteeringModule")		Get the template version working ASAP
	META_FIELD_END
META_CLASS_END

void Vishv::Components::AISteering::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mAiAgentComponent = GetOwner().GetComponent<AIAgent>();

	mSteeringModule.Initialize(*mAiAgentComponent);
	mSteeringModule.AddBehaviour<Vishv::AI::Steering::Arrive>();
	mSteeringModule.AddBehaviour<Vishv::AI::Steering::Evade>();
	mSteeringModule.AddBehaviour<Vishv::AI::Steering::Flee>();
	mSteeringModule.AddBehaviour<Vishv::AI::Steering::Flocking>();
	mSteeringModule.AddBehaviour<Vishv::AI::Steering::ObstacleAvoidance>();
	mSteeringModule.AddBehaviour<Vishv::AI::Steering::Pursuit>();
	mSteeringModule.AddBehaviour<Vishv::AI::Steering::Seek>();
	mSteeringModule.AddBehaviour<Vishv::AI::Steering::Wander>();
}

void Vishv::Components::AISteering::Update()
{
	auto vel = mSteeringModule.Calculate() * Core::Time::Get()->DeltaTime();
	if (vel != Math::Vector3(0.0f))
	{
		mTransformComponent->RotateUp(vel.GetAngle(mTransformComponent->Forward()));
		mTransformComponent->GetPosition() += vel;
	}
}

void Vishv::Components::AISteering::DebugUI()
{
	//show active behaviours and allow to set other
}

void Vishv::Components::AISteering::Terminate()
{
	mSteeringModule.Purge();
}

void Vishv::Components::AISteering::SetBehaviour(AI::SteeringType type, bool set)
{
	mSteeringModule.SetBehaviour(type, set);
}

