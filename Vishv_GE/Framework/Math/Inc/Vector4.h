#ifndef INCLUDED_VISHV_MATH_VECTOR4_H
#define INCLUDED_VISHV_MATH_VECTOR4_H

#include "Vector3.h"

namespace Vishv
{
namespace Math
{

struct Vector4
{
	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };
	union { float w; float a; };

	constexpr Vector4 ()										noexcept : Vector4(0.0f) {}
	constexpr Vector4 (float f)									noexcept : x(f), y(f), z(f), w(f) {}
	constexpr Vector4 (float x, float y, float z)				noexcept : x(x), y(y), z(z), w(1.0f) {}
	constexpr Vector4 (float x, float y, float z, float w)		noexcept : x(x), y(y), z(z), w(w) {}
	constexpr Vector4 (const Vector4& v)						noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}
	constexpr Vector4 (const Vector3& v)						noexcept : x(v.x), y(v.y), z(v.z), w(1.0f) {}
//	constexpr Vector4 (const Vector3& v, float w)				noexcept : x(v.x), y(v.y), z(v.z), w(w) {}

	constexpr Vector4 operator- ()const							{ return { -x,-y, -z }; }
	constexpr Vector4 operator+ (const Vector4& other) const	{ return { x + other.x, y + other.y, z + other.z }; }
	constexpr Vector4 operator* (const Vector4& v) const		{ return { x * v.x, y * v.y, z * v.z }; }
	constexpr Vector4 operator* (float f) const					{ return { x * f, y *f, z * f }; }
	constexpr Vector4 operator- (const Vector4& other) const	{ return { x - other.x, y - other.y, z - other.z }; }
	constexpr Vector4 operator= (const Vector4& v)				{ x = v.x; y = v.y; z = v.z; w = v.w; return *this; }//x = v.x; y = v.y; z = v.z; w = v.w; }
	Vector4 operator/ (float f) const							{ VISHVASSERT(f != 0.0f, "[Vishv::Math::Vector4] devision by zero"); float div = 1 / f; return { x * div, y * div, z* div }; }
	inline float operator[] (int i) const
	{
		VISHVASSERT(i >= 0 && i <= 3, "[Vishv::Math::Vector4] index out of range.");
		switch (i)
		{
		case 0:
			return x;
		case 1: 
			return y;
		case 2:
			return z;
		default:
			return w;
		}
	}
    constexpr bool operator==(const	Vector4& other)
    {
	    if (other.x == x && other.y == y && other.z == z && other.w == w)
	    {
	  	  return true;
	    }
	    return false;
    }
	constexpr bool operator!=(const Vector4& other)
	{
		return !(other.x == x && other.y == y && other.z == z && other.w == w);
	}

	constexpr bool operator<(const Vector4& other) const
	{
		if (other.x > x && other.y > y && other.z > z && other.w > w)
		{
			return true;
		}
		return false;
	}
	constexpr bool operator>(const Vector4& other) const
	{
		if (other.x < x && other.y < y && other.z < z && other.w < w)
		{
			return true;
		}
		return false;
	}
	Vector4 operator%= (const Vector4& v)
	{
		x = (y * v.z) - (z * v.y);
		y = (z * v.x) - (x * v.z);
		z = (x * v.y) - (y * v.x);
		w = 1.0f;
	}
	Vector4 operator% (const Vector4& v)
	{
		return { (y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x), 1.0f };
	}


	Vector4 operator+=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}
	Vector4 operator-=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}
	Vector4 operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}
	Vector4 operator/=(float f)
	{
		VISHVASSERT(f != 0.0f, "[Vishv::Math::Vector] devision by zero");

		float div = 1.0f / f;

		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	float Dot(const Vector4& other)const { return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w); }
	float MagnitudeSq()const  { return (x*x) + (y*y) + (z*z); }
	float Magnitude()const  { return sqrt(MagnitudeSq()); }

	void Max(const Vector4& v)
	{
		x = x > v.x ? x : v.x;
		y = y > v.y ? y : v.y;
		z = z > v.z ? z : v.z;
		w = w > v.w ? w : v.w;
	}

	void Min(const Vector4& v)
	{
		x = x < v.x ? x : v.x;
		y = y < v.y ? y : v.y;
		z = z < v.z ? z : v.z;
		w = w > v.w ? w : v.w;
	}

	inline void Normalize()
	{
		float len = Magnitude();
		VISHVASSERT(len != 0.0f, "[Vishv::Math::Vector3] 0 magnitude Vector!!!!.");
		x /= len;
		y /= len;
		z /= len;
	}

	void Invert()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	static Vector4 Invert(const Vector4& v)
	{
		return Vector4(-v.x, -v.y, -v.z);
	}

	Vector4 Cross(const Vector4& v)
	{
		return { (y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x), 1.0f };
	}
	
	static void MakeOrthonormal(Vector4& v1, Vector4& v2, Vector4& v3)
	{
		v1.Normalize();
		v3 = v1 % v2;
		VISHVASSERT(v3.MagnitudeSq() != 0.0, "The pair is parellel");
		v3.Normalize();
		v2 = v3 % v1;
	}

	static Vector4 Interpolate(Vector4& v0, Vector4& v1, float t)
	{
		return (v0 * (1.0f - t)) + (v1 * t);
	}

	struct Color
	{
		constexpr static Vector4 Black()			{ return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }
		constexpr static Vector4 Gray()				{ return Vector4(0.5f, 0.5f, 0.5f, 1.0f); }
		constexpr static Vector4 DarkGray()			{ return Vector4(0.25f, 0.25f, 0.25f, 1.0f); }

		constexpr static Vector4 Blue()				{ return Vector4(0.0f, 0.0f, 1.0f, 1.0f); }
		constexpr static Vector4 Navy()				{ return Vector4(0.0f, 0.0f, 0.5f, 1.0f); }
		constexpr static Vector4 Aqua()				{ return Vector4(0.0f, 1.0f, 1.0f, 1.0f); }
		constexpr static Vector4 Cyan()				{ return Vector4(0.0f, 1.0f, 1.0f, 1.0f); }
		

		constexpr static Vector4 Green()			{ return Vector4(0.0f, 0.5f, 0.0f, 1.0f); }
		constexpr static Vector4 Teal()				{ return Vector4(0.0f, 0.5f, 0.5f, 1.0f); }
		constexpr static Vector4 Lime()				{ return Vector4(0.0f, 1.0f, 0.0f, 1.0f); }
		constexpr static Vector4 Olive()			{ return Vector4(0.5f, 0.5f, 0.0f, 1.0f); }


		constexpr static Vector4 Red()				{ return Vector4(1.0f, 0.0f, 0.0f, 1.0f); }
		constexpr static Vector4 LightRed()			{ return Vector4(1.0f, 0.5f, 0.5f, 1.0f); }
		constexpr static Vector4 Orange()			{ return Vector4(1.0f, 0.5f, 0.0f, 1.0f); }
		constexpr static Vector4 Magenta()			{ return Vector4(1.0f, 0.0f, 1.0f, 1.0f); }


		static constexpr Vector4 Yellow()			{ return Vector4(1.0f, 1.0f, 0.0f, 1.0f); }
		static constexpr Vector4 Gold()				{ return Vector4(0.82f, 0.68f, 0.21f, 1.0f); }

		static constexpr Vector4 White()			{ return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
		static constexpr Vector4 Silver()			{ return Vector4(0.75f, 0.75f, 0.75f, 1.0f); }


	};	//Color

	//utility
	std::string ToString()
	{
		std::string n = std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + " " + std::to_string(w);
		return n;
	}
};


}// namespace Math
}// namespace Vishv

#endif // !INCLUDED_VISHV_MATH_VECTOR4_H
