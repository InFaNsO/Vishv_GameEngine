#include "Precompiled.h"
#include "Particle.h"
#include "Firework.h"
#include "PhysicsVectors.h"

/*using namespace Vishv;
using namespace Vishv::Physics;


void Vishv::Physics::Firework::Initialize(std::vector<Firework> payload, Fireworks::Ruleset rule, Math::Vector3 spawnPos, float mass, Math::Vector3 acceleratrion)
{
	mPayload = payload;
	mRule = rule;

	mType = rule.mRuleNumeber;

	mParticle.SetMass(mass);
	mParticle.SetPosition(spawnPos);
	mParticle.SetVelocity(mRule.mMinVelocity);
	mParticle.SetAcceleration(acceleratrion);
	mParticle.SetDampening(mRule.mDampening);
}

bool Vishv::Physics::Firework::Update(float deltaTime)
{
	mAge += deltaTime;
	mParticle.Update(deltaTime);

	if (mAge > mRule.mMaxAge)
		return true;

	return false;
}
*/