#pragma once
#include "Vishv/Inc/Vishv.h"
#include "HealthComponent.h"

class ChaseState : public Vishv::AI::FSM::State<Vishv::GameObject>
{
public:
	void Enter(Vishv::GameObject& agent) override;
	void Update(Vishv::GameObject& agent, float deltaTime) override;
	void Exit(Vishv::GameObject& agent) override;

private:
	Vishv::Components::TransformComponent* mTransformComponent;
	Vishv::Components::TransformComponent* mPlayerTransformComponent;

	Vishv::Components::AIAgent* mAgentComponent;
	Vishv::Components::AISteering* mSteeringComponent;

	HealthComponent* mHealth;

	Vishv::Components::AIPathFinding* mPathFinding;

	std::vector<Vishv::Math::Vector3> mPath;

	int mPlayerNode;
	size_t mCurrentPathNode = 0;

	float mDetectionRange;
	float mAttackRange;
	float mNodeMaxDistance;


	float attackUp = 90.0f;
	float detectionUp = 155.0f;
	float nodeUp = 105.0f;

};


