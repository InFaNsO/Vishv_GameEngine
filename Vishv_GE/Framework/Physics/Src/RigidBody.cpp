#include "Precompiled.h"
#include "RigidBody.h"

using namespace Vishv;
using namespace Vishv::Math;
using namespace Vishv::Physics;

void Vishv::Physics::RigidBody::CalculateDerivedData()
{
	mOrientation.Normalize();
	mTransformation = Vishv::Math::Matrix4(mOrientation, mPosition);

	TransformInertia();
}

void Vishv::Physics::RigidBody::SetInertia(const Math::Matrix4 & inertiaTensor, bool isInv)
{
	mInvIntertia = isInv ? inertiaTensor : inertiaTensor.Inverse();
}

void Vishv::Physics::RigidBody::TransformInertia()
{
	float t4 =	mTransformation._11 * mInvIntertia._11 + 
				mTransformation._12 * mInvIntertia._21 + 
				mTransformation._13 * mInvIntertia._31;
	
	float t9 =	mTransformation._11 * mInvIntertia._12 +
				mTransformation._12 * mInvIntertia._22 +
				mTransformation._13 * mInvIntertia._32;

	float t14 =	mTransformation._11 * mInvIntertia._13 +
				mTransformation._12 * mInvIntertia._23 +
				mTransformation._13 * mInvIntertia._33;

	float t28 =	mTransformation._21 * mInvIntertia._11 +
				mTransformation._22 * mInvIntertia._21 +
				mTransformation._23 * mInvIntertia._31;

	float t33 = mTransformation._21 * mInvIntertia._12 +
				mTransformation._22 * mInvIntertia._22 +
				mTransformation._23 * mInvIntertia._32;

	float t38 = mTransformation._21 * mInvIntertia._13 +
				mTransformation._22 * mInvIntertia._23 +
				mTransformation._23 * mInvIntertia._33;

	float t52 = mTransformation._31 * mInvIntertia._11 +
				mTransformation._32 * mInvIntertia._21 +
				mTransformation._33 * mInvIntertia._31;

	float t57 = mTransformation._31 * mInvIntertia._12 +
				mTransformation._32 * mInvIntertia._22 +
				mTransformation._33 * mInvIntertia._32;

	float t62 = mTransformation._31 * mInvIntertia._13 +
				mTransformation._32 * mInvIntertia._23 +
				mTransformation._33 * mInvIntertia._33;

	mInvIntertiaWorld.Reset();
	mInvIntertiaWorld._11 =  t4 * mTransformation._11 +
							 t9 * mTransformation._12 +
							t14 * mTransformation._13;

	mInvIntertiaWorld._12 =  t4 * mTransformation._21 +
							 t9 * mTransformation._22 +
							t14 * mTransformation._23;

	mInvIntertiaWorld._13 =  t4 * mTransformation._31 +
							 t9 * mTransformation._32 +
							t14 * mTransformation._33;

	mInvIntertiaWorld._21 =	t28 * mTransformation._11 +
							t33 * mTransformation._12 +
							t38 * mTransformation._13;

	mInvIntertiaWorld._22 = t28 * mTransformation._21 +
							t33 * mTransformation._22 +
							t38 * mTransformation._23;

	mInvIntertiaWorld._23 = t28 * mTransformation._31 +
							t33 * mTransformation._32 +
							t38 * mTransformation._33;

	mInvIntertiaWorld._31 = t52 * mTransformation._11 +
							t57 * mTransformation._12 +
							t62 * mTransformation._13;

	mInvIntertiaWorld._32 = t52 * mTransformation._21 +
							t57 * mTransformation._22 +
							t62 * mTransformation._23;

	mInvIntertiaWorld._33 = t52 * mTransformation._31 +
							t57 * mTransformation._32 +
							t62 * mTransformation._33;
}

void Vishv::Physics::RigidBody::AddForce(const Math::Vector3 & force)
{
	mForceAccumilation += force;
	mIsAwake = true;
}

void Vishv::Physics::RigidBody::ClearAccumilators()
{
	mForceAccumilation = Math::Vector3();
	mTorqueAccumilation = Math::Vector3();
}

void Vishv::Physics::RigidBody::Integrate(float deltaTime)
{
	Vector3 accelerationPrv(mAcceleration);
	accelerationPrv += mForceAccumilation * mInverseMass;

	mInvIntertiaWorld.Translate({ mTorqueAccumilation.x, mTorqueAccumilation.y, mTorqueAccumilation.z });
	mVelocity += accelerationPrv * deltaTime;
	mRotation += mAngularAcceleration * deltaTime;

	mVelocity *= powf(mLinearDamnping, deltaTime);
	mRotation *= powf(mAngularDampning, deltaTime);

	mPosition += mVelocity * deltaTime;
	mOrientation += mRotation * deltaTime;

	CalculateDerivedData();

	ClearAccumilators();
}

void Vishv::Physics::RigidBody::AddForceAtPoint(const Math::Vector3 & force, const Math::Vector3 & point, bool isLocal)
{
	Math::Vector3 pt(isLocal ? ConvertToWorldCoordinates(point) : point);
	pt -= mPosition;
	mForceAccumilation += force;
	mTorqueAccumilation += pt % force;
}

Vector3 Vishv::Physics::RigidBody::ConvertToWorldCoordinates(const Vector3 &point)
{
	return mPosition + point;
}

Vector3 Vishv::Physics::RigidBody::ConvertToLocalCoordinates(const Vector3 &point)
{
	return (mPosition - point) * -1.0f;
}


