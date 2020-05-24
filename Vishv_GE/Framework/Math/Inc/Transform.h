#ifndef INCLUDED_VISHV_MATH_TRANSFORM_H
#define INCLUDED_VISHV_MATH_TRANSFORM_H

#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Vishv::Math {

class Transform
{
public:
	META_CLASS_DECLARE

	Transform() = default;
	//Transform(const Vector3& v) :mQuaternion(), mPosition(v) {}
	//Transform(const Quaternion& q) :mQuaternion(q), mPosition() {}
	//Transform(const Quaternion& q, const Vector3& v) :mQuaternion(q), mPosition(v) {}
	//Transform(const Vector3& v, const Quaternion& q) :mQuaternion(q), mPosition(v) {}

	//Transform operator*(const Transform& x) const
	//{
	//	return transform(x);
	//}
	bool operator==(const Transform& other)
	{
		return mPosition == other.mPosition && mQuaternion == other.mQuaternion;
	}
	bool operator!= (const Transform& other)
	{
		return mPosition != other.mPosition || mQuaternion != other.mQuaternion;
	}

	const Vector3& Up() const{ return mUp; }
	const Vector3& Forward() const{ return mForward; }

	void TranslateX(float value);
	void TranslateY(float value);
	void TranslateZ(float value);
	void TranslateUp(float value);
	void TranslateForward(float value);
	void TranslateRight(float value);

	void RotateX(float angleDeg);
	void RotateY(float angleDeg);
	void RotateZ(float angleDeg);
	void RotateUp(float angleDeg);
	void RotateForward(float angleDeg);
	void RotateRight(float angleDeg);
	void Rotate(const Quaternion& rotateQuat);
	void Rotate(const Vector3& axis, float angleDeg);
	void SetRotation(Quaternion&& quat) { mQuaternion = std::move(quat); RecalculateDirections(); }
	void SetRotation(const Quaternion& quat) {mQuaternion = quat; RecalculateDirections();
	}

	void SwitchForward() { mForward = -mForward; }

	const Quaternion& Rotation() const{ return mQuaternion; }
	const Math::Vector3& Position() const{ return mPosition; }

	const Quaternion& GetRotationQuaternion() const { return mQuaternion; }

	Vector3 mPosition;
	Vector3 mScale = Vector3(1.0f);

	Matrix4 GetTransformMatrix() const;
	void SetTransformation(const Matrix4& mat);
private:
	void RecalculateDirections();

	Quaternion mQuaternion;
	Vector3 mUp = { 0.0f,1.0f,0.0f };
	Vector3 mForward = { 0.0f, 0.0f, 1.0f };

	Matrix4 mTransformation;
};

}

#endif // !INCLUDED_VISHV_MATH_TRANSFORM_H

