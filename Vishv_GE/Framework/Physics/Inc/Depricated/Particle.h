#ifndef INCLUDED_VISHV_PHYSICS_PARTICLE_H
#define INCLUDED_VISHV_PHYSICS_PARTICLE_H


namespace Vishv::Physics
{
	struct Particle
	{
		Math::Vector3 position = Math::Zero;
		Math::Vector3 latsPosition = Math::Zero;
		Math::Vector3 acceleration = Math::Zero;

		float radius = 1.0f;
		float invMass = 0.0f;
		float bounce = 0.0f;

		void SetPosition(const Math::Vector3& pos)
		{
			position = pos;
			latsPosition = pos;

			//no motion
		}

		void SetVelocity(const Math::Vector3& velocity)
		{
			latsPosition = position - velocity;
		}
	};
}


/*
*/


//Old Particle

/*A Particle is the simplets object that can be simulated in the physics system*/
/*
namespace Vishv::Physics {
	class Particle
	{
	public:
		Particle() = default;

		void Update(float deltaTime);
		void AddForce(const Math::Vector3 & force);
		float KineticEnergy();

		void SetMass(float mass);
		void SetPosition(const Math::Vector3 &pos)			{ mPosition = pos; }
		void SetVelocity(const Math::Vector3 &vel)			{ mVelocity = vel; }
		void SetAcceleration(const Math::Vector3 &acc)		{ mAcceleration = acc; }
		void SetEmmiterGravity(const Math::Vector3 &grav)	{ mGravity= grav; }
		void SetDampening(float damp)						{ mDampening = damp; }
		void SetMaxLifeTime(float time)						{ mMaxLifeTime = time; }

		const Math::Vector3& GetPosition()					{ return mPosition; }
		const Math::Vector3& GetVelocity()					{ return mVelocity; }
		const Math::Vector3& GetAcceleration()				{ return mAcceleration; }
		float GetDampening()								{ return mDampening; }
		float GetMass()										{ return  mInverseMass == 0.0f ? 0.0f : 1 / mInverseMass; }

		void Reset(const Math::Vector3& pos)				{ mLifeTime = 0.0f;  mPosition = pos; mIsAlive = true; }

		bool IsAlive() { return mIsAlive; }
		void Kill() { mIsAlive = false; }
		void SetIsEmmiter(bool emiter = true) { mIsParticleEmmiter = emiter; }

		float GetTime() { return mLifeTime;}
		float GetTotalTime() { return mMaxLifeTime; }

		bool operator==(const Particle& other);

	private:
		Math::Vector3 mPosition = Math::Vector3();					//Holds world position
		Math::Vector3 mVelocity = Math::Vector3();					//Holds linear velocity
		Math::Vector3 mAcceleration = Math::Vector3();				//Holds acceleration usually for gravity
		Math::Vector3 mAccumulatedForce = Math::Vector3();			//Holds the sum of all the forces acting on a particle
		Math::Vector3 mGravity = Math::Vector3();					//Used in case of patricle Emmision

		bool mIsParticleEmmiter = true;
		float mDampening;											//Used for drag to remove energy from a system
		float mInverseMass{ 1.0f };
		float mLifeTime = 0.0f;
		float mMaxLifeTime = 5.0f;									//Used to run a particle for certain amount of time
		bool mIsAlive = false;										//Used to see if the particle is active or not
	};

}*/


#endif // !INCLUDED_VISHV_PHYSICS_PARTICLE_H
