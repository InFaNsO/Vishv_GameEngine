#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_AABBINT_H
#define INCLUDED_VISHV_PHYSICS_AABBINT_H

namespace Vishv::Physics::IntData
{
	struct Vector3Int
	{
		Vector3Int() = default;
		Vector3Int(int X, int Y, int Z)
			:x(X)
			,y(Y)
			,z(Z)
		{
		}
		Vector3Int(const Vector3Int& other)
			: x(other.x)
			, y(other.y)
			, z(other.z)
		{
		}

		int x, y, z;

		Vector3Int operator-=(const Vector3Int& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}
		Vector3Int operator+=(const Vector3Int& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		Vector3Int operator- (const Vector3Int& other) const { return { x - other.x, y - other.y, z - other.z }; }
		Vector3Int operator+ (const Vector3Int& other) const { return { x + other.x, y + other.y, z + other.z }; }
	};

	struct AABBInt
	{
		AABBInt() = default;
		AABBInt(const AABBInt& other)
			:center(other.center)
			,min(other.min)
			,max(other.max)
		{
			
		}


		Vector3Int center;
		Vector3Int min;
		Vector3Int max;

		inline void Set(const Vector3Int& c, const Vector3Int& half)
		{
			center = c;
			min = c - half;
			max = c + half;
		}
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_AABBINT_H


