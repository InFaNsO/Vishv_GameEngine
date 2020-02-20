#include "PlayerManager.h"
#include "AnimationStates.h"
#include "ObjectTags.h"

using namespace Vishv;

void PlayerManager::InitPlayerAnim()
{
	Vishv::Graphics::AnimationIO aio;

	std::filesystem::path path = "..\\..\\Assets\\3D_Models\\VishMesh\\Brute";

	mAnimationsSetPlayer.animationClips.resize((size_t)AnimationStates::max);

	for (size_t i = 0; i < (size_t)AnimationStates::max; ++i)
		mAnimationsSetPlayer.animationClips[i] = nullptr;

	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::Idle] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / "StandingIdle.vanim", *mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::Idle]);
	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::Idle]->isLooping = true;

	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::Attack] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / "Attack.vanim", *mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::Attack]);

	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::WalkBackward] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / "WalkBackward.vanim", *mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::WalkBackward]);
	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::WalkBackward]->isLooping = true;

	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::Run] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / "Run.vanim", *mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::Run]);
	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::Run]->isLooping = true;

	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::WalkingForward] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / "WalkForward.vanim", *mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::WalkingForward]);
	mAnimationsSetPlayer.animationClips[(size_t)AnimationStates::WalkingForward]->isLooping = true;
}

void PlayerManager::Initialize(Vishv::GameWorld * world)
{
	InitPlayerAnim();
	mWorld = world;
	std::filesystem::path p;
	
	mPlayer = mWorld->Create(p, "Player");

	mTransform = mPlayer.Get()->AddComponent< Vishv::Components::TransformComponent>();
	mModelAnimation = mPlayer.Get()->AddComponent<Vishv::Components::ModelAnimation>();
	mCollider = mPlayer.Get()->AddComponent<Vishv::Components::ColliderComponent>();
	mController = mPlayer.Get()->AddComponent<Vishv::Components::ThirdPersonControllerComponent>();

	mHealth = mPlayer.Get()->AddComponent<HealthComponent>();
	mWeapon = mPlayer.Get()->AddComponent<WeaponComponent>();

	world->Register(*mPlayer.Get(), true);
	mPlayer.Get()->Initialize();

	std::filesystem::path path = "..\\..\\Assets\\3D_Models\\VishMesh\\Brute";
	std::string modelName = "Brute";

	mModelAnimation->Set(path, modelName, mAnimationsSetPlayer);
	mModelAnimation->ChangeAnimation((size_t)AnimationStates::Idle);
	mTransform->GetPosition() = { 500.0f, 0.0f, 200.0f };
	mTransform->SwitchForard();
	mCollider->SetTag((int)ObjectTags::Player);

	mAttackDuration = mModelAnimation->GetAnimationDuration((int)AnimationStates::Attack);
}

void PlayerManager::Update(float deltaTime)
{
	//mPlayer.Update(deltaTime);

	auto input = Vishv::Input::InputSystem::Get();

	if (input->IsKeyDown(Input::KeyCode::W) && input->IsKeyDown(Input::KeyCode::LSHIFT))
	{
		if (mModelAnimation->CurrentrAnimation() != (int)AnimationStates::Run && !mModelAnimation->IsNextAnim())
		{
			mModelAnimation->ChangeAnimation((size_t)AnimationStates::Run);
		}
	}
	else if (input->IsKeyDown(Input::KeyCode::W))
	{
		if (mModelAnimation->CurrentrAnimation() != (int)AnimationStates::WalkingForward && !mModelAnimation->IsNextAnim())
		{
			mModelAnimation->ChangeAnimation((size_t)AnimationStates::WalkingForward);
		}
	}
	else if (input->IsKeyDown(Input::KeyCode::S))
	{
		if (mModelAnimation->CurrentrAnimation() != (int)AnimationStates::WalkBackward && !mModelAnimation->IsNextAnim())
		{
			mModelAnimation->ChangeAnimation((size_t)AnimationStates::WalkBackward);
		}
	}
	else if (input->IsMousePressed(Input::MouseButton::LBUTTON))
	{
		mAttackTimer += 1.0f;
		if (mAttackTimer > mAttackDuration)
		{
			mModelAnimation->ChangeAnimation((int)AnimationStates::Attack);
			attacked = true;
			mAttackTimer = 0.0f;
		}
		else if (mAttackTimer > mAttackDuration * 0.65f &&  mAttackTimer < mAttackDuration * 0.75f && attacked)
		{
			auto col = mCollider->GetCollisions((int)ObjectTags::Enemy);
			if (col.size() > 0)
			{
				for (auto& enem : col)
				{
					mWeapon->Use(*enem->GetComponent<HealthComponent>());
				}
				attacked = false;
			}
		}
	}
	else
	{
		if (!mModelAnimation->IsNextAnim())
		{
			mModelAnimation->ChangeAnimation((size_t)AnimationStates::Idle);
		}
	}

}

void PlayerManager::SimpleDraw()
{
	//mPlayer.SimpleDraw();
}

void PlayerManager::DebugUI()
{
	//mPlayer.DebugUI();
}

void PlayerManager::Render()
{
	//mPlayer.Render();
}

void PlayerManager::Terminate()
{
	//mPlayer.Terminate();
	mWorld->Destroy(mPlayer);
}

