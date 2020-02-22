#include "AttackState.h"
#include "EnemyStates.h"
#include "AnimationStates.h"

#include "ObjectTags.h"

void AttackState::Enter(Vishv::GameObject & agent)
{
	mTransformComponent = agent.GetComponent<Vishv::Components::TransformComponent>();
	mHealth = agent.GetComponent<HealthComponent>();
	mAnimation = agent.GetComponent<Vishv::Components::ModelAnimation>();
	mWeapon = agent.GetComponent<WeaponComponent>();
	mColliderComponent = agent.GetComponent<Vishv::Components::ColliderComponent>();

	auto player = agent.GetWorld().Player();
	
	mPlayerTransformComponent = player->GetComponent<Vishv::Components::TransformComponent>();
	mPlayerHealth = player->GetComponent<HealthComponent>();

	auto mAgentComponent = agent.GetComponent<Vishv::Components::AIAgent>();

	mAttackRange = mAgentComponent->CalucalteLengthValue(attackUp);
	mDetectionRange = mAgentComponent->CalucalteLengthValue(detectionUp);

	mAttackAnimIndex = (size_t)AnimationStates::Attack;
	mTimer = 0.0f;
	mAttackDuration = mAnimation->GetAnimationDuration(mAttackAnimIndex);
}

void AttackState::Update(Vishv::GameObject & agent, float deltaTime)
{
	if (!mHealth->IsAlive())
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Dying));
		return;
	}
	
	float playerDisSq = Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(mTransformComponent->Position() - mPlayerTransformComponent->Position()));
	if (playerDisSq > mAttackRange * mAttackRange&& playerDisSq < mDetectionRange * mDetectionRange)
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Chase));
		return;
	}
	else if (playerDisSq > mDetectionRange * mDetectionRange)
	{
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Wander));
		return;
	}

	FacePlayer(deltaTime);

	if (!mAnimation->IsNextAnim())
		mAnimation->ChangeAnimation((size_t)AnimationStates::Idle);

	mTimer += 1.0f;
	if (mTimer > mAttackDuration)
	{
		mAnimation->ChangeAnimation(mAttackAnimIndex);
		attacked = true;
		mTimer = 0.0f;
	}
	else if (mTimer > mAttackDuration * 0.65f &&  mTimer < mAttackDuration * 0.75f && attacked)
	{
		if (mColliderComponent->IsColliding((int)ObjectTags::Player))
		{
			mWeapon->Use(*mPlayerHealth);
			attacked = false;
		}
	}

	//face the player
	auto tar = Vishv::Math::Normalize((mTransformComponent->Position() - mPlayerTransformComponent->Position()));
	float angle = Vishv::Math::GetAngle(tar, mTransformComponent->Forward());

	if (angle)
	{
		float deg = angle * Vishv::Math::Constans::RadToDeg;

		if (Vishv::Math::Abs(deg - prvDeg) < 0.01f)
			return;

		if (tar.x < mTransformComponent->Forward().x)
			deg *= -1.0f;

		prvDeg = deg;
		mTransformComponent->RotateUp(deg * deltaTime);
	}
}

void AttackState::FacePlayer(float deltaTime)
{
	mTransformComponent->RotateUp(Vishv::Math::Vector3::GetAngle(mTransformComponent->Forward(), (mTransformComponent->Position() - mPlayerTransformComponent->Position())) * deltaTime);
}

void AttackState::Exit(Vishv::GameObject & agent)
{
}
