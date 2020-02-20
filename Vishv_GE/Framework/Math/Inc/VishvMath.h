#ifndef INCLUDED_VISHV_VISHVMATH_H
#define INCLUDED_VISHV_VISHVMATH_H

#include "Common.h"

#include "MetaRegistration.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Quaternion.h"

#include "Matrix4.h"
#include "Matrix3.h"
#include "Matrix2.h"

#include "Constants.h"
#include "Bounds3.h"

#include "Transform.h"

#include "Convert.h"

//Shapes
#include "Shape3D.h"
#include "Sphere.h"
#include "Cube.h"
#include "Cuboid.h"
#include "Capsule.h"

#include "VishvRandom.h"

namespace Vishv
{
namespace Math
{
	constexpr float Max(float a, float b)
	{
		return a < b ? b : a;
	}
	constexpr float Min(float a, float b)
	{
		return a > b ? b : a;
	}

	constexpr int Max(int a, int b)
	{
		return a < b ? b : a;
	}
	constexpr int Min(int a, int b)
	{
		return a > b ? b : a;
	}

	constexpr Vector3 Max(Vector3 a, Vector3 b)
	{
		return a.MagnitudeSq() < b.MagnitudeSq() ? b : a;
	}
	constexpr Vector3 Min(Vector3 a, Vector3 b)
	{
		return a.MagnitudeSq() > b.MagnitudeSq() ? b : a;
	}

	constexpr Vector3 Cross(const Vector3 &v0, const Vector3 & v1)
	{
		return { (v0.y * v1.z) - (v0.z * v1.y), (v0.z * v1.x) - (v0.x * v1.z), (v0.x * v1.y) - (v0.y * v1.x) };
	}
	constexpr Vector4 Cross(const Vector4 &v0, const Vector4 & v1)
	{
		return { (v0.y * v1.z) - (v0.z * v1.y), (v0.z * v1.x) - (v0.x * v1.z), (v0.x * v1.y) - (v0.y * v1.x), 1.0f };
	}

	constexpr float Dot(const Vector2 &v0, const Vector2 & v1)
	{
		return ((v0.x * v1.x) + (v0.y * v1.y));
	}
	constexpr float Dot(const Vector3 &v0, const Vector3 & v1)
	{
		return ((v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z));
	}
	constexpr float Dot(const Vector4 &v0, const Vector4 & v1)
	{
		return ((v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z));
	}

	inline float Magnitude(const Vector2 &v)
	{
		return sqrtf(Dot(v, v));
	}
	inline float Magnitude(const Vector3 &v)
	{
		return sqrtf(Dot(v, v));
	}
	inline float Magnitude(const Vector4 &v)
	{
		return sqrtf(Dot(v, v));
	}

	constexpr float MagnitudeSqr(const Vector2 &v)
	{
		return Dot(v, v);
	}
	constexpr float MagnitudeSqr(const Vector3 &v)
	{
		return Dot(v, v);
	}
	constexpr float MagnitudeSqr(const Vector4 &v)
	{
		return Dot(v, v);
	}

	inline float GetAngle(const Vector2& v0, const Vector2& v1)
	{
		return acosf(Magnitude(v0) * Magnitude(v1));
	}
	inline float GetAngle(const Vector3& v0, const Vector3& v1)
	{
		return acosf((Dot(v0,v1)) / (Magnitude(v0) * Magnitude(v1)));
	}
	inline float GetAngle(const Vector4& v0, const Vector4& v1)
	{
		return acosf(Magnitude(v0) * Magnitude(v1));
	}

	inline Vector2 Normalize(const Vector2& v0)
	{
		float len = Magnitude(v0);
		return Vector2(v0.x / len, v0.y / len);
	}
	inline Vector3 Normalize(const Vector3& v0)
	{
		float len = Magnitude(v0);
		return Vector3(v0.x / len, v0.y / len, v0.z / len);
	}
	inline Vector4 Normalize(const Vector4& v0) 
	{
		float len = Magnitude(v0);
		return Vector4(v0.x / len, v0.y / len, v0.z / len);
	}

	inline float Abs(float f)
	{
		return f < 0.0f ? -f : f;

	}
	inline float Sqr(float f)
	{
		return f * f;
	}
	inline float Sqrt(float f)
	{
		return sqrtf(f);
	}

	inline void MakeOrthonormalBasis(Vector3 &v0, Vector3 &v1, Vector3 &v2)
	{
		v0.Normalize();
		v2 = Cross(v0, v1);
		VISHVASSERT(MagnitudeSqr(v2) != 0.0f, "[Vishv::Math::MakeOrthonormalBasis] vectors are parellel.");
		v2.Normalize();
		v1 = Cross(v2, v1);
		v1.Normalize();
	}

	constexpr Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
	{
		return {
			(v.x * m._11) + (v.y * m._21) + (v.z * m._31) + m._41,
			(v.x * m._12) + (v.y * m._21) + (v.z * m._31) + m._41,
			(v.x * m._13) + (v.y * m._21) + (v.z * m._31) + m._41
		};
	}


}
}


#endif // !INCLUDED_MATH
