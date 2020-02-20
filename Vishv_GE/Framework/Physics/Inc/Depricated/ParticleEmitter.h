#ifndef INCLUDED_VISHV_PHYSICS_PARTICLEEMITTER_H
#define INCLUDED_VISHV_PHYSICS_PARTICLEEMITTER_H

#include "Particle.h"

namespace Vishv::Physics
{
	struct BurstPreset
	{
		uint32_t particleCount = 0;
		bool loop = false;
		float time = 0.0f;
	};

	struct ParticlePreset
	{
		uint32_t numTextures;
		std::vector<size_t> mTextureIDS;
		std::vector<BurstPreset> mBursts;

		//Global 
		float gravity;
		float emmiterRadius;
		Vishv::Math::Vector3 emmiterPosition;
		uint32_t maxNumberOfParticles;
		float rateOfEmmision;

		//PerParticle data
		float lifeTime;
		float lifeTimeJitter;

		float positionJitter;

		Vishv::Math::Vector3 velocity;
		float velocityJitter;

		float radius;
		float radiusJitter;

		bool collideWithin = false;
		bool outsideCollide = false;
		bool burst = false;
	};


class ParticleEmitter
{
public:
	struct ParticleBurstData
	{
		uint32_t count;
		float duration;
		float time;

		bool loop;
		bool loop_done = false;
	};

	struct ParticleData			//was in private;
	{
		Particle particle;
		float mRadius;
		//Vishv::Graphics::MeshPX mesh;
		//Vishv::Graphics::MeshBuffer meshBuffer;
	};

	enum class ParticleType
	{
		Plane,
		Cube,
		Sphere,
		Cylinder
		//Cone,
		//Torus,
	};

/*	void Initialize(const ParticlePreset& particlePreset);
	void AddBurst(const BurstPreset& bp);
	std::vector<ParticleBurstData>& GetBursts() { return mBursts; }

	void Update(float deltaTime);
	void Terminate();
	void Sort(const Math::Vector3& cameraDirection );

	void SetPlane(float height);
	void SetPlane(float rowHeight, float colHeight);
	void SetSphere(float radius);
	void SetCylinder(float height, float radius);
	void SetCube(float length);
	void SetCube(float height, float width, float length);

	void SetRateOfEmmision(float roe)							{ mEmmisionPerSecond = roe; }
	float GetRateOfEmmision()									{ return mEmmisionPerSecond; }

	void SetGravity(float g);
	void SetGravity(const Math::Vector3& g);
	float GetGravity()											{ return mGravity.y; }

	void SetVelocity(const Math::Vector3& vel);
	void SetVelocityJitter(float jitter);

	const Math::Vector3& GetVelocity()	const					{ return mVelocity; }
	float GetVelocityJitter()									{ return mVelocityJitter; }

	void SetLife(float time);
	void SetLifeJitter(float time);

	void SetPosition(const Math::Vector3& pos)					{ mCenter = pos; }
	void SetRadius(float radius)								{ mRadius = radius > 0.0f ? radius : 0.001f; }
	
	const Math::Vector3& GetPosition() const					{ return mCenter; }
	float GetRadius()											{ return mRadius; }

	float GetLife() { return mLifeTime; }
	float GetLifeJitter() { return mLifeTimeJitter; }

	size_t GetTextureID() { return mTextureID; }

	void SetCollideWithin(bool collide) { mIsCollidingWithin = collide; }
	void SetCollideOutside(bool collide) { mIsCollideOutSide = collide; }
	void SetBurst(bool collide)			{ mIsBurst = collide; }

	void Render();

	//Temp function need to fix later
	std::vector<ParticleData>& GetParticles() 
	{ 
		return mParticles;
	}
	std::vector<ParticleData> GetParticlesAlive()
	{
		std::vector<ParticleData> v;

		for (auto& p : mParticles)
		{
			if (p.particle.IsAlive())
				v.push_back(p);
		}
		return v;
	}



private:
	bool IsColliding(ParticleData& s1, ParticleData& s2, Vishv::Math::Vector3& pointOfContact);
	void CollisionResolution(ParticleData& s1, ParticleData& s2, const Vishv::Math::Vector3& pointOfCollision);
	void ResetVelocity();
	void Spawn();

	bool mIsCollidingWithin = false;
	bool mIsCollideOutSide = false;
	bool mIsBurst = false;

	std::vector<ParticleData> mParticles;
	std::vector<ParticleBurstData> mBursts;

	size_t mTextureID;
	float mLifeTime;
	float mLifeTimeJitter;

	Math::Vector3 mGravity;
	
	float mEmmisionPerSecond = 1.0f;
	float mSpawnTimmer = 0.0f;

	Math::Vector3 mCenter;
	float mRadius;

	Math::Vector3 mVelocity;
	float mVelocityJitter;

	ParticleType mParticleType;
};

class ParticleEmmiterGPU
{
public:
	void Initialize(uint32_t maxParticleNum = 100000)
	{
		mParticlesGPU.clear();
		mParticlesGPU.resize(maxParticleNum);
		spawnerTimer = 0.0f;

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> distLife(mLifeTime - mLifeTimeJitter < 0.0f ? 0.0f : mLifeTime - mLifeTimeJitter, mLifeTime + mLifeTimeJitter);

		std::uniform_real_distribution<float> distVelX(mVelocity.x - mVelocityJitter, mVelocity.x + mVelocityJitter);
		std::uniform_real_distribution<float> distVelY(mVelocity.y - mVelocityJitter, mVelocity.y + mVelocityJitter);
		std::uniform_real_distribution<float> distVelZ(mVelocity.z - mVelocityJitter, mVelocity.z + mVelocityJitter);

		std::uniform_real_distribution<float> distDampX(mDampening.x - mDampeningVelocity, mDampening.x + mDampeningVelocity);
		std::uniform_real_distribution<float> distDampY(mDampening.y - mDampeningVelocity, mDampening.y + mDampeningVelocity);
		std::uniform_real_distribution<float> distDampZ(mDampening.z - mDampeningVelocity, mDampening.z + mDampeningVelocity);

		std::uniform_real_distribution<float> distPosX(mPosition.x - mPositionJitter, mPosition.x + mPositionJitter);
		std::uniform_real_distribution<float> distPosY(mPosition.y - mPositionJitter, mPosition.y + mPositionJitter);
		std::uniform_real_distribution<float> distPosZ(mPosition.z - mPositionJitter, mPosition.z + mPositionJitter);

		for (uint32_t i = 0; i < maxParticleNum; ++i)
		{
			ParticleData pd;
			pd.mCurrentTime = 0.0f;
			pd.mMaxlifeTime = distLife(mt);

			pd.mPosition = { distPosX(mt), distPosY(mt), distPosZ(mt) };
			pd.mVelocity = { distVelX(mt), distVelY(mt), distVelZ(mt) };
			pd.mDampening = { distDampX(mt), distDampY(mt), distDampZ(mt) };

			mParticlesGPU.emplace_back(pd);
		}
	}

	struct ParticleData
	{
		Math::Vector3 mPosition;
		Math::Vector3 mVelocity;
		Math::Vector3 mDampening;

		float mMaxlifeTime;
		float mCurrentTime;

		bool mIsAlive = false;

		float mRadius;
	};

	void Spawn()
	{
		for (auto& p : mParticlesGPU)
		{
			if (!p.mIsAlive)
			{
				std::random_device rd;
				std::mt19937 mt(rd());
				std::uniform_real_distribution<float> distLife(mLifeTime - mLifeTimeJitter < 0.0f ? 0.0f : mLifeTime - mLifeTimeJitter, mLifeTime + mLifeTimeJitter);
				std::uniform_real_distribution<float> distRadius(
					mRadius- mRadiusJitter < 1.0f ? 1.0f : mRadius - mRadiusJitter, 
					mRadius + mRadiusJitter < 2.0f ? 2.0f : mRadius + mRadiusJitter);

				std::uniform_real_distribution<float> distVelX(mVelocity.x - mVelocityJitter, mVelocity.x + mVelocityJitter);
				std::uniform_real_distribution<float> distVelY(mVelocity.y - mVelocityJitter, mVelocity.y + mVelocityJitter);
				std::uniform_real_distribution<float> distVelZ(mVelocity.z - mVelocityJitter, mVelocity.z + mVelocityJitter);

				std::uniform_real_distribution<float> distDampX(mDampening.x - mDampeningVelocity, mDampening.x + mDampeningVelocity);
				std::uniform_real_distribution<float> distDampY(mDampening.y - mDampeningVelocity, mDampening.y + mDampeningVelocity);
				std::uniform_real_distribution<float> distDampZ(mDampening.z - mDampeningVelocity, mDampening.z + mDampeningVelocity);

				std::uniform_real_distribution<float> distPosX(mPosition.x - mPositionJitter, mPosition.x + mPositionJitter);
				std::uniform_real_distribution<float> distPosY(mPosition.y - mPositionJitter, mPosition.y + mPositionJitter);
				std::uniform_real_distribution<float> distPosZ(mPosition.z - mPositionJitter, mPosition.z + mPositionJitter);

				p.mCurrentTime = 0.0f;
				p.mMaxlifeTime = distLife(mt);

				p.mPosition = { distPosX(mt), distPosY(mt), distPosZ(mt) };
				p.mVelocity = { distVelX(mt), distVelY(mt), distVelZ(mt) };
				p.mDampening = { distDampX(mt), distDampY(mt), distDampZ(mt) };

				p.mRadius = distRadius(mt);

				p.mIsAlive = true;

				break;
			}
		}
	}

	void Update(float deltaTime)
	{
		for (auto& p : mParticlesGPU)
		{
			p.mCurrentTime += deltaTime;

			if (p.mCurrentTime > p.mMaxlifeTime)
			{
				p.mIsAlive = false;
			}
		}

		spawnerTimer += deltaTime;
		if (spawnerTimer >= 1.0f / mParticlesPerMinute)
		{
			spawnerTimer = timerSpawn;
			Spawn();
		}
	}


	Math::Vector3 mPosition;
	float mPositionJitter;

	Math::Vector3 mVelocity;
	float mVelocityJitter;

	Math::Vector3 mDampening;
	float mDampeningVelocity;

	float mLifeTime;
	float mLifeTimeJitter;

	float spawnerTimer;
	float timerSpawn;

	float mRadius;
	float mRadiusJitter;

	float mParticlesPerMinute = 1.0f;

	std::vector<ParticleData> mParticlesGPU;*/
};

}

#endif // !INCLUDED_VISHV_PHYSICS_PARTICLEEMITTER_H

