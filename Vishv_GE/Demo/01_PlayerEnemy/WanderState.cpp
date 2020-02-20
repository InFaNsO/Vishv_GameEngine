#include "WanderState.h"
#include "EnemyStates.h"
#include "AnimationStates.h"
using namespace Vishv::Graphics;

void WanderState::Enter(Vishv::GameObject & agent)
{
	mTransformComponent = agent.GetComponent<Vishv::Components::TransformComponent>();
	mAnimationComponent = agent.GetComponent<Vishv::Components::ModelAnimation>();

	mAgentComponent = agent.GetComponent<Vishv::Components::AIAgent>();
	mSteeringComponent = agent.GetComponent<Vishv::Components::AISteering>();
	mHealthComponent = agent.GetComponent<HealthComponent>();

	mGameWorld = &agent.GetWorld();

	playerTransform = mGameWorld->Player()->GetComponent<Vishv::Components::TransformComponent>();
	mPathFinding = mGameWorld->PathFinding()->GetComponent<Vishv::Components::AIPathFinding>();

	VISHVASSERT(mTransformComponent && mAnimationComponent && mAgentComponent && mSteeringComponent, "[Wander State] agent doesnt have necessary components");

	mTarget = mPathFinding->GetRandomNodePos();
	wanderPath = mPathFinding->RunAStar(mTransformComponent->Position(), mTarget);

	//agent.ResetSteering();
	//agent.SetSteeringBehaviour(AI::SteeringType::Arrive, true);
	//agent.GetAiAgent().path.clear();
	//agent.GetAiAgent().path = wanderPath;
	//agent.SetNextAnimation(AnimationMovement::WalkForward);

	mSteeringComponent->ResetModule();
	mSteeringComponent->SetBehaviour(Vishv::AI::SteeringType::Seek, true);

	mAttackRange = mAgentComponent->CalucalteLengthValue(attackUp);
	mDetectionRange = mAgentComponent->CalucalteLengthValue(detectionUp);
	mNodeMaxDistance = mAgentComponent->CalucalteLengthValue(nodeUp);

	mAgentComponent->Target() = wanderPath[mCurrentPathNode];

	agent.GetComponent<Vishv::Components::ModelAnimation>()->ChangeAnimation((size_t)AnimationStates::WalkingForward);
}

void WanderState::Update(Vishv::GameObject & agent, float deltaTime)
{
	if (wanderPath[mCurrentPathNode] == mTarget)
	{
		mTarget = mPathFinding->GetRandomNodePos();
		wanderPath = mPathFinding->RunAStar(mTransformComponent->Position(), mTarget);

	}

	if (!mHealthComponent->IsAlive())
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Dying));
		return;
	}

	//see if close to player change state 
	//attack
	//go to
	float playerDisSq = Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(mTransformComponent->Position() - playerTransform->Position()));
	if (playerDisSq < mAttackRange * mAttackRange)
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Attack));
		return;
	}
	else if (playerDisSq < mDetectionRange * mDetectionRange)
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Chase));
		return;
	}

	//check if agent is close to path
	float disSq = Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(mTransformComponent->Position() - wanderPath[mCurrentPathNode]));

	if (disSq > mNodeMaxDistance * mNodeMaxDistance)
		return;



	//update the path 
	mCurrentPathNode += 1;
	if ((size_t)mCurrentPathNode >= wanderPath.size())
	{
		mTarget = mPathFinding->GetRandomNodePos();
		wanderPath = mPathFinding->RunAStar(mTransformComponent->Position(), mTarget);

		mCurrentPathNode = 0;
	}
	mAgentComponent->Target() = wanderPath[mCurrentPathNode];

}

void WanderState::Exit(Vishv::GameObject & agent)
{
	mTransformComponent = nullptr;
	mAnimationComponent = nullptr;
	mAgentComponent = nullptr;
	mSteeringComponent = nullptr;
	mGameWorld = nullptr;
	playerTransform = nullptr;
}

void WanderState::DebugUI(Vishv::GameObject & agent)
{
	if (!ImGui::CollapsingHeader("Wander Path"))
		return;
	ImGui::Text("Wander");
	ImGui::DragFloat("Node Radius", &debugNodeSize, 0.1f, 0.5f, 10.0f);
	if(ImGui::Button("Loop Path"))
	{
		isLooping = !isLooping;

		if (isLooping)
		{
			mSteeringComponent->ResetModule();
			mSteeringComponent->SetBehaviour(Vishv::AI::SteeringType::Seek,true);
		}
		else
		{
			mSteeringComponent->ResetModule();
			mSteeringComponent->SetBehaviour(Vishv::AI::SteeringType::Arrive,true);
		}
	}

	for (size_t i = 0; i < wanderPath.size(); ++i)
	{
		std::string name = "Node: " + std::to_string(i);
		ImGui::DragFloat3(name.c_str(), &wanderPath[i].x, 0.1f);
	}

	if (ImGui::Button("Add path node"))
		wanderPath.push_back(Vishv::Math::Vector3());
	
	if(ImGui::DragFloat("Attack_UP", &attackUp))
		mAttackRange = mAgentComponent->CalucalteLengthValue(attackUp);
	if (ImGui::DragFloat("Detection_UP", &detectionUp))
		mDetectionRange = mAgentComponent->CalucalteLengthValue(detectionUp);
	if (ImGui::DragFloat("Node_UP", &nodeUp))
		mNodeMaxDistance = mAgentComponent->CalucalteLengthValue(nodeUp);


}

void WanderState::SimpleDraw(Vishv::GameObject & agent)
{
	SimpleDraw::AddSphere(mTransformComponent->Position(), mAttackRange, Colors::Maroon, 5, 5);
	SimpleDraw::AddSphere(mTransformComponent->Position(), mDetectionRange, Colors::CornflowerBlue, 5, 5);
	SimpleDraw::AddSphere(mTransformComponent->Position(), mNodeMaxDistance, Colors::Wheat, 5, 5);

	for (size_t i = 0; i < wanderPath.size(); ++i)
	{
		SimpleDraw::AddSphere(wanderPath[i], debugNodeSize, Colors::Honeydew, 5, 5);
		if (i != wanderPath.size() - 1)
			SimpleDraw::AddLine(wanderPath[i], wanderPath[i + 1], Colors::CadetBlue);
	}
	if(isLooping)
		SimpleDraw::AddLine(wanderPath[wanderPath.size() - 1], wanderPath[0], Colors::CadetBlue);
}

