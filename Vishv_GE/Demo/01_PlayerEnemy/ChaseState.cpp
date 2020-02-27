#include "ChaseState.h"
#include "EnemyStates.h"
#include "AnimationStates.h"


using namespace Vishv;

void ChaseState::Enter(Vishv::GameObject & agent)
{
	//Set all the Components
	mTransformComponent = agent.GetComponent<Components::TransformComponent>();
	mSteeringComponent = agent.GetComponent<Components::AISteering>();
	mAgentComponent = agent.GetComponent<Components::AIAgent>();
	mHealth = agent.GetComponent<HealthComponent>();
	mPathFinding = agent.GetWorld().PathFinding()->GetComponent<Components::AIPathFinding>();

	mPlayerTransformComponent = agent.GetWorld().Player()->GetComponent<Components::TransformComponent>();

	//Set All The Ranges
	mAttackRange = 70.0f;// mAgentComponent->CalucalteLengthValue(attackUp);
	mDetectionRange = mAgentComponent->CalucalteLengthValue(detectionUp);
	mNodeMaxDistance = mAgentComponent->CalucalteLengthValue(nodeUp);

	//Set Steering
	mSteeringComponent->ResetModule();
	mSteeringComponent->SetBehaviour(Vishv::AI::SteeringType::Arrive, true);
	agent.GetComponent<Vishv::Components::ModelAnimation>()->ChangeAnimation((size_t)AnimationStates::Run);

	mAgentComponent->MaxSpeed() = mAgentComponent->MaxSpeed() * 1.0f;

	//Path finding
	mPath = mPathFinding->RunAStar(mTransformComponent->Position(), mPlayerTransformComponent->Position());

	mOffsetFromPlayer = mTransformComponent->Position() - mPlayerTransformComponent->Position();
	mOffsetFromPlayer.Normalize();
	mOffsetFromPlayer *= 50.0f;

	mPath.emplace_back(mPlayerTransformComponent->Position() - mOffsetFromPlayer );
	mPlayerNode = mPathFinding->GetNodeID(mPlayerTransformComponent->Position());
	mCurrentPathNode = 0;
	mAgentComponent->Target() = mPath[mCurrentPathNode];

	mTransformComponent->SetRotation(mPlayerTransformComponent->Rotation().GetConjugate());
}

void ChaseState::Update(Vishv::GameObject & agent, float deltaTime)
{
	if (!mHealth->IsAlive())
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Dying));
		return;
	}

	float playerDisSq = Math::Abs(Math::MagnitudeSqr(mTransformComponent->Position() - mPlayerTransformComponent->Position()));
	if (playerDisSq < mAttackRange * mAttackRange || mPath.size() == 0)
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Attack));
		return;
	}
	else if (playerDisSq > mDetectionRange * mDetectionRange)
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Wander));
		return;
	}

	int pnodeId = mPathFinding->GetNodeID(mPlayerTransformComponent->Position());
	if (pnodeId != mPlayerNode)
	{
		mPlayerNode = pnodeId;
		mPath = mPathFinding->RunAStar(mTransformComponent->Position(), mPlayerTransformComponent->Position());
		mCurrentPathNode = 0;
		mPath.emplace_back(mPlayerTransformComponent->Position() - mOffsetFromPlayer);
		mAgentComponent->Target() = mPath[mCurrentPathNode];
	}

	//check if agent is close to path
	float disSq = Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(mTransformComponent->Position() - mPath[mCurrentPathNode]));

	if (disSq > mNodeMaxDistance * mNodeMaxDistance)
		return;

	mCurrentPathNode += 1;
	if ((size_t)mCurrentPathNode >= mPath.size())
	{
		mPath = mPathFinding->RunAStar(mTransformComponent->Position(), mPlayerTransformComponent->Position());
		if(mPath.size() == 0)
			agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Attack));

		mPath.emplace_back(mPlayerTransformComponent->Position() - mOffsetFromPlayer);
		mCurrentPathNode = 0;
	}
	mAgentComponent->Target() = mPath[mCurrentPathNode];
}

void ChaseState::Exit(Vishv::GameObject & agent)
{
	mAgentComponent->MaxSpeed() = mAgentComponent->MaxSpeed() * 1.0f;
}


