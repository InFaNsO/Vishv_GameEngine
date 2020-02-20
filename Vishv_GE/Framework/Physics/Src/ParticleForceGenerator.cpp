#include "Precompiled.h"
#include "ParticleForceGenerator.h"
#include "Particle.h"
#include "RigidBody.h"
#include "World.h"

using namespace Vishv;
using namespace Vishv::Physics;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
/*Registry

bool  ForceRegistry::AddForceGenerator(std::shared_ptr<ForceGenerator::ForceGenerator> forceGen)
{
	bool found = false;
	for (int i = 0; i < mRegistrations.size(); ++i)
	{
		if (mRegistrations[i].mForceGenerator == forceGen)
		{
			found = true;
			break;
		}
	}

	if (found)
		LOG("[Vishv::Physics::PartcileForceRegistry::RemoveForceGenerator] the generator already exists.");
	else
	{
		ForceRegistration reg;
		reg.mForceGenerator = std::move(forceGen);
		mRegistrations.push_back(reg);
	}
	return found;
}

bool ForceRegistry::RemoveForceGenerator(std::string generatorName)
{
	bool found = false;
	for (int i = 0; i < mRegistrations.size(); ++i)
	{
		if (mRegistrations[i].mForceGenerator->mName == generatorName)
		{
			found = true;
			mRegistrations.erase(mRegistrations.begin() + i);
			break;
		}
	}

	if (!found)
		LOG("[Vishv::Physics::PartcileForceRegistry::RemoveForceGenerator] the generator wasnt found.");

	return found;
}

bool ForceRegistry::AddParticle(ParticleID particle, std::string genratorName)
{
	bool found = false;
	for (auto& registration : mRegistrations)
	{
		if (registration.mForceGenerator->mName == genratorName)
		{
			registration.mParticles.push_back(particle);
			break;
		}
	}

	if(!found)
		LOG( "[Vishv::Physics::PartcileForceRegistry::AddParticle] the generator wasnt found.");

	return found;
}

bool ForceRegistry::RemoveParticle(ParticleID particle, std::string genratorName)
{
	bool found = false;
	for (auto& registration : mRegistrations)
	{
		if (registration.mForceGenerator->mName == genratorName)
		{
			for (int i = 0; i < registration.mParticles.size(); ++i)
			{
				if (registration.mParticles[i] == particle)
				{
					registration.mParticles.erase(registration.mParticles.begin() + i);
					break;
				}
			}
			break;
		}
	}

	if (!found)
		LOG("[Vishv::Physics::PartcileForceRegistry::RemoveParticle] the generator wasnt found.");

	return found;
}

bool ForceRegistry::AddRigidBody(RigidBodyID body, std::string genratorName)
{
	bool found = false;
	for (auto& registration : mRegistrations)
	{
		if (registration.mForceGenerator->mName == genratorName)
		{
			registration.mRigidBodies.push_back(body);
			break;
		}
	}

	if (!found)
		LOG("[Vishv::Physics::PartcileForceRegistry::AddRigidBody] the generator wasnt found.");

	return found;
}

bool ForceRegistry::RemoveRigidBody(RigidBodyID body, std::string genratorName)
{
	bool found = false;
	for (auto& registration : mRegistrations)
	{
		if (registration.mForceGenerator->mName == genratorName)
		{
			for (int i = 0; i < registration.mParticles.size(); ++i)
			{
				if (registration.mParticles[i] == body)
				{
					registration.mRigidBodies.erase(registration.mRigidBodies.begin() + i);
					break;
				}
			}
			break;
		}
	}

	if (!found)
		LOG("[Vishv::Physics::PartcileForceRegistry::RemoveRigidBody] the generator wasnt found.");

	return found;
}

void ForceRegistry::Clear()
{
	mRegistrations.clear();
}

void ForceRegistry::Update(float deltaTime)
{
	for (int i = 0; i < mRegistrations.size(); ++i)
	{
		for (int j = 0; j < mRegistrations[i].mParticles.size(); ++j)
		{
			mRegistrations[i].mForceGenerator->UpdateForceParticle(mRegistrations[i].mParticles[j], deltaTime);
		}
		for (int j = 0; j < mRegistrations[i].mRigidBodies.size(); ++j)
		{
			mRegistrations[i].mForceGenerator->UpdateForceRigidBody(mRegistrations[i].mRigidBodies[j], deltaTime);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Gravity Generator

ForceGenerator::Gravity::Gravity(const Vishv::Math::Vector3 & gravity)
	:mGravity(gravity)
{
}

ForceGenerator::Gravity::Gravity(float gravity)
	: mGravity({0.0f, gravity > 0 ? -gravity : gravity, 0.0f})
{
}

void ForceGenerator::Gravity::UpdateForceParticle(ParticleID particle, float deltaTime)
{
	auto p = World::Get()->GetParticle(particle);

	if ( p->GetMass() < 0.0f)
		return;
	p->AddForce(mGravity * p->GetMass());
}

void ForceGenerator::Gravity::UpdateForceRigidBody(RigidBodyID body, float deltaTime)
{
	auto b = World::Get()->GetRigidBody(body);

	if (!b->HasFiniteMass())
		return;
	b->AddForce(mGravity * b->GetMass());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Drag Generator

Vishv::Physics::ForceGenerator::Drag::Drag(float constant)
	:mConstant1(constant)
	,mConstant2(constant)
{
}

Vishv::Physics::ForceGenerator::Drag::Drag(float k1, float k2)
	:mConstant1(k1)
	,mConstant2(k2)
{
}

void Vishv::Physics::ForceGenerator::Drag::UpdateForceParticle(ParticleID particleID, float deltaTime)
{
	auto particle = World::Get()->GetParticle(particleID);

	Vishv::Math::Vector3 force(particle->GetVelocity());

	float dragCoeff = force.Magnitude();
	dragCoeff = mConstant1 * dragCoeff + mConstant2 * dragCoeff * dragCoeff;

	force.Normalize();
	force *= -dragCoeff;

	particle->AddForce(force);
}

void Vishv::Physics::ForceGenerator::Drag::UpdateForceRigidBody(RigidBodyID bodyID, float deltaTime)
{
	auto body = World::Get()->GetRigidBody(bodyID);

	Vishv::Math::Vector3 force(body->GetVelocity());

	float dragCoeff = force.Magnitude();
	dragCoeff = mConstant1 * dragCoeff + mConstant2 * dragCoeff * dragCoeff;

	force.Normalize();
	force *= -dragCoeff;

	body->AddForce(force);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Spring Force Generator

Vishv::Physics::ForceGenerator::Spring::Spring(float springConstant, float restLength)
	:mSpringConstant(springConstant)
	,mRestLength(restLength)
{
}

void Vishv::Physics::ForceGenerator::Spring::SetOtherParticle(Physics::ParticleID particle)
{
	mOtherParticle = World::Get()->GetParticle(particle);
}

void Vishv::Physics::ForceGenerator::Spring::SetOtherRigidBody(Physics::RigidBodyID body, Math::Vector3 connectionPoint1, Math::Vector3 connectionPoint2)
{
	mOtherRigidBody = World::Get()->GetRigidBody(body);
	mConnectionPoint = connectionPoint1;
	mOtherConnectionPoint = connectionPoint2;
}

void Vishv::Physics::ForceGenerator::Spring::UpdateForceParticle(ParticleID particleID, float deltaTime)
{
	auto particle = World::Get()->GetParticle(particleID);
	Math::Vector3 force(particle->GetPosition());
	force -= mOtherParticle->GetPosition();

	float magnitude = force.Magnitude();
	magnitude = fabsf(magnitude - mRestLength);
	magnitude *= mSpringConstant;
	force.Normalize();

	force *= -magnitude;
	particle->AddForce(force);

	/*Probably can add negative force to the other particle here instead of making another generator
}

void Vishv::Physics::ForceGenerator::Spring::UpdateForceRigidBody(RigidBodyID bodyID, float deltaTime)
{
	auto body = World::Get()->GetRigidBody(bodyID);
	Math::Vector3 force(mConnectionPoint - mOtherConnectionPoint);

	float magnitude = force.Magnitude();
	magnitude = fabsf(magnitude - mRestLength) * mSpringConstant;

	force.Normalize();
	force *= -magnitude;

	body->AddForceAtPoint(force, mConnectionPoint);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Anchored Spring

Vishv::Physics::ForceGenerator::AnchoredSpring::AnchoredSpring(const Math::Vector3& anchor, float springConstant, float restLength)
	:mAnchor(anchor)
	,mSpringConstant(springConstant)
	,mRestLength(restLength)
{
}

void Vishv::Physics::ForceGenerator::AnchoredSpring::UpdateForceParticle(ParticleID particleID, float deltaTime)
{
	auto particle = World::Get()->GetParticle(particleID);

	Math::Vector3 force(particle->GetPosition());
	force -= mAnchor;

	float mag = force.Magnitude();
	mag = (mRestLength - mag) * mSpringConstant;

	force.Normalize();
	force *= -mag;
	particle->AddForce(force);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Bungee Spring

Vishv::Physics::ForceGenerator::Bungee::Bungee(const Particle & other, float constant, float length)
	:mSpringConstant(constant)
	,mRestLength(length)
{
	*mOther = other;
}

void Vishv::Physics::ForceGenerator::Bungee::UpdateForceParticle(ParticleID particleID, float deltaTime)
{
	auto particle = World::Get()->GetParticle(particleID);

	Math::Vector3 force(particle->GetPosition());
	force -= mOther->GetPosition();

	float mag = force.Magnitude();
	if (mag <= mRestLength)
		return;

	mag = (mRestLength - mag) * mSpringConstant;


	force.Normalize();
	force *= -mag;
	particle->AddForce(force);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Buoyancy Force

Vishv::Physics::ForceGenerator::Buoyancy::Buoyancy(float maxDepth, float volume, float height, float dencity)
	:mMaxDepth(maxDepth)
	,mVolume(volume)
	,mHeight(height)
	,mDencity(dencity)
{
}

void Vishv::Physics::ForceGenerator::Buoyancy::UpdateForceParticle(ParticleID particleID, float deltaTime)
{
	/*Change this to 3D (it would make it very complicated)
	auto particle = World::Get()->GetParticle(particleID);

	float depth = particle->GetPosition().y;	

	if (depth >= mHeight + mMaxDepth)
		return;

	Math::Vector3 force;

	if (depth <= mHeight - mMaxDepth)
	{
		force.y = mDencity * mVolume;
		particle->AddForce(force);
		return;
	}

	force.y = mDencity * mVolume * ((depth - mMaxDepth - mHeight) / 2.0f )* mMaxDepth;

	particle->AddForce(force);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Fake Spring

Vishv::Physics::ForceGenerator::FakeSpring::FakeSpring(const Math::Vector3& anchor, float constant, float dampening)
	:mAnchor(anchor)
	,mSpringConstant(constant)
	,mDampening(dampening)
{
}

void Vishv::Physics::ForceGenerator::FakeSpring::UpdateForceParticle(ParticleID particleID, float deltaTime)
{
	auto particle = World::Get()->GetParticle(particleID);
	if (particle->GetMass() <= 0.0f) return;

	Math::Vector3 position(particle->GetPosition());
	position -= mAnchor;

	float gamma = 0.05f * sqrtf(4.0f * mSpringConstant - mDampening * mDampening);
	if (gamma == 0.0f) return;

	Math::Vector3 c(position * (mDampening / (2.0f * gamma))
		+ particle->GetVelocity());
	c *= (1.0f / gamma);

	Math::Vector3 target(position);
	target *= cosf(gamma * deltaTime);
	target += c * sinf(gamma * deltaTime);
	target *= expf(-0.5f * deltaTime * mDampening);

	Math::Vector3 acc((target - position) * (1.0f / deltaTime * deltaTime));
	Math::Vector3 vel(particle->GetVelocity());
	vel *= deltaTime;
	acc -= vel;

	particle->AddForce(acc * particle->GetMass());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Aerodynamic

Vishv::Physics::ForceGenerator::AeroDynamic::AeroDynamic(const Math::Matrix4& m, const Math::Vector3& position, std::shared_ptr<Math::Vector3> wind)
	:mSurfaceBody(m)
	,mPosition(position)
	,mWindSpeed(wind)
{
}

void Vishv::Physics::ForceGenerator::AeroDynamic::SetSurfaceBody(const Math::Matrix4 & surfaceBody)
{
	mSurfaceBody = surfaceBody;
}

void Vishv::Physics::ForceGenerator::AeroDynamic::SetPosition(const Math::Vector3 & pos)
{
	mPosition = pos;
}

void Vishv::Physics::ForceGenerator::AeroDynamic::SetSpeed(std::shared_ptr<Math::Vector3> wind)
{
	mWindSpeed = wind;
}

void Vishv::Physics::ForceGenerator::AeroDynamic::Set(const Math::Matrix4& surfaceBody, const Math::Vector3& position, std::shared_ptr<Math::Vector3> wind)
{
	SetSurfaceBody(surfaceBody);
	SetPosition(position);
	SetSpeed(wind);
}

void Vishv::Physics::ForceGenerator::AeroDynamic::UpdateForceParticle(RigidBodyID body, float deltaTime)
{
	return;
}

void Vishv::Physics::ForceGenerator::AeroDynamic::UpdateForceRigidBody(ParticleID particle, float deltaTime)
{
	return;
}

void Vishv::Physics::ForceGenerator::AeroDynamic::UpdateForceFromSurfaceBody(RigidBody & body, float deltaTime, const Math::Matrix4 & surfaceBody)
{
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

*/