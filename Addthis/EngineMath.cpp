//====================================================================================================
// SIEGE - Super Innovative Exciting Game Engine
// Copyright (c) 2020 Peter Chan. All rights reserved.
//====================================================================================================

#include "Precompiled.h"
#include "EngineMath.h"

using namespace Siege;
using namespace Siege::Math;

const Vector2 Vector2::XAxis{ 1.0f, 0.0f };
const Vector2 Vector2::YAxis{ 0.0f, 1.0f };

const Vector3 Vector3::Zero{ 0.0f };
const Vector3 Vector3::One{ 1.0f };
const Vector3 Vector3::XAxis{ 1.0f, 0.0f, 0.0f };
const Vector3 Vector3::YAxis{ 0.0f, 1.0f, 0.0f };
const Vector3 Vector3::ZAxis{ 0.0f, 0.0f, 1.0f };

const Quaternion Quaternion::Zero{ 0.0f, 0.0f, 0.0f, 0.0f };
const Quaternion Quaternion::Identity{ 0.0f, 0.0f, 0.0f, 1.0f };

Quaternion Quaternion::RotationAxis(const Vector3& axis, float rad)
{
	const float c = cos(rad * 0.5f);
	const float s = sin(rad * 0.5f);
	const Math::Vector3 a = Math::Normalize(axis);
	return Quaternion(a.x * s, a.y * s, a.z * s, c);
}

const Matrix4 Matrix4::Identity
{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f,
};

Matrix4 Matrix4::RotationAxis(const Vector3& axis, float rad)
{
	const Vector3 u = Normalize(axis);
	const float x = u.x;
	const float y = u.y;
	const float z = u.z;
	const float s = sin(rad);
	const float c = cos(rad);

	return {
		c + (x * x * (1.0f - c)),
		x * y * (1.0f - c) + z * s,
		x * z * (1.0f - c) - y * s,
		0.0f,

		x * y * (1.0f - c) - z * s,
		c + (y * y * (1.0f - c)),
		y * z * (1.0f - c) + x * s,
		0.0f,

		x * z * (1.0f - c) + y * s,
		y * z * (1.0f - c) - x * s,
		c + (z * z * (1.0f - c)),
		0.0f,

		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4 Matrix4::RotationQuaternion(const Quaternion& q)
{
	return
	{
		1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
		(2.0f * q.x * q.y) + (2.0f * q.z * q.w),
		(2.0f * q.x * q.z) - (2.0f * q.y * q.w),
		0.0f,

		(2.0f * q.x * q.y) - (2.0f * q.z * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
		(2.0f * q.y * q.z) + (2.0f * q.x * q.w),
		0.0f,

		(2.0f * q.x * q.z) + (2.0f * q.y * q.w),
		(2.0f * q.y * q.z) - (2.0f * q.x * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	};
}

Quaternion Math::Slerp(Quaternion q0, Quaternion q1, float t)
{
	// Find the dot product
	float dot = (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) + (q0.w * q1.w);

	// Determine the direction of the rotation.
	if (dot < 0.0f)
	{
		dot = -dot;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
		q1.w = -q1.w;
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
		(q0.x * scale0) + (q1.x * scale1),
		(q0.y * scale0) + (q1.y * scale1),
		(q0.z * scale0) + (q1.z * scale1),
		(q0.w * scale0) + (q1.w * scale1)
	);
}

bool Math::Intersect(const Ray& ray, const Vector3& a, const Vector3& b, const Vector3& c, float& distance)
{
	// Reference: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

	// Find vectors for two edges sharing V1
	Vector3 e1 = b - a;
	Vector3 e2 = c - a;

	// Begin calculating determinant - also used to calculate u parameter
	Vector3 P = Cross(ray.direction, e2);

	// If determinant is near zero, ray lies in plane of triangle
	float det = Dot(e1, P);
	// NOT CULLING
	if (IsZero(det))
	{
		return false;
	}

	float inv_det = 1.0f / det;

	// Calculate distance from V1 to ray origin
	Vector3 T = ray.origin - a;

	// Calculate u parameter and test bound
	float u = Dot(T, P) * inv_det;

	// The intersection lies outside of the triangle
	if (u < 0.0f || u > 1.0f)
	{
		return false;
	}

	// Prepare to test v parameter
	Vector3 Q = Cross(T, e1);

	// Calculate V parameter and test bound
	float v = Dot(ray.direction, Q) * inv_det;

	// The intersection lies outside of the triangle
	if (v < 0.0f || u + v  > 1.0f)
	{
		return false;
	}

	// Ray intersection
	float t = Dot(e2, Q) * inv_det;
	if (t <= 0.0f)
	{
		// No hit, no win
		return false;
	}

	distance = t;
	return true;
}

bool Math::Intersect(const Ray& ray, const Plane& plane, float& distance)
{
	const float orgDotN = Dot(ray.origin, plane.normal);
	const float dirDotN = Dot(ray.direction, plane.normal);

	// Check if ray is parallel to the plane
	if (IsZero(dirDotN))
	{
		if (IsZero(orgDotN - plane.distance))
		{
			distance = 0.0f;
			return true;
		}
		else
		{
			return false;
		}
	}

	// Compute distance
	distance = (plane.distance - orgDotN) / dirDotN;
	return true;
}

bool Math::Intersect(const Ray& ray, const AABB& aabb, float& distEntry, float& distExit)
{
	// https://truesculpt.googlecode.com/hg-history/Release%25200.8/Doc/ray_box_intersect.pdf

	// Returns true if ray intersects bounding box
	// Sets d1 to entry distance, d2 to exit distance (along ray.direction)

	Vector3 boxMin = aabb.center - aabb.extend;
	Vector3 boxMax = aabb.center + aabb.extend;
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	float divx = 1.0f / ray.direction.x;
	float divy = 1.0f / ray.direction.y;
	float divz = 1.0f / ray.direction.z;

	if (divx >= 0.0f)
	{
		tmin = (boxMin.x - ray.origin.x) * divx;
		tmax = (boxMax.x - ray.origin.x) * divx;
	}
	else
	{
		tmin = (boxMax.x - ray.origin.x) * divx;
		tmax = (boxMin.x - ray.origin.x) * divx;
	}
	if (divy >= 0.0f)
	{
		tymin = (boxMin.y - ray.origin.y) * divy;
		tymax = (boxMax.y - ray.origin.y) * divy;
	}
	else
	{
		tymin = (boxMax.y - ray.origin.y) * divy;
		tymax = (boxMin.y - ray.origin.y) * divy;
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		return false;
	}

	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	if (divz >= 0.0f)
	{
		tzmin = (boxMin.z - ray.origin.z) * divz;
		tzmax = (boxMax.z - ray.origin.z) * divz;
	}
	else
	{
		tzmin = (boxMax.z - ray.origin.z) * divz;
		tzmax = (boxMin.z - ray.origin.z) * divz;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return false;
	}

	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	distEntry = tmin;
	distExit = tmax;
	return true;
}

bool Math::Intersect(const Ray& ray, const OBB& obb, float& distEntry, float& distExit)
{
	// Compute the local-to-world/world-to-local matrices
	Matrix4 matTrans = Matrix4::Translation(obb.center);
	Matrix4 matRot = Matrix4::RotationQuaternion(obb.rot);
	Matrix4 matWorld = matRot * matTrans;
	Matrix4 matWorldInv = Inverse(matWorld);

	// Transform the ray into the OBB's local space
	Vector3 org = TransformCoord(ray.origin, matWorldInv);
	Vector3 dir = TransformNormal(ray.direction, matWorldInv);

	AABB aabb{ Vector3::Zero, obb.extend };
	return Math::Intersect(Ray{ org, dir }, aabb, distEntry, distExit);
}

bool Math::Intersect(const Ray& ray, const Sphere& sphere, float& distance)
{
	Vector3 originToCenter = sphere.center - ray.origin;
	float orignToCenterDist = Magnitude(originToCenter);

	// Check if sphere is behind the origin
	const float d = Dot(originToCenter, ray.direction);
	if (d < 0.0f)
	{
		// Check if origin is inside sphere
		if (orignToCenterDist > sphere.radius)
		{
			// No intersection
			return false;
		}
		else
		{
			Vector3 centerOnRay = ray.origin + ray.direction * d;
			float side = sqrt(Sqr(sphere.radius) - MagnitudeSqr(sphere.center - centerOnRay));
			distance = side - Magnitude(centerOnRay - ray.origin);
			return true;
		}
	}

	// Center of sphere projects on the ray
	Vector3 centerOnRay = ray.origin + ray.direction * d;

	// Check if projected center is inside sphere
	float centerToRayDist = Magnitude(sphere.center - centerOnRay);
	if (centerToRayDist > sphere.radius)
	{
		// No intersection
		return false;
	}

	float side = sqrt(Sqr(sphere.radius) - Sqr(centerToRayDist));
	if (orignToCenterDist > sphere.radius)
	{
		// Origin is outside sphere
		distance = Magnitude(centerOnRay - ray.origin) - side;
	}
	else
	{
		// Origin is inside sphere
		distance = Magnitude(centerOnRay - ray.origin) + side;
	}
	return true;
}

bool Math::Intersect(const Vector3& point, const AABB& aabb)
{
	const Vector3 test = point - aabb.center;
	if (abs(test.x) > aabb.extend.x) return false;
	if (abs(test.y) > aabb.extend.y) return false;
	if (abs(test.z) > aabb.extend.z) return false;
	return true;
}

bool Math::Intersect(const Vector3& point, const OBB& obb)
{
	// Compute the local-to-world/world-to-local matrices
	Matrix4 matTrans = Matrix4::Translation(obb.center);
	Matrix4 matRot = Matrix4::RotationQuaternion(obb.rot);
	Matrix4 matWorld = matRot * matTrans;
	Matrix4 matWorldInv = Inverse(matWorld);

	// Transform the point into the OBB's local space
	Vector3 localPoint = TransformCoord(point, matWorldInv);
	AABB aabb{ Vector3::Zero, obb.extend };

	// Test against local AABB
	return Math::Intersect(localPoint, aabb);
}

bool Math::Intersect(const AABB& a, const AABB& b)
{
	auto minA = a.Min();
	auto maxA = a.Max();
	auto minB = b.Min();
	auto maxB = b.Max();
	if (maxA.x < minB.x || maxA.y < minB.y || maxA.z < minB.z ||
		minA.x > maxB.x || minA.y > maxB.y || minA.z > maxB.z)
		return false;
	return true;
}
