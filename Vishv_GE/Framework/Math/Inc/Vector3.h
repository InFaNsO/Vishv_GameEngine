#ifndef INCLUDED_VISHV_MATH_VECTOR3_H
#define INCLUDED_VISHV_MATH_VECTOR3_H

namespace Vishv::Math
{
	struct Quaternion;

struct Vector3
{
	union
	{
		struct { float x, y, z; };
		std::array<float, 3> v;
	};

	constexpr Vector3()									noexcept : Vector3(0.0f) {}
	constexpr Vector3(float f)							noexcept : x(f), y(f), z(f) {}
	constexpr Vector3(float x, float y, float z)		noexcept : x(x), y(y), z(z) {}
	constexpr Vector3(const Vector3& v)					noexcept :x(v.x), y(v.y), z(v.z) {}			//Copy constructor
	inline    Vector3(std::array<float, 3> arr)			noexcept :x(arr[0]), y(arr[1]), z(arr[2]) {}

	//	constexpr Vector3(const Vector4& v) noexcept :x(v.x), y(v.y), z(v.z) {}			//Copy constructor for truncating vector 4

	//Operators
	constexpr Vector3 operator- ()							{ return { -x,-y, -z }; }
	constexpr Vector3 operator- (const Vector3& other) const { return { x - other.x, y - other.y, z - other.z }; }
	constexpr Vector3 operator+ (const Vector3& other) const		{ return { x + other.x, y + other.y, z + other.z }; }
	Vector3 operator* (const Vector3& other) const		{ return { x * other.x, y * other.y, z * other.z }; }
	constexpr Vector3 operator* (float f)							{ return { x * f, y *f, z * f }; }
			  Vector3 operator/ (float f)							{ VISHVASSERT(f != 0.0f, "[Vishv::Math::Vector3] devision by zero"); float div = 1 / f; return { x * div, y * div, z* div }; }
			  Vector3 operator* (const Quaternion& quat) const;


//	float Dot(const Vector3& other) const					{ return (x * other.x) + (y * other.y) + (z * other.z); }
	float MagnitudeSq() const								{ return (x*x) + (y*y) + (z*z); }
	float Magnitude() const 								{ return sqrt(MagnitudeSq()); }

	inline void Normalize()
	{
		float len = Magnitude();
		VISHVASSERT(len != 0.0f, "[Vishv::Math::Vector3] 0 magnitude Vector!!!!.");
		x /= len;
		y /= len;
		z /= len;
	}

	inline Vector3 Normalized() const
	{
		float len = 1 / Magnitude();
		return Vector3(x * len, y * len, z * len);
	}

	void Rotate(const Quaternion& quat);

	//equals operators
	constexpr bool operator==(const Vector3& other)
	{
		return (other.x == x && other.y == y && other.z == z);
	}
	constexpr bool operator!=(const Vector3& other)
	{
		return !(other.x == x && other.y == y && other.z == z);
	}
	//constexpr bool operator==(const Vector4& other)
	//{
	//	if (other.x == x && other.y == y && other.z == z)
	//	{
	//		return true;
	//	}
	//	return false;
	//}

	Vector3 operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}
	Vector3 operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}
	Vector3 operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}
	Vector3 operator*=(const Quaternion& quat);

	Vector3 operator/=(float f)
	{
		VISHVASSERT(f != 0.0f, "[Vishv::Math::Vector] devision by zero");

		float div = 1.0f / f;

		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	Vector3 Cross(const Vector3& v)
	{
		return { (y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x) };
	}

	Vector3 operator%= (const Vector3& v)
	{
		x = (y * v.z) - (z * v.y);
		y = (z * v.x) - (x * v.z);
		z = (x * v.y) - (y * v.x);
	}
	Vector3 operator% (const Vector3& v)
	{
		return { (y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x) };
	}

	static Vector3 Invert(const Vector3& v)
	{
		return Vector3(-v.x, -v.y, -v.z);
	}

	static void MakeOrthonormal(Vector3& v1, Vector3& v2, Vector3& v3)
	{
		v1.Normalize();
		v3 = v1 % v2;
		VISHVASSERT(v3.MagnitudeSq() != 0.0, "The pair is parellel");
		v3.Normalize();
		v2 = v3 % v1;
	}

	//Physics Functions
	constexpr void UpdateVelocity(const Vector3& v, float deltaTime)
	{
		x += v.x * deltaTime;
		y += v.y * deltaTime;
		z += v.z * deltaTime;
	}

	float Dot(const Vector3& other)const { return (x * other.x) + (y * other.y) + (z * other.z); }

	Vector3 Project(const Vector3& base) const
	{
		float dot = Dot(base);
		float magSq = base.MagnitudeSq();
		return base * (dot / magSq);
	}
	Vector3 ProjectX()
	{
		return { x, 0.0f, 0.0f };
	}
	Vector3 ProjectY()
	{
		return { 0.0f, y, 0.0f };
	}
	Vector3 ProjectZ()
	{
		return { 0.0f , 0.0f, z };
	}

	float GetAngle(const Vector3& other)
	{
		float numerator = Dot(other);
		float deno = Magnitude() * other.Magnitude();
		return numerator / deno;
	}
	static float GetAngle(const Vector3 &v1, const Vector3& v2)
	{
		auto numerator = v1.Dot(v2);
		auto deno = v1.Magnitude() * v2.Magnitude();
		return numerator / deno;
	}

	static Vector3 Project(const Vector3& vector, const Vector3& base)
	{
		auto dot = vector.Dot(base);
		auto magSq = base.MagnitudeSq();
		return base * (dot / magSq);
	}

	static Vector3 Lerp(const Vector3& v0, const Vector3& v1, float t)
	{
		return (v0 * (1.0f - t)) + (v1 * t);
	}

	//utility
	std::string ToString() const
	{
		std::string n = std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
		return n;
	}
};

constexpr static Vector3 XAxis { 1.0f, 0.0f, 0.0f };
constexpr static Vector3 YAxis { 0.0f, 1.0f, 0.0f };
constexpr static Vector3 ZAxis { 0.0f, 0.0f, 1.0f };
constexpr static Vector3 Zero  { 0.0f, 0.0f, 0.0f };


}	//Vishv::Math


#endif // !INCLUDED_VISHV_MATH_VECTOR3_H

