#pragma once
#include "Vishv/Inc/Vishv.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"

class AttackState : public Vishv::AI::FSM::State<Vishv::GameObject>
{
public:
	void Enter(Vishv::GameObject& agent) override;
	void Update(Vishv::GameObject& agent, float deltaTime) override;
	void Exit(Vishv::GameObject& agent) override;

private:
	void FacePlayer(float deltaTime);

	Vishv::Components::TransformComponent* mTransformComponent;
	Vishv::Components::TransformComponent* mPlayerTransformComponent;

	Vishv::Components::ModelAnimation* mAnimation;

	Vishv::Components::ColliderComponent* mColliderComponent;

	size_t mAttackAnimIndex;

	float mAttackDuration;
	float mTimer = 0.0f;

	HealthComponent* mPlayerHealth;
	HealthComponent* mHealth;

	float mDetectionRange;
	float mAttackRange;
	float attackUp = 90.0f;
	float detectionUp = 500.0f;

	WeaponComponent* mWeapon;

	bool attacked = false;
	float prvDeg = 0.0f;
};

