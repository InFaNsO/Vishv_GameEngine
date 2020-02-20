#ifndef INCLUDED_VISHV_PHYSICS_PARTICLEFORCEGENERATOR_H
#define INCLUDED_VISHV_PHYSICS_PARTICLEFORCEGENERATOR_H

namespace Vishv::Physics {

	struct Particle;
	class RigidBody;

	using RigidBodyID = size_t;
	using ParticleID = size_t;

	//a force generator can be asked to add a force to one or more particles.

	namespace ForceGenerator {

		//Base Class for Force Generators
		class ForceGenerator
		{
		public:
			ForceGenerator() = default;
			ForceGenerator(const ForceGenerator& other)
				:mName(other.mName)
			{
			}
			virtual void UpdateForceParticle (ParticleID particleID, float deltaTime) = 0;
			virtual void UpdateForceRigidBody(RigidBodyID bodyID, float deltaTime) = 0;

			std::string mName = "/0";

			bool operator==(const ForceGenerator& other)
			{
				return mName == other.mName;
			}

			void operator=(const ForceGenerator& other)
			{
				mName = other.mName;
			}
		};

		/*//basic Force Generators 
		class Gravity: public ForceGenerator
		{
		public:
			Gravity(const Vishv::Math::Vector3& gravity);
			Gravity(float gravity = 9.807f);

			void UpdateForceParticle(ParticleID particleID, float deltaTime) override;
			void UpdateForceRigidBody(RigidBodyID bodyID, float deltaTime) override;

			std::string mName = "Gravity" ;
		private:
			Vishv::Math::Vector3 mGravity;
		};

		class Drag: public ForceGenerator
		{
		public:
			Drag() = default;
			Drag(float constant);
			Drag(float k1, float k2);

			void UpdateForceParticle(ParticleID particleID, float deltaTime) override;
			void UpdateForceRigidBody(RigidBodyID bodyID, float deltaTime) override;
			std::string mName = "Drag";
		private:
			float mConstant1 = 1.0f;
			float mConstant2 = 1.0f;
		};

		class Spring: ForceGenerator
		{
		public:
			Spring() = default;
			Spring(float springConstant, float restLength);

			void UpdateForceParticle(ParticleID particleID, float deltaTime) override;
			void UpdateForceRigidBody(RigidBodyID bodyID, float deltaTime) override;

			void SetOtherParticle(ParticleID particle);
			void SetOtherRigidBody(RigidBodyID body, Math::Vector3 connectionPoint1, Math::Vector3 connectionPoint2);
			void SetProperties(float springConstant = 1.0f, float restLength = 1.0f)					{ mSpringConstant = springConstant; mRestLength = restLength; }

			void Set(float springConstant, float restLength, ParticleID particle, RigidBodyID body, Math::Vector3 connectionPoint1, Math::Vector3 connectionPoint2) { SetOtherParticle(particle); SetOtherRigidBody(body, connectionPoint1, connectionPoint2); SetProperties(springConstant, restLength); }

			std::string mName = "Spring";
		private:
			//for particle
			Particle* mOtherParticle = nullptr;
			
			//for RigidBody
			RigidBody* mOtherRigidBody = nullptr;
			Math::Vector3 mConnectionPoint;
			Math::Vector3 mOtherConnectionPoint;

			//for both
			float mSpringConstant = 1.0f;
			float mRestLength = 1.0f;
		};

		class AnchoredSpring: ForceGenerator
		{
		public:
			AnchoredSpring() = default;
			AnchoredSpring(const Math::Vector3& anchor, float springConstant, float restLength);

			void UpdateForceParticle(ParticleID particle, float deltaTime) override;
			void UpdateForceRigidBody(RigidBodyID body, float deltaTime) override {};

			void SetAnchorPoint(const Math::Vector3& pos) { mAnchor = pos; }

			std::string mName = "AnchoredSpring";
		private:
			Math::Vector3 mAnchor = Math::Vector3();
			float mSpringConstant = 1.0f;
			float mRestLength = 1.0f;
		};

		class Bungee: public ForceGenerator
		{
		public:
			Bungee() = default;
			Bungee(const Particle& other, float constant, float length);

			void UpdateForceParticle(ParticleID particle, float deltaTime) override;
			void UpdateForceRigidBody(RigidBodyID body, float deltaTime) override {};
			std::string mName = "Bungee";
		private:
			std::shared_ptr<Particle> mOther = nullptr;
			float mSpringConstant = 1.0f;
			float mRestLength = 1.0f;
		};

		class Buoyancy: public ForceGenerator
		{
		public:
			Buoyancy() = default;
			Buoyancy(float maxDepth, float volume, float height, float dencity);

			void UpdateForceParticle(ParticleID particleID, float deltaTime) override;
			void UpdateForceRigidBody(RigidBodyID body, float deltaTime) override {};

			std::string mName = "Buoyancy";
		private:
			float mMaxDepth = 1.0f;
			float mVolume = 1.0f;
			float mHeight = 1.0f;
			float mDencity = 1000.0f;
		};

		class FakeSpring : public ForceGenerator
		{
		public:
			FakeSpring() = default;
			FakeSpring(const Math::Vector3& anchor, float constant, float dampening);

			void SetAnchor(const Math::Vector3& anchor) { mAnchor = anchor; };
			void SetConstant(float springConstant) { mSpringConstant = springConstant; };
			void SetDampening(float dampening) { mDampening = dampening; };

			void UpdateForceParticle(ParticleID particle, float deltaTime) override;
			void UpdateForceRigidBody(RigidBodyID body, float deltaTime) override {};
			
			std::string mName = "FakeSpring";
		private:
			Math::Vector3 mAnchor;
			float mSpringConstant;
			float mDampening;
		};

		class AeroDynamic : public ForceGenerator
		{
		public:
			AeroDynamic() = default;
			AeroDynamic(const Math::Matrix4& m,	const Math::Vector3& position, std::shared_ptr<Math::Vector3> wind);

			void SetSurfaceBody(const Math::Matrix4& surfaceBody);
			void SetPosition(const Math::Vector3& pos);
			void SetSpeed(std::shared_ptr<Math::Vector3> wind);
			void Set(const Math::Matrix4& surfaceBody, const Math::Vector3& position, std::shared_ptr<Math::Vector3> wind);

			void UpdateForceParticle(ParticleID particle, float deltaTime) override;
			void UpdateForceRigidBody(RigidBodyID body, float deltaTime) override;

			std::string mName = "AeroDynamic";
		protected:
			void UpdateForceFromSurfaceBody(RigidBody& body, float deltaTime, const Math::Matrix4& surfaceBody);

		private:
			Vishv::Math::Matrix4 mSurfaceBody;
			Math::Vector3 mPosition;
			std::shared_ptr<Math::Vector3> mWindSpeed;
		};
	}

	//Holds all the force generators and the particles they act on
	class ForceRegistry
	{
	public:
		bool AddForceGenerator(std::shared_ptr<ForceGenerator::ForceGenerator> forceGen);
		bool RemoveForceGenerator(std::string generatorName);
		bool AddParticle(ParticleID particle, std::string genratorName);
		bool AddRigidBody(RigidBodyID body, std::string genratorName);
		bool RemoveParticle(ParticleID particle, std::string genratorName);
		bool RemoveRigidBody(RigidBodyID body, std::string genratorName);
		void Clear();

		void Update(float deltaTime);

	private:

		struct ForceRegistration
		{
			ForceRegistration() = default;

			std::vector<ParticleID> mParticles;
			std::vector<RigidBodyID> mRigidBodies;
			std::shared_ptr<ForceGenerator::ForceGenerator> mForceGenerator;

			ForceRegistration(const ForceRegistration& other)
				:mParticles(other.mParticles)
				, mRigidBodies(other.mRigidBodies)
				,mForceGenerator(other.mForceGenerator)
			{
			}
		};

		using  Registry = std::vector<ForceRegistration>;
		Registry mRegistrations;
	};*/

}

#endif // !INCLUDED_VISHV_PHYSICS_PARTICLEFORCEGENERATOR_H
