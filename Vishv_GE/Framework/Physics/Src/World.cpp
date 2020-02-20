#include "Precompiled.h"
#include "World.h"


void Vishv::Physics::World::Initialize(const Settings & setting)
{
	mSettings = setting;
}

void Vishv::Physics::World::Update(float deltaTime)
{
	mTimer += deltaTime;
	while (mTimer > mSettings.deltaTime)
	{
		mTimer -= mSettings.deltaTime;
		//do physics;
	}
}

void Vishv::Physics::World::DebugDraw()
{
	using namespace Vishv::Graphics;

	for (auto p : mParticles)
		SimpleDraw::AddSphere(p->position, p->radius, Colors::Aqua, 6, 6);
}

void Vishv::Physics::World::AddParticle(Particle * p)
{
	mParticles.push_back(p); //improve
}

void Vishv::Physics::World::AccumilateForce()
{
	for (auto p : mParticles)
		p->acceleration = mSettings.gravity;
}

void Vishv::Physics::World::ClearDynamic()
{
	for (auto p : mParticles)
		delete p;
	mParticles.clear();
}

void Vishv::Physics::World::Integrate()
{
	const float gamma = 1.0f - mSettings.drag;
	const float timeStepSqr = mSettings.deltaTime * mSettings.deltaTime;
	for (auto p : mParticles)
	{
		Math::Vector3 displacement = (p->position - p->latsPosition) * gamma + (p->acceleration * mSettings.deltaTime);
	}

}

void Vishv::Physics::World::SatisfyConstraints()
{
}


/*
#include "RigidBody.h"
#include "Particle.h"


using namespace Vishv;
using namespace Vishv::Math;
using namespace Vishv::Physics;


namespace
{
	std::unique_ptr<World> sPhysicsWorld = nullptr;
}

void Vishv::Physics::World::StaticInitialize()
{
	VISHVASSERT(sPhysicsWorld == nullptr, "[Vishv::Physics::World::StaticInitialize] Already static Initialized");

	sPhysicsWorld = std::make_unique<World>();
}

void Vishv::Physics::World::StaticTerminate()
{
	if (sPhysicsWorld != nullptr)
	{
		sPhysicsWorld = nullptr;
	}
}

World * Vishv::Physics::World::Get()
{
	return sPhysicsWorld.get();
}

Particle * Vishv::Physics::World::GetParticle(ParticleID particle)
{
	if (auto it = mParticles.find(particle);
		it != mParticles.end())
	{
		return it->second.get();
	}
	LOG("failed to find particle id %i", (int)particle);
	return nullptr
;
}

RigidBody * Vishv::Physics::World::GetRigidBody(RigidBodyID body)
{
	if (auto it = mBodies.find(body);
		it != mBodies.end())
	{
		return it->second.get();
	}

	LOG("failed to find particle id %i", (int)body);
	return nullptr;
}

void Vishv::Physics::World::Reset()
{
	for (auto& body : mBodies)
	{
		body.second->ClearAccumilators();
		body.second->CalculateDerivedData();
	}
}

void Vishv::Physics::World::Update(float deltaTime)
{
	mRegistry.Update(deltaTime);

	for (auto& body : mBodies)
	{
		body.second->Integrate(deltaTime);
	}

	for (auto& particle : mParticles)
	{
		particle.second->Update(deltaTime);
	}
}

bool Vishv::Physics::World::AddForceGenerator(std::shared_ptr<ForceGenerator::ForceGenerator> forceGen)
{
	return mRegistry.AddForceGenerator(forceGen);
}

bool Vishv::Physics::World::RemoveForceGenerator(std::string generatorName)
{
	return mRegistry.RemoveForceGenerator(std::move(generatorName));
}

RigidBodyID Vishv::Physics::World::AddRigidBody(std::unique_ptr<RigidBody> body, std::string name)
{
	int seed = 0;
	RigidBodyID hash;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1,10000); // distribution in range [1, 10000]
	seed = dist(rng);
	std::hash<int>gen;
	hash = gen(seed);
	

	if (mBodies.find(hash) == mBodies.end())
	{
		mBodies.emplace(hash, std::move(body));
	}
	return hash;
}

ParticleID Vishv::Physics::World::AddParticle(std::unique_ptr<Particle> particle, int seed)
{
	VISHVASSERT(seed >= 0 && seed < 10000, "Seed has to be between 1 & 10000");

	if (seed == 0)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10000); // distribution in range [1, 10000]
		seed = dist(rng);
	}
	std::hash<int>gen;

	ParticleID hash = gen(seed);
	if (mParticles.find(hash) == mParticles.end())
	{
		mParticles.emplace(hash, std::move(particle));
	}
	else
	{
		//LOG("Seed: %i already exists." seed);
		return 0;
	}

	return hash;
}

bool Vishv::Physics::World::AddParticleToRegistry(ParticleID particleID, std::string genratorName)
{
	if (auto it = mParticles.find(particleID);
		it != mParticles.end())
	{
		return mRegistry.AddParticle(particleID, genratorName);
	}

	LOG("failed to find particle id %i", (int)particleID);
	return false;
}

bool Vishv::Physics::World::RemoveParticleFromRegistry(ParticleID particleID, std::string genratorName)
{
	if (auto it = mParticles.find(particleID);
		it != mParticles.end())
	{
		return mRegistry.RemoveParticle(particleID, genratorName);
	}

	LOG("failed to find particle id %i", (int)particleID);
	return false;
}

bool Vishv::Physics::World::AddRigidBodyToRegistry(RigidBodyID bodyID, std::string genratorName)
{
	if (auto it = mBodies.find(bodyID);
		it != mBodies.end())
	{
		return mRegistry.AddRigidBody(bodyID, genratorName);
	}

	LOG("failed to find particle id %i", (int)bodyID);
	return false;
}

bool Vishv::Physics::World::RemoveRigidBodyFromRegistry(RigidBodyID bodyID, std::string genratorName)
{
	if (auto it = mBodies.find(bodyID);
		it != mBodies.end())
	{
		return mRegistry.RemoveRigidBody(bodyID, genratorName);
	}

	LOG("failed to find particle id %i", (int)bodyID);
	return false;
}

void Vishv::Physics::World::ClearForceRegistry()
{
	mRegistry.Clear();
}
*/

