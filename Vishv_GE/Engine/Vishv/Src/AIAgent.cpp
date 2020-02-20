#include "Precompiled.h"
#include "AIAgent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameWorld.h"

using namespace Vishv;
using namespace Components;


META_DERIVED_BEGIN(AIAgent, Component)
META_FIELD_BEGIN
	//	META_FIELD(mWorld, "AIWorld")
		META_FIELD(mSafeDistance, "SafeDistance")
		META_FIELD(mSafeDistanceIncrementValue, "SafeDistanceIncrementValue")
		META_FIELD(mIsOnSurface, "IsOnSurface")
	META_FIELD_END
META_CLASS_END


void Vishv::Components::AIAgent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mWorld = &GetOwner().GetWorld().GetAIWorld();
}

void Vishv::Components::AIAgent::Update(float deltaTime)
{
	UpdateNearByAgents();
	FindNearByAgents();
}

void Vishv::Components::AIAgent::SimpleDraw()
{
}

void Vishv::Components::AIAgent::DebugUI()
{
	if (!ImGui::CollapsingHeader("AIAgent"))
		return;

	ImGui::DragFloat("Max Speed", &mMaxSpeed, 1.0f);
	ImGui::DragFloat("Mass", &mMass, 1.0f);

	ImGui::DragFloat3("Target", &mTarget.x);

	ImGui::DragFloat("Safe Distance", &mSafeDistance, 1.0f);
	ImGui::DragFloat("Safe Distance Increment", &mSafeDistanceIncrementValue, 0.10f);

	ImGui::Checkbox("On Surface", &mIsOnSurface);
}

void Vishv::Components::AIAgent::Render()
{
}

void Vishv::Components::AIAgent::Terminate()
{
}

float Vishv::Components::AIAgent::CalucalteLengthValue(float bufferValue)
{
	return mSafeDistance + (mSafeDistanceIncrementValue * bufferValue);
}

void Vishv::Components::AIAgent::UpdateNearByAgents()
{
	size_t count = 0;
	float neighbourDistance = CalucalteLengthValue(mNeighbourDistanceBuffer);

	for (auto nearBy : mMyNearbyAgents)
	{
		if (Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(nearBy->Position() - Position())) < neighbourDistance* neighbourDistance)
			continue;

		for (size_t i = 0; i < nearBy->mMyNearbyAgents.size(); ++i)
		{
			if (*nearBy->mMyNearbyAgents[i] == *this)
			{
				nearBy->mMyNearbyAgents.erase(nearBy->mMyNearbyAgents.begin() + i);
				break;
			}
		}

		if (count < mMyNearbyAgents.size())
			mMyNearbyAgents.erase(mMyNearbyAgents.begin() + count);


		count++;
	}
}

void Vishv::Components::AIAgent::FindNearByAgents()
{
	auto agents = mWorld->GetAgents();
	float neighbourDistance = CalucalteLengthValue(mNeighbourDistanceBuffer);
	for (size_t index = 0; index < agents.size(); ++index)
	{
		if (*agents[index] == *this)		//this needs work
			continue;

		bool isThere = false;
		for (size_t i = 0; i < mMyNearbyAgents.size(); ++i)
			if (mMyNearbyAgents[i]->mIndex == agents[index]->mIndex)
			{
				isThere = true;
				break;
			}
		if (isThere)
			continue;

		if (Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(agents[index]->Position() - Position())) > neighbourDistance* neighbourDistance)
			continue;

		agents[index]->mMyNearbyAgents.push_back(this);
		mMyNearbyAgents.push_back(agents[index]);
	}
}

const Math::Vector3& Vishv::Components::AIAgent::Position()
{
	return mTransformComponent->Position();
}

const Math::Vector3& Vishv::Components::AIAgent::Forward()
{
	return mTransformComponent->Forward();
}

