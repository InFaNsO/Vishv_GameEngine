#ifndef INCLUDED_VISHV_MATH_SHAPES_CAPSULE_H
#define INCLUDED_VISHV_MATH_SHAPES_CAPSULE_H

#include "Shape3D.h"
#include "Constants.h"

namespace Vishv::Math::Shapes
{
	struct Capsule : public Base::Shape3D
	{
		Capsule() = default;
		Capsule(float height, float radius, Vector3& pos)
			:mHalfHeight(height * 0.5f)
			, mRadius(radius)
		{
			mTransform.mPosition = pos;
		}
		float GetVolume() override
		{
			float roundV = Constans::Pi * (4.0f / 3.0f) * mRadius * mRadius * mRadius;
			float cylenderV = Constans::Pi * mRadius * mRadius * (mHalfHeight + mHalfHeight);
			return roundV + cylenderV;
		}

		float mRadius = 1.0f;
		void SetHeight(float length) { mHalfHeight = length * 0.5f; }
		float GetHeight() const { return mHalfHeight * 2.0f; }

	private:
		float mHalfHeight = 1.0f;
	};
}

#endif // !INCLUDED_VISHV_MATH_SHAPES_SPHERE_H


