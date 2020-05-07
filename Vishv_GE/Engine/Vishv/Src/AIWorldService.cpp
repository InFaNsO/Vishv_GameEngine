#include "Precompiled.h"
#include "AIWorldService.h"

#include "GameObject.h"
#include "AIAgent.h"

#include "OBBColliderComponent.h"
#include "CapsuleColliderComponent.h"

using namespace Vishv;

META_DERIVED_BEGIN(AIWorld, Service)
	META_FIELD_BEGIN
		//META_FIELD(mAgents, "Agents")
	META_FIELD_END
META_CLASS_END


void Vishv::AIWorld::Initialize()
{
	SetName("AI World");
}

void Vishv::AIWorld::Terminate()
{
}

void Vishv::AIWorld::Update()
{
}

void Vishv::AIWorld::Render()
{
}

void Vishv::AIWorld::DebugUI()
{
}

void Vishv::AIWorld::Register(GameObject& object)
{
	auto agent = object.GetComponent<Components::AIAgent>();
	if (agent)
	{
		mAgents.emplace_back(agent);
		return;
	}
	auto wall = object.GetComponent<Components::OBBCollider>();
	if(wall)
	{
		if (wall->IsStatic() && !wall->IsTrigger())
			mWalls.emplace_back(wall);
		return;
	}
	auto obs = object.GetComponent<Components::CapsuleCollider>();
	if (obs)
	{
		if (obs->IsStatic() && !obs->IsTrigger())
			mObstacles.emplace_back(obs);
		return;
	}
}

void Vishv::AIWorld::RegisterPlayer(GameObject& object)
{
	mPlayers.emplace_back(&object);
}

std::vector<Components::AIAgent*> Vishv::AIWorld::GetAgents()
{
	return mAgents;
}
