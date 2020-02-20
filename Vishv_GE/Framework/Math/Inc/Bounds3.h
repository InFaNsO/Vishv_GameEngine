#ifndef INCLUDED_VISHV_MATH_BOUNDS3_H
#define INCLUDED_VISHV_MATH_BOUNDS3_H

#include "Vector4.h"

namespace Vishv::Math {

struct Bounds3
{
	Vector4 mMinimum;
	Vector4 mMaximum;

	void Set(const Vector4& min, const Vector4& max)
		{
			mMaximum = max;
			mMinimum = min;
		}
	void SetEmpty()
		{
			Set(Vector4(), Vector4());
		}
	void SetMax()
		{
			Set(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
		}
	void Include(const Vector4& v)
		{
			mMaximum.Max(v);
			mMinimum.Min(v);
		}
	void Combine(const Bounds3& b2)
		{
			// - if we're empty, min = MAX,MAX,MAX => min will be b2 in all cases => it will copy b2, ok
			// - if b2 is empty, the opposite happens => keep us unchanged => ok
			// => same behavior as before, automatically
			mMinimum.Min(b2.mMinimum);
			mMaximum.Max(b2.mMaximum);
		}
	bool IsEmpty() const
		{
			// Consistency condition for (Min, Max) boxes: min < max
			// TODO: PT: should we test against the explicit pattern ?
			if (mMinimum.x < mMaximum.x)	return false;
			if (mMinimum.y < mMaximum.y)	return false;
			if (mMinimum.z < mMaximum.z)	return false;
			return true;
		}
	bool Intersects(const Bounds3& b) const
		{
			if ((b.mMinimum.x > mMaximum.x) || (mMinimum.x > b.mMaximum.x)) return false;
			if ((b.mMinimum.y > mMaximum.y) || (mMinimum.y > b.mMaximum.y)) return false;
			if ((b.mMinimum.z > mMaximum.z) || (mMinimum.z > b.mMaximum.z)) return false;
			return true;
		}
	bool Intersects2D(const Bounds3& b, unsigned axis) const
	{
		// TODO: PT: could be static and like this:
		// static unsigned i[3] = { 1,2,0,1 };
		// const unsigned ii = i[axis];
		// const unsigned jj = i[axis+1];
		const unsigned i[3] = { 1,0,0 };
		const unsigned j[3] = { 2,2,1 };
		const unsigned ii = i[axis];
		const unsigned jj = j[axis];
		if ((b.mMinimum[ii] > mMaximum[ii]) || (mMinimum[ii] > b.mMaximum[ii])) return false;
		if ((b.mMinimum[jj] > mMaximum[jj]) || (mMinimum[jj] > b.mMaximum[jj])) return false;
		return true;
	}
	bool Contain(const Vector4& v)
	{
		if ((v.x < mMinimum.x) || (v.x > mMaximum.x)) return false;
		if ((v.y < mMinimum.y) || (v.y > mMaximum.y)) return false;
		if ((v.z < mMinimum.z) || (v.z > mMaximum.z)) return false;
		return true;
	}
	Vector4 GetCenter() const
	{
		Vector4 center(mMinimum);
		center += mMaximum;
		center *= 0.5f;
	}
	Vector4 GetDimensions() const
	{
		Vector4 d(mMaximum);
		d -= mMinimum;
		return d;
	}
	Vector4 GetExtents() const
	{
		Vector4 e(mMaximum);
		e -= mMinimum;
		e *= 0.5f;
	}
	void SetCenterExtents(const Vector4& c, const Vector4& e)
	{
		mMinimum = c - e;
		mMaximum = c + e;
	}
	void Scale(float scale)
	{
		Vector4 center(GetCenter()), extents(GetExtents());
		SetCenterExtents(center, extents * scale);
	}
	void Fatten(float distance)
	{
		mMinimum.x -= distance;
		mMinimum.y -= distance;
		mMinimum.z -= distance;

		mMaximum.x += distance;
		mMaximum.y += distance;
		mMaximum.z += distance;
	}
};

}

#endif // !INCLUDED_VISHV_MATH_BOUNDS3_H
