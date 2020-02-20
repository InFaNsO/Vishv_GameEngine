#ifndef INCLUDED_VISHV_PHYSICS_PARTICLECONTACT_H
#define INCLUDED_VISHV_PHYSICS_PARTICLECONTACT_H

namespace Vishv::Physics{

	class Particle;

class ParticleContact
{
public:

protected:
	void Resolve(float deltaTime);
	float CalculateSeperatingVelocity() const;

private:
	std::array<std::shared_ptr<Particle>, 2> mParticles;
	float mRestitution;
	Math::Vector4 mContactNormal;

	void ResolveVelocity(float deltaTime);
};

}

#endif // !INCLUDED_VISHV_PHYSICS_PARTICLECONTACT_H
