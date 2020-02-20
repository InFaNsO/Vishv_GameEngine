#ifndef INCLUDED_VISHV_MATH_SHAPES_CUBE_H
#define INCLUDED_VISHV_MATH_SHAPES_CUBE_H

#include "Shape3D.h"
#include "Constants.h"

namespace Vishv::Math::Shapes
{
	struct Cube : public Base::Shape3D
	{
		Cube() = default;
		float GetVolume() override
		{
			float len = mHalfLength * 2.0f;
			return len * len * len;
		}

		void SetLength(float length) { mHalfLength = length * 0.5f; }
		float GetLength() { return mHalfLength * 2.0f; }

	private:
		float mHalfLength = 1.0f;
	};
}

#endif // !INCLUDED_VISHV_MATH_SHAPES_SPHERE_H


