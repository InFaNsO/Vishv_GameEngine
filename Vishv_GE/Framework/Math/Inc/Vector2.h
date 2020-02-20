#ifndef INCLUDED_VISHV_MATH_VECTOR2_H
#define INCLUDED_VISHV_MATH_VECTOR2_H

namespace Vishv
{
namespace Math
{
struct Vector2
{
	union
	{
		struct { float x, y; };
		struct { float u, v; };
		std::array<float, 2> a;
	};

	constexpr Vector2() noexcept : Vector2(0.0f) {}
	constexpr Vector2(float f) noexcept : x(f), y(f) {}
	constexpr Vector2(float x, float y) noexcept : x(x), y(y) {}
	constexpr Vector2(const std::array<float, 2> &arr) noexcept : x(arr[0]), y(arr[1]) {}
	constexpr Vector2(const Vector2 &v) noexcept : x(v.x), y(v.y) {}
//	constexpr Vector2(const Vector3 &v) noexcept : x(v.x), y(v.y) {}

	float MagnitudeSq()const { return (x*x) + (y*y); }
	float Magnitude()const { return sqrt(MagnitudeSq()); }


	constexpr Vector2 operator-()								{ return { -x,-y}; }
	constexpr Vector2 operator+(const Vector2& other)			{ return { x + other.x, y + other.y }; }
	constexpr Vector2 operator*(const Vector2& other)			{ return { x * other.x, y * other.y }; }
	constexpr Vector2 operator*(float f)						{ return { x * f, y *f}; }
	constexpr Vector2 operator-(const Vector2& other)			{ return { x - other.x, y - other.y}; }
	constexpr Vector2 operator= (const Vector2& v)				{ x = v.x; y = v.y; return *this; }
	Vector2 operator/(float f)									{ VISHVASSERT(f != 0.0f, "[Vishv::Math::Vector2] devision by zero"); float div = 1 / f; return { x * div, y * div}; }

	inline float operator[](size_t i)				{ return a[i]; }

	bool operator<(const Vector2& other) const
	{
		return MagnitudeSq() < other.MagnitudeSq();
	}
	bool operator>(const Vector2& other) const
	{
		return MagnitudeSq() > other.MagnitudeSq();
	}

	Vector2 operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}
	Vector2 operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}
	Vector2 operator*=(float f)
	{
		x *= f;
		y *= f;

		return *this;
	}
	Vector2 operator/=(float f)
	{
		VISHVASSERT(f != 0.0f, "[Vishv::Math::Vector] devision by zero");

		float div = 1.0f / f;

		x *= f;
		y *= f;

		return *this;
	}	
	 bool operator==(const	Vector2& other)
	{
		return other.x == x && other.y == y;
	}
	bool operator!=(const	Vector2& other)
	{
		return !(other.x == x && other.y == y);
	}

	std::string ToString()
	{
		std::string n = std::to_string(x) + " " + std::to_string(y);
		return n;
	}
};

}
}

#endif //INCLUDED_VISHV_MATH_VECTOR2