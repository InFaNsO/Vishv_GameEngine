#pragma once
#include <Vishv/Inc/Vishv.h>
#include "PlayerManager.h"
#include "GameWorldCreator.h"

class MainState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;

	void Render() override;

	void RenderDebugUI() override;

	void Terminate() override;
	void RenderSimpleDraw() override;
private:
	void InitEnemies();
	void InitAnimEnemy();

	//Vishv::Graphics::Object3D mPlayerObject;
	//Vishv::AI::Agent mPlayerAI;
	//
	//std::vector<std::unique_ptr<DemoObject>> mEnemies;
	std::vector<Vishv::GameObjectHandle> mEnemies;
	PlayerManager mPlayerManager;
	GameWorldCreator mCreator;
	size_t maxEnemies = 2;
	Vishv::GameWorld mGameWorld;
	
	Vishv::GameObjectHandle mPathFinding;

	Vishv::Graphics::RiggedModel mEnemyModel;
	
	Vishv::Graphics::AnimationSet mAnimationsSetEnemy;

	bool isRunningSimulation = false;

	Vishv::GameObjectHandle testLoader;
};

