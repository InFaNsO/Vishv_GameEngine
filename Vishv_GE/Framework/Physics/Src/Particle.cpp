#include "Precompiled.h"
#include "Particle.h"

/*using namespace Vishv;

void Vishv::Physics::Particle::SetMass(float mass)
{
	VISHVASSERT(mass > 0.0f, "[Vishv::Physics::Particle::SetMass] mass has to be greater than 0.");
	mInverseMass = 1 / mass;
}

void Vishv::Physics::Particle::Update(float deltaTime)
{
	VISHVASSERT(mInverseMass > 0.0f, "[Vishv::Physics::Particle::Update] mass has wrong value");

	mLifeTime += deltaTime;
	if (mLifeTime >= mMaxLifeTime)
		mIsAlive = false;

	//update position
	if (mIsParticleEmmiter)
		AddForce(mGravity);

	mPosition += mVelocity * deltaTime;


	//Update acceleration
	Math::Vector3 acceleration = mAccumulatedForce * mInverseMass;

	//Update velocity 
	mVelocity += acceleration * deltaTime;
	//mVelocity *= powf(mDampening, deltaTime);		//Reduce velocity using the dampening forces

	mAccumulatedForce = Math::Vector3();		//reset the accumulated forces for the next frame
}

void Vishv::Physics::Particle::AddForce(const Math::Vector3 & force)
{
	mAccumulatedForce += force;
}

float Vishv::Physics::Particle::KineticEnergy()
{
	VISHVASSERT(mInverseMass > 0.0f, "[Vishv::Physics::Particle::Update] mass has wrong value");

	float mass = 1 / mInverseMass;

	return 0.5f * mass * mVelocity.MagnitudeSq();
}

bool Vishv::Physics::Particle::operator==(const Particle & other)
{
	return mPosition == other.mPosition;
}*/
