#include "Precompiled.h"
#include "ParticleEmitter.h"
//#include "Particle.h"
//#include "Graphics.h"

//struct Vishv::Physics::ParticleEmitter::ParticleData
//{
//	Vishv::Physics::Particle particle;
//	//Vishv::Graphics::MeshPX mesh;
//	//Vishv::Graphics::MeshBuffer meshBuffer;
//};

/*void Vishv::Physics::ParticleEmitter::Initialize(const Vishv::Physics::ParticlePreset& p)
{
	mGravity = { 0.0f, p.gravity, 0.0f };
	mParticles.reserve(p.maxNumberOfParticles);

	mCenter = p.emmiterPosition;
	mRadius = p.emmiterRadius;
	mEmmisionPerSecond = fabsf(p.rateOfEmmision);

	mLifeTime = p.lifeTime;
	mLifeTimeJitter = p.lifeTimeJitter;

	mVelocity = p.velocity;
	mVelocityJitter = p.velocityJitter;

	//To generate Random values for each particle
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_real_distribution<float> distSize(p.radius - p.radiusJitter < 0.1f ? 0.1f : p.radius - p.radiusJitter,
		p.radius + p.radiusJitter < 0.11f ? 0.11f : p.radius + p.radiusJitter);

	std::uniform_real_distribution<float> distLife(mLifeTime - mLifeTimeJitter < 0.1f ? 0.1f : mLifeTime - mLifeTimeJitter,
		mLifeTime + mLifeTimeJitter < 0.1f ? 0.1f : mLifeTime + mLifeTimeJitter);

	std::uniform_real_distribution<float> distVelX(mVelocity.x - mVelocityJitter, mVelocity.x + mVelocityJitter);
	std::uniform_real_distribution<float> distVelY(mVelocity.y - mVelocityJitter, mVelocity.y + mVelocityJitter);
	std::uniform_real_distribution<float> distVelZ(mVelocity.z - mVelocityJitter, mVelocity.z + mVelocityJitter);

	std::uniform_real_distribution<float> distPosX(mCenter.x - mRadius, mCenter.x + mRadius);
	std::uniform_real_distribution<float> distPosY(mCenter.y - mRadius, mCenter.y + mRadius);
	std::uniform_real_distribution<float> distPosZ(mCenter.z - mRadius, mCenter.z + mRadius);

	for (uint32_t i = 0; i < p.maxNumberOfParticles; ++i)
	{
		ParticleData pd;
		pd.particle.SetMass(1.0f);
		pd.particle.SetPosition({ distPosX(mt), distPosY(mt), distPosZ(mt) });
		pd.particle.SetVelocity({ distVelX(mt), distVelY(mt), distVelZ(mt) });
		pd.particle.SetMaxLifeTime(distLife(mt));
		pd.particle.SetIsEmmiter();
		pd.particle.SetEmmiterGravity(mGravity);

		pd.mRadius = distSize(mt);

		mParticles.emplace_back(pd);
	}
}

void Vishv::Physics::ParticleEmitter::AddBurst(const Vishv::Physics::BurstPreset& preset)
{
	ParticleBurstData data;
	data.count = preset.particleCount;
	data.loop = preset.loop;
	data.time = preset.time;
}

void Vishv::Physics::ParticleEmitter::SetGravity(float g)
{
	SetGravity({ 0.0f, g, 0.0f });
}
void Vishv::Physics::ParticleEmitter::SetGravity(const Math::Vector3 & g)
{
	mGravity = g;
	for (auto& p : mParticles)
	{
		p.particle.SetEmmiterGravity(mGravity);
	}
}

void Vishv::Physics::ParticleEmitter::SetVelocity(const Math::Vector3 & vel)
{
	mVelocity = vel;
	ResetVelocity();
}
void Vishv::Physics::ParticleEmitter::SetVelocityJitter(float jitter)
{
	mVelocityJitter = jitter;
	ResetVelocity();
}

void Vishv::Physics::ParticleEmitter::Sort(const Math::Vector3& cameraDirection)
{
	std::sort(mParticles.begin(), mParticles.end(), [&](auto& a, auto& b)
	{
		auto s = Math::Dot(a.particle.GetPosition(), cameraDirection);
		auto t = Math::Dot(b.particle.GetPosition(), cameraDirection);
		return s > t;
	});
}

void Vishv::Physics::ParticleEmitter::ResetVelocity()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_real_distribution<float> distVelX(mVelocity.x - mVelocityJitter, mVelocity.x + mVelocityJitter);
	std::uniform_real_distribution<float> distVelY(mVelocity.y - mVelocityJitter, mVelocity.y + mVelocityJitter);
	std::uniform_real_distribution<float> distVelZ(mVelocity.z - mVelocityJitter, mVelocity.z + mVelocityJitter);

	for (auto& p : mParticles)
	{
		p.particle.SetVelocity({ distVelX(mt), distVelY(mt), distVelZ(mt) });
	}
}

void Vishv::Physics::ParticleEmitter::SetLife(float time)
{
	mLifeTime = time - mLifeTimeJitter > 0.1f ? time : 0.1f;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> distLife(mLifeTime - mLifeTimeJitter, mLifeTime + mLifeTimeJitter);

	for (auto& p : mParticles)
		p.particle.SetMaxLifeTime(distLife(mt));
	
}
void Vishv::Physics::ParticleEmitter::SetLifeJitter(float time)
{
	mLifeTimeJitter = mLifeTime - time > 0.0f ? time : 0.0f;
	if (mLifeTimeJitter == 0.0f)
		for (auto& p : mParticles)
			p.particle.SetMaxLifeTime(mLifeTime);
	else
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> distLife(mLifeTime - mLifeTimeJitter, mLifeTime + mLifeTimeJitter);

		for (auto& p : mParticles)
			p.particle.SetMaxLifeTime(distLife(mt));
	}
}

void Vishv::Physics::ParticleEmitter::Update(float deltaTime)
{
	mSpawnTimmer += deltaTime;
	if (mSpawnTimmer >= 1.0f / mEmmisionPerSecond)
	{
		int num = static_cast<int>(mSpawnTimmer / (1.0f / mEmmisionPerSecond));
		for (int i = 0; i < num; ++i)
			Spawn();

		mSpawnTimmer -= (int)(mSpawnTimmer / mEmmisionPerSecond);
	}
	if (mSpawnTimmer > 1.0f / mEmmisionPerSecond)
	{
		mSpawnTimmer = 0.0f;
	}

	//do collision
	if (mIsCollidingWithin)
	{
		//this is a very naive way
		for (int i = 0; i < mParticles.size(); ++i)
		{
			if (mParticles[i].particle.IsAlive())
			{
				for (int j = 0; j < mParticles.size(); ++j)
				{
					if (mParticles[j].particle.IsAlive() && i != j)
					{
						Math::Vector3 PoC;
						if (IsColliding(mParticles[i], mParticles[j], PoC))
						{
							CollisionResolution(mParticles[i], mParticles[j], PoC);
						}
					}
				}
			}
		}
	}

	if (mBursts.size() > 0 && mIsBurst)
	{
		int count = 0;
		for (auto& burst : mBursts)
		{
			if (!burst.loop)
			{
				for (uint32_t i = 0; i < burst.count; ++i)
					Spawn();

				mBursts.erase(mBursts.begin(), mBursts.begin() + count);
			}
			else
			{
				burst.duration += deltaTime;
				if (burst.duration >= burst.time)
				{
					burst.duration = 0.0f;
					for (uint32_t i = 0; i < burst.count; ++i)
						Spawn();
				}
				count++;
			}
			burst.loop_done = true;

		}
	}

	if (mIsCollideOutSide)
	{
		//Get outside objects then do collision check and resolution
	}

	for (auto& particle : mParticles)
	{
		if (particle.particle.IsAlive())
			particle.particle.Update(deltaTime);
	}
}

void Vishv::Physics::ParticleEmitter::Spawn()
{
	for (auto& p : mParticles)
	{
		if (p.particle.IsAlive())
			continue;
		
		//To generate Random values for each particle
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> distLife(mLifeTime - mLifeTimeJitter < 0.1f ? 0.1f : mLifeTime - mLifeTimeJitter,
			mLifeTime + mLifeTimeJitter < 0.1f ? 0.1f : mLifeTime + mLifeTimeJitter);
		std::uniform_real_distribution<float> distVelX(mVelocity.x - mVelocityJitter, mVelocity.x + mVelocityJitter);
		std::uniform_real_distribution<float> distVelY(mVelocity.y - mVelocityJitter, mVelocity.y + mVelocityJitter);
		std::uniform_real_distribution<float> distVelZ(mVelocity.z - mVelocityJitter, mVelocity.z + mVelocityJitter);

		std::uniform_real_distribution<float> distPosX(mCenter.x - mRadius, mCenter.x + mRadius);
		std::uniform_real_distribution<float> distPosY(mCenter.y - mRadius, mCenter.y + mRadius);
		std::uniform_real_distribution<float> distPosZ(mCenter.z - mRadius, mCenter.z + mRadius);

		p.particle.Reset({ distPosX(mt), distPosY(mt), distPosZ(mt) });
		p.particle.SetVelocity({ distVelX(mt), distVelY(mt), distVelZ(mt) });
		p.particle.SetMaxLifeTime(distLife(mt));
		break;
	}
}

void Vishv::Physics::ParticleEmitter::SetPlane(float height)
{
	SetPlane(height, height);
}
void Vishv::Physics::ParticleEmitter::SetPlane(float rowHeight, float colHeight)
{
	VISHVASSERT(mParticleType == ParticleType::Plane, "[ParticleEmmiter] Wrong function called.");

	for (auto& p : mParticles)
	{
		//p.mesh = Vishv::Graphics::Meshbuilder::CreatePlaneUV(1, 1, rowHeight, colHeight);
		//p.meshBuffer.Initialize(p.mesh);
	}
}
void Vishv::Physics::ParticleEmitter::SetSphere(float radius)
{
	VISHVASSERT(mParticleType == ParticleType::Sphere, "[ParticleEmmiter] Wrong function called.");

	for (auto& p : mParticles)
	{
		//p.mesh = Vishv::Graphics::Meshbuilder::CreateSphereUV(10, 10, radius);
		//p.meshBuffer.Initialize(p.mesh);
	}
}
void Vishv::Physics::ParticleEmitter::SetCylinder(float height, float radius)
{
	VISHVASSERT(mParticleType == ParticleType::Cylinder, "[ParticleEmmiter] Wrong function called.");

	for (auto& p : mParticles)
	{
		//p.mesh = Vishv::Graphics::Meshbuilder::CreateCylinderUV(2, 12, radius, height / 12.0f);
		//p.meshBuffer.Initialize(p.mesh);
	}
}
void Vishv::Physics::ParticleEmitter::SetCube(float length)
{
	SetCube(length, length, length);
}
void Vishv::Physics::ParticleEmitter::SetCube(float height, float width, float length)
{
	VISHVASSERT(mParticleType == ParticleType::Cube, "[ParticleEmmiter] Wrong function called.");

	for (auto& p : mParticles)
	{
		//p.mesh = Vishv::Graphics::Meshbuilder::CreateCubeUV(height, width, length);
		//p.meshBuffer.Initialize(p.mesh);
	}
}

void Vishv::Physics::ParticleEmitter::Render()
{
	//for (auto&p : mParticles)
	//{
	//	if (p.particle.IsAlive())
//		{
//			p.meshBuffer.Render();
//		}
	//}
}

bool Vishv::Physics::ParticleEmitter::IsColliding(ParticleData & s1, ParticleData & s2, Vishv::Math::Vector3 & pointOfContact)
{
	float disSq = fabsf((s2.particle.GetPosition() - s1.particle.GetPosition()).MagnitudeSq());
	float radiusSq = (s1.mRadius * s1.mRadius) + (s2.mRadius * s2.mRadius);

	if (disSq < radiusSq)		//they are colliding
	{
		//Generate point of contact
		float dist = sqrtf(disSq);
		float pen = s1.mRadius - (dist - s2.mRadius);
		pen *= 0.5f;

		Math::Vector3 dir1(s2.particle.GetPosition() - s1.particle.GetPosition());
		dir1.Normalize();

		s1.particle.SetPosition(s1.particle.GetPosition() + (dir1 * pen));
		s2.particle.SetPosition(s2.particle.GetPosition() - (dir1 * pen));

		pointOfContact = s2.particle.GetPosition() + (dir1 * s2.mRadius);

		return true;
	}

	return false;
}

void Vishv::Physics::ParticleEmitter::CollisionResolution(ParticleData & s1, ParticleData & s2, const Vishv::Math::Vector3& pointOfCollision)
{
	Vishv::Math::Vector3 normal = s1.particle.GetPosition() - s2.particle.GetPosition();
	normal.Normalize();

	Vishv::Math::Vector3 perpendicular(normal.Cross(pointOfCollision));

	Vishv::Math::Vector3 v1Par(normal * normal.Dot(s1.particle.GetVelocity()));
	Vishv::Math::Vector3 v1Orth(perpendicular * perpendicular.Dot(s1.particle.GetVelocity()));

	Vishv::Math::Vector3 v2Par(normal * normal.Dot(s2.particle.GetVelocity()));
	Vishv::Math::Vector3 v2Orth(perpendicular * perpendicular.Dot(s2.particle.GetVelocity()));

	float len1 = v1Par.MagnitudeSq();
	float len2 = v2Par.MagnitudeSq();

	float CommonVel(4.0f * (s1.particle.GetMass() * s1.particle.GetMass() + len1 + s2.particle.GetMass() * s2.particle.GetMass())
		/ s1.particle.GetMass() * s1.particle.GetMass() + s2.particle.GetMass() * s2.particle.GetMass());

	v1Par *= (CommonVel - len1) / len1;
	v2Par *= (CommonVel - len2) / len2;

	s1.particle.SetVelocity(v1Par + v1Orth);
	s2.particle.SetVelocity(v2Par + v2Orth);
}

void Vishv::Physics::ParticleEmitter::Terminate()
{
}*/

