#pragma once
#include "Vishv/Inc/Vishv.h"
#include "WeaponComponent.h"
#include "HealthComponent.h"

class PlayerManager
{
public:
	void Initialize(Vishv::GameWorld* world);
	void Update(float deltaTime);
	void SimpleDraw();
	void DebugUI();
	void Render();
	void Terminate();

private:
	void InitPlayerAnim();

public:
	Vishv::GameWorld* mWorld;

	Vishv::GameObjectHandle mPlayer;

	Vishv::Components::TransformComponent *mTransform;
	Vishv::Components::ColliderComponent *mCollider;
	Vishv::Components::ModelAnimation *mModelAnimation;
	Vishv::Components::ThirdPersonControllerComponent *mController;

	HealthComponent *mHealth;
	WeaponComponent *mWeapon;
	
	Vishv::Graphics::AnimationSet mAnimationsSetPlayer;

	bool attacked = false;
	float mAttackTimer = 0.0f;
	float mAttackDuration = 1.0f;
};


