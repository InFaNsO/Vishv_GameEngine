#include "MainState.h"
#include "AttackState.h"
#include "ChaseState.h"
#include "WanderState.h"
#include "DyingState.h"
#include "EmptyState.h"
#include "EnemyStates.h"
#include "AnimationStates.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "MetaRegistration.h"

#include "ObjectTags.h"

using namespace Vishv;
using namespace Math;
using namespace Graphics;

void MainState::InitEnemies()
{
	mEnemies.resize(maxEnemies);
	std::filesystem::path p;


	for (size_t i = 0; i < maxEnemies; ++i)
	{
		std::string name = "Enemy "+ std::to_string(i);
		mEnemies[i] = mGameWorld.Create(p, std::move(name));
		mEnemies[i].Get()->AddComponent<Components::TransformComponent>();
		mEnemies[i].Get()->AddComponent<Components::AIAgent>();
		mEnemies[i].Get()->AddComponent<Components::AIStateMachine>();
		mEnemies[i].Get()->AddComponent<Components::AISteering>();
		mEnemies[i].Get()->AddComponent<Components::ModelAnimation>();
		mEnemies[i].Get()->AddComponent<Components::ColliderComponent>();
		mEnemies[i].Get()->AddComponent<HealthComponent>();
		mEnemies[i].Get()->AddComponent<WeaponComponent>();

		mGameWorld.Register(*mEnemies[i].Get());
	}
}

void MainState::InitAnimEnemy()
{
	AnimationIO aio;

	std::filesystem::path path = "..\\..\\Assets\\3D_Models\\VishMesh\\Zombie";

	mAnimationsSetEnemy.animationClips.resize((size_t)AnimationStates::max);

	for (size_t i = 0; i < (size_t)AnimationStates::max; ++i)
		mAnimationsSetEnemy.animationClips[i] = nullptr;

	mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Idle] = std::make_unique<AnimationClip>();
	aio.LoadAnimation(path / "StandingIdle.vanim", *mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Idle]);
	mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Idle]->isLooping = true;

	mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Attack] = std::make_unique<AnimationClip>();
	aio.LoadAnimation(path / "Attack.vanim", *mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Attack]);

	mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Dying] = std::make_unique<AnimationClip>();
	aio.LoadAnimation(path / "Dying.vanim", *mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Dying]);

	mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Run] = std::make_unique<AnimationClip>();
	aio.LoadAnimation(path / "Run.vanim", *mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Run]);
	mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::Run]->isLooping = true;

	mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::WalkingForward] = std::make_unique<AnimationClip>();
	aio.LoadAnimation(path / "Walking.vanim", *mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::WalkingForward]);
	mAnimationsSetEnemy.animationClips[(size_t)AnimationStates::WalkingForward]->isLooping = true;

	mEnemyModel.animations = &mAnimationsSetEnemy;
}

void MainState::Initialize()
{
	Demo::MetaRegistration();

	mGameWorld.Initialize(150);

	mGameWorld.Register(*scene.sceneCamera);
	InitEnemies();
	InitAnimEnemy();

	mCreator.SetWorld(mGameWorld);

	mPlayerManager.Initialize(&mGameWorld);


	std::filesystem::path path = "..\\..\\Assets\\3D_Models\\VishMesh\\Brute";
	std::string modelName = "Brute";
	mPathFinding = mGameWorld.Create(path, "PathFinding");
	mPathFinding.Get()->AddComponent<Components::AIPathFinding>();
	mPathFinding.Get()->Initialize();
	mGameWorld.Register(*mPathFinding.Get());

	path = "..\\..\\Assets\\3D_Models\\VishMesh\\Zombie";
	modelName = "Zombie";

	for (auto& enemy : mEnemies)
	{
		enemy.Get()->Initialize();

		auto stateMachine = enemy.Get()->GetComponent<Components::AIStateMachine>();
		stateMachine->AddState<EmptyState>(std::move(ToString(EnemyStates::Empty)));
		stateMachine->AddState<WanderState>(std::move(ToString(EnemyStates::Wander)));
		stateMachine->AddState<ChaseState>(std::move(ToString(EnemyStates::Chase)));
		stateMachine->AddState<AttackState>(std::move(ToString(EnemyStates::Attack)));
		stateMachine->AddState<DyingState>(std::move(ToString(EnemyStates::Dying)));

		auto animation = enemy.Get()->GetComponent<Components::ModelAnimation>();
		animation->Set(path, modelName, mAnimationsSetEnemy);

		enemy.Get()->GetComponent<Components::ColliderComponent>()->SetTag((int)ObjectTags::Enemy);
		enemy.Get()->GetComponent<Components::TransformComponent>()->SwitchForard();
	}


	scene.sceneCamera->transform.mPosition = mPlayerManager.mTransform->Position();
	scene.sceneCamera->transform.mPosition += mPlayerManager.mTransform->Forward()* -1.0f * 100.0f;
	scene.sceneCamera->LookAt(mPlayerManager.mTransform->Position());
}

void MainState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
	mPlayerManager.Update(deltaTime);
}

void MainState::RenderSimpleDraw()
{
	mGameWorld.SimpleDraw();
}

void MainState::RenderDebugUI()
{
	mGameWorld.DebugUI();
	mCreator.DebugUI();
}


void MainState::Render()
{
	mGameWorld.Render();
}


void MainState::Terminate()
{
	mGameWorld.Terminate();
}




