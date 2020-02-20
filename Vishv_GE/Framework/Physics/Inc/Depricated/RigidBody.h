#ifndef INCLUDED_VISHV_PHYSICS_RIGIDBODY_H
#define INCLUDED_VISHV_PHYSICS_RIGIDBODY_H

namespace Vishv::Physics {

class RigidBody
{
public:
	float GetMass() { return mInverseMass <= 0.0f ? 0.0f : 1.0f / mInverseMass; }
	bool HasFiniteMass() { return mInverseMass > 0.0f ? true : false; }
	void AddForce(const Math::Vector3 & force);
	Math::Vector3& GetVelocity() { return mVelocity; }
	void AddForceAtPoint(const Math::Vector3& force, const Math::Vector3& point, bool isLocal = false);			//point is in world space
	void Integrate(float deltaTime);
	void SetInertia(const Math::Matrix4& inertiaTensor, bool isInv = false);
	void ClearAccumilators();
	void CalculateDerivedData();
	Math::Matrix4& GetTransform() { return mTransformation; }


protected:
	bool mIsAwake;
	float mInverseMass = 0.0f;
	float mLinearDamnping;
	float mAngularDampning;
	Math::Vector3 mPosition;
	Math::Vector3 mVelocity;
	Math::Vector3 mRotation;
	Math::Vector3 mAcceleration;
	Math::Vector3 mAngularVelocity;
	Math::Vector3 mAngularAcceleration;
	Math::Vector3 mForceAccumilation;
	Math::Vector3 mTorqueAccumilation;
	Math::Quaternion mOrientation;
	Math::Matrix4 mTransformation;
	Math::Matrix4 mInvIntertia;
	Math::Matrix4 mInvIntertiaWorld;

	void TransformInertia();

	Math::Vector3 ConvertToWorldCoordinates(const Math::Vector3 &point);
	Math::Vector3 ConvertToLocalCoordinates(const Math::Vector3 &point);

private:

};
}

#endif // !INCLUDED_VISHV_PHYSICS_RIGIDBODY_H
