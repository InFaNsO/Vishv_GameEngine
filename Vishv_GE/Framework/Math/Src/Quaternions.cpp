#include "Precompiled.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Constants.h"

using namespace Vishv;
using namespace Vishv::Math;




Quaternion Quaternion::operator*=(const Quaternion& other)
{
	this->w = (w * other.w) - (x * other.x) - (y * other.y) - (z*other.z);
	this->x = (other.w * x) + (other.x * w) + (other.y * z) - (other.z * y);
	this->y = (other.w * y) - (other.x * z) + (other.y * w) + (other.z * x);	
	this->z = (other.w * z) + (other.x * y) - (other.y * x) + (other.z * w);

	return *this;
}

Quaternion Vishv::Math::Quaternion::operator+(const Vector4 & v)
{
	Quaternion q(v);
	q *= *this;
	return Quaternion(w + q.w * 0.5f, x + q.x * 0.5f, y + q.y * 0.5f, z + q.z * 0.5f);
}

Quaternion Vishv::Math::Quaternion::operator+(const Vector3 & v)
{
	Quaternion q(v);
	q *= *this;
	return Quaternion(w + q.w * 0.5f, x + q.x * 0.5f, y + q.y * 0.5f, z + q.z * 0.5f);
}

void Vishv::Math::Quaternion::operator+=(const Vector4 & v)
{
	Quaternion q(v);
	q *= *this;
	w += q.w * 0.5f;
	x += q.x * 0.5f;
	y += q.y * 0.5f;
	z += q.z * 0.5f;
}

void Vishv::Math::Quaternion::operator+=(const Vector3 & v)
{
	Quaternion q(v);
	q *= *this;
	w += q.w * 0.5f;
	x += q.x * 0.5f;
	y += q.y * 0.5f;
	z += q.z * 0.5f;
}

inline float Vishv::Math::Quaternion::MagnitudeSq()
{
	return (w*w) + (x*x) + (y*y) + (z*z);
}

inline float Vishv::Math::Quaternion::Magnitude()
{
	return sqrtf(MagnitudeSq());
}

void Quaternion::Normalize()
{
	float len = Magnitude();
	VISHVASSERT(len > 0.0f, "[Vishv::MAth::Quaternion] length is invalid.");
	
	len = 1 / len;

	w *= len;
	x *= len;
	y *= len;
	z *= len;
}

Quaternion Quaternion::Normalize(const Quaternion& quat)
{
	Quaternion q(quat);
	float len = q.Magnitude();
	VISHVASSERT(len > 0.0f, "[Vishv::MAth::Quaternion] length is invalid.");

	len = 1.0f / len;

	q.w *= len;
	q.x *= len;
	q.y *= len;
	q.z *= len;
	return q;
}

Quaternion Quaternion::GetNormalize() const
{
	Quaternion q(*this);
	float len = q.Magnitude();
	VISHVASSERT(len > 0.0f, "[Vishv::MAth::Quaternion] length is invalid.");

	len = 1 / len;

	//q.w *= len;
	q.x *= len;
	q.y *= len;
	q.z *= len;
	return q;
}

Vector3 Vishv::Math::Quaternion::Rotate(const Vector3 & v) const
{
	const float vx = 2.0f * v.x;
	const float vy = 2.0f * v.y;
	const float vz = 2.0f * v.z;
	const float w2 = w * w * 0.5f;
	const float dot2 = (x*vx + y * vy + z * vz);
	return Vector3
	(
		(vx*w2 + (y * vz - z * vy)*w + x * dot2),
		(vy*w2 + (z * vx - x * vz)*w + y * dot2),
		(vz*w2 + (x * vy - y * vx)*w + z * dot2)
	);
}

Quaternion Vishv::Math::Quaternion::MatrixToQuaternion(const Matrix4 & mat)
{
	Quaternion q;
	float tr = mat._11 + mat._22 + mat._33;

	if (tr > 0) {
		float S = sqrt(tr + 1.0f) * 2.0f; // S=4*qw 
		q.w = 0.25f * S;
		q.x = (mat._32 - mat._23) / S;
		q.y = (mat._13 - mat._31) / S;
		q.z = (mat._21 - mat._12) / S;
	}
	else if ((mat._11 > mat._22) & (mat._11 > mat._33)) {
		float S = sqrt(1.0f + mat._11 - mat._22 - mat._33) * 2.f; // S=4*qx 
		q.w = (mat._32 - mat._23) / S;
		q.x = 0.25f * S;
		q.y = (mat._12 + mat._21) / S;
		q.z = (mat._13 + mat._31) / S;
	}
	else if (mat._22 > mat._33) {
		float S = sqrt(1.0f + mat._22 - mat._11 - mat._33) * 2.f; // S=4*qy
		q.w = (mat._13 - mat._31) / S;
		q.x = (mat._12 + mat._21) / S;
		q.y = 0.25f * S;
		q.z = (mat._23 + mat._32) / S;
	}
	else {
		float S = sqrt(1.0f + mat._33 - mat._11 - mat._22) * 2.f; // S=4*qz
		q.w = (mat._21 - mat._12) / S;
		q.x = (mat._13 + mat._31) / S;
		q.y = (mat._23 + mat._32) / S;
		q.z = 0.25f * S;
	}

	return q;
}

Quaternion Vishv::Math::Quaternion::RotationQuaternion(const float angleRadian, const Vector3 & axis)
{
	Vector3 v(axis);
	v.Normalize();
	float a = angleRadian * 0.5f;

	float an = sinf(a);
	return { v.x * an, v.y * an, v.z * an, cosf(a)};
}

void Vishv::Math::Quaternion::Rotate(float angleRad, Vector3 & object)
{
	auto a = angleRad * 0.5f;
	r = cosf(a) + sinf(a);
	Rotate(object);
}

void Vishv::Math::Quaternion::Rotate(Vector3& object)
{
	if (r = 0)
	{
		LOG("Angle not set on the quaternion");
		return;
	}
	if (MagnitudeSq() < 1.0f)
	{
		LOG("Not a unit axis vector");
		return;
	}
	else if (MagnitudeSq() > 1.0f)
		MakeUnit();

	//work here next

}

void Vishv::Math::Quaternion::MakeUnit()
{
	if (MagnitudeSq() > 1.0f)
	{
		float len = Magnitude();

		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}
	else
	{
		LOG("The quaternion is small.");
	}

}


