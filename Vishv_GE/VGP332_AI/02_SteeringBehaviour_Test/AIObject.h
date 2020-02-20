#pragma once

#include"Vishv/Inc/Vishv.h"

enum class States
{
	wander,
	go,
	attack,
	die
};

struct AiObject
{
	AiObject()
		:aiAgent(Vishv::AI::Agent())
		,mSteeringModule(aiAgent)
		,mStateMachine(*this)
	{
	}

	AiObject(const AiObject&) = delete;
	AiObject& operator=(const AiObject&) = delete;

	AiObject(AiObject&&) = default;
	AiObject& operator=(AiObject&&) = default;

	Vishv::Graphics::Object3D object;
	Vishv::AI::Agent aiAgent;

	Vishv::AI::SteeringModule mSteeringModule;
	Vishv::AI::GraphSearch mPathFinder;

	Vishv::AI::FSM::StateMachine<AiObject, States> mStateMachine;

	void ChangeState(States stateName)
	{
		mStateMachine.ChangeState(stateName);
	}

	void Update(float deltaTime)
	{
		//if agent near destination find new path
		aiAgent.velocity = mSteeringModule.Calculate() * deltaTime;
		auto proj = aiAgent.velocity.Project(aiAgent.transform.Forward());// aiAgent.transform.Forward().Project(aiAgent.velocity);
		
		if (aiAgent.path.size() > 0)
		{
			auto target = aiAgent.path[0];

		}

		//Use Slerp to find rotation
		//aiAgent.transform.RotateX(proj.x);
		//aiAgent.transform.RotateY(proj.y);
		//aiAgent.transform.RotateZ(proj.z);
		proj = aiAgent.velocity - proj;
		aiAgent.transform.mPosition += proj;

	}

	void DebugUI(int index)
	{
		std::string title = "AI Object ";
		title += index;

		if (!ImGui::CollapsingHeader(title.c_str()))
			return;
		ImGui::DragFloat3("Position##AGENTSET", &aiAgent.transform.mPosition.x, 0.1f);
		ImGui::DragFloat3("Velocity##AGENTSET", &aiAgent.velocity.x, 0.1f);
		ImGui::DragFloat("Mass##AGENTSET", &aiAgent.mass, 0.1f);
		ImGui::DragFloat("Safe Distance##AGENTSET", &aiAgent.safeDistanceMin, 0.1f);
		ImGui::DragFloat("Safe Distance Steps##AGENTSET", &aiAgent.safeDistanceSteps, 0.1f);
		ImGui::DragFloat("Neighbour Distance##AGENTSET", &aiAgent.safeDistanceSteps, 0.1f);
		ImGui::DragFloat("Max Speed##AGENTSET", &aiAgent.maxSpeed, 0.1f);
		ImGui::Checkbox("Is on flat surface##AGENTSET", &aiAgent.isOnFlatSurface);
	}
	void SimpleDraw()
	{
		Vishv::Graphics::SimpleDraw::AddSphere(aiAgent.transform.mPosition, 1.0f, Vishv::Graphics::Colors::Gainsboro, 10, 10);
		Vishv::Graphics::SimpleDraw::AddSphere(aiAgent.transform.Position() + (aiAgent.transform.Forward() * (aiAgent.safeDistanceMin * aiAgent.safeDistanceSteps)), aiAgent.safeDistanceSteps * 4, Vishv::Graphics::Colors::Crimson, 5, 5);
		Vishv::Graphics::SimpleDraw::AddSphere(aiAgent.wanderTarget , 0.5f, Vishv::Graphics::Colors::BlueViolet, 5, 5);
	}

private:
	Vishv::Math::Quaternion mTargetQuaternion;
};
