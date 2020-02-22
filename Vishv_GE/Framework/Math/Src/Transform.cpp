#include "Precompiled.h"
#include "Transform.h"

#include "MetaRegistration.h"

META_CLASS_BEGIN(Vishv::Math::Transform)
	META_FIELD_BEGIN
		META_FIELD(mPosition, "Position")
		META_FIELD(mQuaternion, "Rotation")
		META_FIELD(mScale, "Scale")
	META_FIELD_END
META_CLASS_END

namespace
{
	Vishv::Math::Vector3 cross(const Vishv::Math::Vector3 &v0, const Vishv::Math::Vector3 & v1)
	{
		return { (v0.y * v1.z) - (v0.z * v1.y), (v0.z * v1.x) - (v0.x * v1.z), (v0.x * v1.y) - (v0.y * v1.x) };
	}
}

void Vishv::Math::Transform::TranslateX(float value)
{
	mPosition.x += value;
}

void Vishv::Math::Transform::TranslateY(float value)
{
	mPosition.y += value;
}

void Vishv::Math::Transform::TranslateZ(float value)
{
	mPosition.z += value;
}

void Vishv::Math::Transform::TranslateUp(float value)
{
	mPosition += mUp * value;
}

void Vishv::Math::Transform::TranslateForward(float value)
{
	mPosition += mForward * value;
}

void Vishv::Math::Transform::TranslateRight(float value)
{
	mPosition += cross(mUp, mForward) * value;
}

void Vishv::Math::Transform::RotateUp(float angleDeg)
{
	if (angleDeg == 0.0f)
		return;

	auto q = Quaternion::RotationQuaternion(angleDeg * Constans::DegToRad, mUp);
	mQuaternion *= q;
	mQuaternion.Normalize();
	mForward.Rotate(q);
	mForward.Normalize();
}

void Vishv::Math::Transform::RotateForward(float angleDeg)
{
	if (angleDeg == 0.0f)
		return;

	auto q = Quaternion::RotationQuaternion(angleDeg * Constans::DegToRad, mForward);
	mQuaternion *= q;
	mQuaternion.Normalize();
	mUp.Rotate(q);
	mUp.Normalize();
}

void Vishv::Math::Transform::RotateRight(float angleDeg)
{
	if (angleDeg == 0.0f)
		return;

	auto q = Quaternion::RotationQuaternion(angleDeg * Constans::DegToRad, cross(mUp, mForward));
	mQuaternion *= q;
	mQuaternion.Normalize();
	mUp.Rotate(q);
	mForward.Rotate(q);
	mUp.Normalize();
	mForward.Normalize();
}

void Vishv::Math::Transform::RotateX(float angleDeg)
{
	if (angleDeg == 0.0f)
		return;
	auto q = Quaternion::RotationQuaternion(angleDeg * Constans::DegToRad, { 1.0f,0.0f,0.0f });
	mQuaternion *= q;
	mQuaternion.Normalize();
	mUp.Rotate(q);
	mForward.Rotate(q);
	mUp.Normalize();
	mForward.Normalize();
}

void Vishv::Math::Transform::RotateY(float angleDeg)
{
	if (angleDeg == 0.0f)
		return;

	auto q = Quaternion::RotationQuaternion(angleDeg * Constans::DegToRad, { 0.0f,1.0f,0.0f });
	mQuaternion *= q;
	mQuaternion.Normalize();
	mUp.Rotate(q);
	mForward.Rotate(q);
	mUp.Normalize();
	mForward.Normalize();
}

void Vishv::Math::Transform::RotateZ(float angleDeg)
{
	if (angleDeg == 0.0f)
		return;

	auto q = Quaternion::RotationQuaternion(angleDeg * Constans::DegToRad, { 0.0f,0.0f,1.0f });
	mQuaternion *= q;
	mQuaternion.Normalize();
	mUp.Rotate(q);
	mForward.Rotate(q);
	mUp.Normalize();
	mForward.Normalize();
}

void Vishv::Math::Transform::Rotate(const Vector3& axis, float angleDeg)
{
	auto q = Quaternion::RotationQuaternion(angleDeg * Constans::DegToRad, axis);
	mQuaternion *= q;
	mQuaternion.Normalize();
	mUp.Rotate(q);
	mForward.Rotate(q);
	mUp.Normalize();
	mForward.Normalize();
}

