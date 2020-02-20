#pragma once
#include "Vishv/Inc/Vishv.h"

class GameWorldCreator
{
public:
	void SetWorld(Vishv::GameWorld& w);
	void Update(float deltaTime);
	void SimpleDraw();
	void DebugUI();
	void Render();
	void Load(std::filesystem::path p);

private:
	void Save();

	Vishv::GameWorld * mWorld;

	std::vector<Vishv::GameObjectHandle> mGameObjects;
};

