#include "GameState.h"

using namespace Vishv;

void GameState::Initialize()
{
	mPWorld.Initialize();
}

void GameState::Update(float deltaTime)
{
	mPWorld.Update(deltaTime);
}

void GameState::Render()
{

}

void GameState::RenderDebugUI()
{
	ImGui::Begin("Physics World");
	
	static int numParticle = 0;

	if (ImGui::DragInt("Num Particles", &numParticle, 1.0f, (int)mPWorld.GetNumberOfParticles()))
	{
		if (numParticle < (int)mPWorld.GetNumberOfParticles())
			numParticle = (int)mPWorld.GetNumberOfParticles();

		//get size and add remaining
		

	}
	
	if (ImGui::Button("Reset"))
	{
		mPWorld.ClearDynamic();
		for (int i = 0; i < numParticle; ++i)
		{
			auto particle = new Physics::Particle();
			particle->SetPosition(Math::Vector3::Zero);
			particle->SetVelocity({ 0.0f, Math::Random::Float(0.01f, 50.0f), 0.0f });
			particle->radius = 0.1f;
			particle->invMass = 1.0f;
			mPWorld.AddParticle(particle);
		}
	}
}

void GameState::RenderSimpleDraw()
{
	mPWorld.DebugDraw();
}

void GameState::Terminate()
{

}


