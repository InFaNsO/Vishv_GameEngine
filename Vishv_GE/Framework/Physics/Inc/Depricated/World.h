#ifndef INCLUDED_VISHV_PHYSICS_WORLD_H
#define INCLUDED_VISHV_PHYSICS_WORLD_H

#include "Particle.h"

namespace Vishv::Physics
{
	struct Settings
	{
		Math::Vector3 gravity{0.0f, -9.8f, 0.0f};
		float deltaTime = 1.0f / 60.0f;
		float drag = 0.0f;
		int interactions = 1;
	};

	class World
	{
	public:
		void Initialize(const Settings& setting = Settings());

		void Update(float deltaTime);
		void DebugDraw();

		void AddParticle(Particle* p);
		size_t GetNumberOfParticles() { return mParticles.size(); }

		void ClearDynamic();
	private:
		void AccumilateForce();
		void Integrate();
		void SatisfyConstraints();

		std::vector<Particle*> mParticles;

		Settings mSettings;
		float mTimer = 0.0f;
	};
}


/*
#include "ParticleForceGenerator.h"
#include "BoundingVolumeHirarchy.h"
#include "BinarySpacePartitioning.h"

namespace Vishv::Physics {

using RigidBodyID = size_t;
using ParticleID = size_t;

class World
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static World* Get();

public:
	void Reset();
	void Update(float deltaTime);

	RigidBodyID	AddRigidBody	(std::unique_ptr<RigidBody> body, std::string name = '\0');
	ParticleID	AddParticle		(std::unique_ptr<Particle> particle, int seed = 0);

	Particle* GetParticle(ParticleID particle);
	RigidBody* GetRigidBody(RigidBodyID body);

	//functions for registry
	bool AddForceGenerator				(std::shared_ptr<ForceGenerator::ForceGenerator> forceGen);
	bool RemoveForceGenerator			(std::string generatorName);
	bool AddParticleToRegistry			(ParticleID particleID, std::string genratorName);
	bool RemoveParticleFromRegistry		(ParticleID particleID, std::string genratorName);
	bool AddRigidBodyToRegistry			(RigidBodyID bodyID, std::string genratorName);
	bool RemoveRigidBodyFromRegistry	(RigidBodyID bodyID, std::string genratorName);
	void ClearForceRegistry();


private:
	std::unordered_map<RigidBodyID, std::unique_ptr<RigidBody>> mBodies;
	std::unordered_map<ParticleID, std::unique_ptr<Particle>> mParticles;
	ForceRegistry mRegistry;
	BoundingVolumeHirarchy mRigidBodyHirarchy;
	BinarySpacePartitioning mSpatialPartitioning;
};

}*/

#endif // !INCLUDED_VISHC_PHYSICS_WORLD_H
