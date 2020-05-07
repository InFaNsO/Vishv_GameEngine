#include "MainState.h"

void MainState::Initialize()
{
	mGameWorld.AddService<Vishv::PhysicsSystem>();
	mGameWorld.AddService<Vishv::CameraSystem>();
	mGameWorld.AddService<Vishv::AIWorld>();
	mGameWorld.AddService<Vishv::ModelService>();

	mGameWorld.Initialize(10000);
}


