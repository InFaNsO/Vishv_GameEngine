#pragma once
#include "Vishv/Inc/Vishv.h"
#include "HealthComponent.h"

class WanderState : public Vishv::AI::FSM::State<Vishv::GameObject>
{
public:
	void Enter(Vishv::GameObject& agent) override;
	void Update(Vishv::GameObject& agent, float deltaTime) override;
	void Exit(Vishv::GameObject& agent) override;

	void DebugUI(Vishv::GameObject& agent) override;
	void SimpleDraw(Vishv::GameObject& agent) override;

private:
	std::vector<Vishv::Math::Vector3> wanderPath;
	Vishv::Math::Vector3 mTarget;

	float debugNodeSize = 2.0f;
	bool isLooping = false;		//used if path is traversed like a pendulum or looped

	Vishv::Components::TransformComponent* mTransformComponent;
	Vishv::Components::ModelAnimation* mAnimationComponent;
	Vishv::Components::AIAgent* mAgentComponent;
	Vishv::Components::AISteering * mSteeringComponent;
	Vishv::Components::AIPathFinding* mPathFinding;
	HealthComponent* mHealthComponent;
	Vishv::GameWorld* mGameWorld;

	Vishv::Components::TransformComponent* playerTransform;

	float mDetectionRange;
	float mAttackRange;
	float mNodeMaxDistance;

	float attackUp = 90.0f;
	float detectionUp = 155.0f;
	float nodeUp = 105.0f;

	int mCurrentPathNode;
};

