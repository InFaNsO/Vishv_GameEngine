#ifndef INCLUDED_VISHV_MATH_QUATERNION_H
#define INCLUDED_VISHV_MATH_QUATERNION_H

#include "Vector4.h"
#include "Vector3.h"
#include "Constants.h"

namespace Vishv::Math {

	struct Matrix4;

struct Quaternion
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct
		{
			float i;
			float j;
			float k;
			float r;
		};
		std::array<float, 4> v;
	};

	constexpr Quaternion()											noexcept : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
	constexpr Quaternion(float f)									noexcept : w(f), x(f), y(f), z(f) {}
	constexpr Quaternion(float x, float y, float z)					noexcept : x(x), y(y), z(z), w(0.0f) {}
	constexpr Quaternion(float x, float y, float z, float w)		noexcept : x(x), y(y), z(z), w(w) {}
	constexpr Quaternion(const Quaternion& q)						noexcept : w(q.w), x(q.x), y(q.y), z(q.z) {}
	explicit constexpr Quaternion(const Vector4& v)							noexcept : w(v.w), x(v.x), y(v.y), z(v.z) {}
	explicit constexpr Quaternion(const Vector3& v)							noexcept :w(0.0f), x(v.x), y(v.y), z(v.z) {}
	constexpr Quaternion(const float a, const Vector3& v)			noexcept :w(a), x(v.x), y(v.y), z(v.z) {}
	Quaternion(const Vector3& v, float angleRad)
		:x(0.0f)
		,y(0.0f)
		,z(0.0f)
		,w(0.0f)
	{
		float a = angleRad * 0.5f;
		float s = sinf(a);
		w = cosf(a);
		x = v.x * s;
		y = v.y * s;
		z = v.z * s;
	}

	//Nvidia functions
	void ToRadiansAndUnitAxis(float& angle, Vector3& axis)
	{
		float qEpsilon = float(1.0e-8f);
		float s2 = x * x + y * y + z * z;
		if (s2 < qEpsilon * qEpsilon)
		{
			angle = 0.0f;
			axis = Vector3(1.0, 0.0f, 0.0f);
		}
		else
		{
			float s = 1.0f / sqrtf(s2);
			axis = Vector3(x, y, z) * s;
			angle = fabsf(w) < qEpsilon ? Constans::Pi : atan2f(s2 * s, w) * 2.0f;
		}
	}

	float GetAngle() const
	{
		return acosf(w) * 2.0f;
	}

	static float GetAngle(const Quaternion& q)
	{
		return acosf(q.w) * 2.0f;
	}

	static float GetAngle(const Quaternion& q1, const Quaternion& q2)
	{
		return acosf(Dot(q1, q2)) * 2.0f;
	}

	static Quaternion MatrixToQuaternion(const Matrix4& mat);

	Quaternion operator- () const
	{
		return { -x,-y,-z,w };
	}
	Quaternion operator* (const Quaternion& q) const
	{
		/*
		
		*/

		Quaternion pro;

		pro.w = w * q.w - x * q.x - y * q.y - z * q.z;
		pro.x = w * q.x - x * q.w - y * q.z - z * q.y;
		pro.y = w * q.y - x * q.z - y * q.w - z * q.x;
		pro.z = w * q.z - x * q.y - y * q.x - z * q.w;

		return pro;
		//
		//return Quaternion(w*q.x + q.w*x + y * q.z - q.y*z,
		//	w*q.y + q.w*y + z * q.x - q.z*x,
		//	w*q.z + q.w*z + x * q.y - q.x*y,
		//	w*q.w - x * q.x - y * q.y - z * q.z);
	}

	Quaternion operator* (float f) const 
	{
		return Quaternion(x*f, y*f, z*f, w*f);

	}

	Quaternion operator/ (float f) const 
	{
		return Quaternion(x/f, y/f, z/f, w / f);
	}

	Quaternion operator*= (const Quaternion& other);
	Quaternion operator+ (const Quaternion& other)
	{
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}
	Quaternion operator+ (const Vector4& v);	
	Quaternion operator+ (const Vector3& v);
	void operator+= (const Vector4& v);
	void operator+= (const Vector3& v);

	constexpr bool operator==(const Quaternion& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	constexpr bool operator!=(const Quaternion& other)
	{
		return !(x == other.x && y == other.y && z == other.z && w == other.w);
	}

	inline float MagnitudeSq();
	inline float Magnitude();

	void Normalize();
	Quaternion GetNormalize() const;

	static Quaternion Normalize(const Quaternion& q);

	float Dot(const Quaternion& q2) const
	{
		return x * q2.x + y * q2.y + z * q2.z + w * q2.w;
	}
	static float Dot(const Quaternion& q1, const Quaternion& q2)
	{
		return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	}

	Vector3 Rotate(const Vector3& v) const;

	Quaternion GetConjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}
	static Quaternion GetConjugate(const Quaternion& q)
	{
		return { -q.i, -q.j, -q.k, q.r };
	}
	Vector3 GetImaginaryPart() const
	{
		return Vector3(x, y, z);
	}
	Vector3 GetBasisVector0()	const
	{
		//		return rotate(Vec3(1,0,0));
		const float x2 = x * 2.0f;
		const float w2 = w * 2.0f;
		return Vector3((w * w2) - 1.0f + x * x2,
			(z * w2) + y * x2,
			(-y * w2) + z * x2);
	}
	Vector3 GetBasisVector1()	const
	{
		//		return rotate(Vec3(0,1,0));
		const float y2 = y * 2.0f;
		const float w2 = w * 2.0f;
		return Vector3((-z * w2) + x * y2,
			(w * w2) - 1.0f + y * y2,
			(x * w2) + z * y2);
	}
	Vector3 GetBasisVector2() const
	{
		//		return rotate(Vec3(0,0,1));
		const float z2 = z * 2.0f;
		const float w2 = w * 2.0f;
		return Vector3((y * w2) + x * z2,
			(-x * w2) + y * z2,
			(w * w2) - 1.0f + z * z2);
	}

	const Vector3 RotateInv(const Vector3& v) const
		//	  const Vec3 rotateInv(const Vec3& v) const
	{
		const float vx = 2.0f * v.x;
		const float vy = 2.0f * v.y;
		const float vz = 2.0f * v.z;
		const float w2 = w * w - 0.5f;
		const float dot2 = (x*vx + y * vy + z * vz);
		return Vector3
		(
			(vx*w2 - (y * vz - z * vy)*w + x * dot2),
			(vy*w2 - (z * vx - x * vz)*w + y * dot2),
			(vz*w2 - (x * vy - y * vx)*w + z * dot2)
		);
		//		const Vec3 qv(x,y,z);
		//		return (v*(w*w-0.5f) - (qv.cross(v))*w + qv*(qv.dot(v)))*2;
	}

	static Quaternion CreateIdentity() { return { 0.0f, 0.0f, 0.0f, 1.0f }; }

	static Quaternion RotationQuaternion(const float angleRadian, const Vector3& axis);
	void Rotate(Vector3& object);
	void Rotate(float angle, Vector3& object);
	void MakeUnit();

	static Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
	{
		Quaternion qq = q1;

		if (t == 0.0f)
			return q0;
		else if (t == 1.0f)
			return q1;

		// Find the dot product
		float dot = (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) + (q0.w * q1.w);

		// Determine the direction of the rotation.
		if (dot < 0.0f)
		{
			dot = -dot;
			qq.x = -q1.x;
			qq.y = -q1.y;
			qq.z = -q1.z;
			qq.w = -q1.w;
		}
		else if (dot > 0.999f)
		{
			return Normalize(Lerp(q0, q1, t));
		}

		float theta = acosf(dot);
		float sintheta = sinf(theta);
		float scale0 = sinf(theta * (1.0f - t)) / sintheta;
		float scale1 = sinf(theta * t) / sintheta;

		// Perform the slerp
		return Quaternion
		(
			(q0.x * scale0) + (qq.x * scale1),
			(q0.y * scale0) + (qq.y * scale1),
			(q0.z * scale0) + (qq.z * scale1),
			(q0.w * scale0) + (qq.w * scale1)
		);

	}
	static Quaternion Lerp(const Quaternion& q0, const Quaternion& q1, float t)
	{
		return (q0 * (1.0f - t)) + (q1 * t);

	}
	
	std::string ToString() const
	{
		return std::to_string(w) + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
	}
};

}

#endif // !INCLUDED_VISHV_MATH_QUATERNION_H
