#ifndef INCLUDED_VISHV_PHYSICS_FIREWORK_H
#define INCLUDED_VISHV_PHYSICS_FIREWORK_H

/*namespace Vishv::Physics {

	class	Particle;

	namespace Fireworks {
		struct Ruleset
		{
			int mRuleNumeber;
			float mMaxAge;
			Math::Vector3 mMinVelocity;
			Math::Vector3 mMaxVelocity;
			float mDampening;
		};
	}


	class Firework
	{
	public:
		void Initialize(std::vector<Firework> payload, Fireworks::Ruleset rule, Math::Vector3 spawnPos, float mass = 1.0f, Math::Vector3 acceleratrion = { 0.0f, -9.807f, 0.0f });
		bool Update(float deltaTime);
		std::vector<Firework> &GetPayload() { return mPayload; }
		const Math::Vector4 &GetPosition() { return mParticle.GetPosition(); }
		Fireworks::Ruleset &GetRuleSet() { return mRule; }

	private:
		Particle mParticle;
		int mType;
		float mAge = 0.0f;
		std::vector<Firework> mPayload;
		Fireworks::Ruleset mRule;
	};



}
*/
#endif // !INCLUDED_VISHV_PHYSICS_FIREWORK_H
