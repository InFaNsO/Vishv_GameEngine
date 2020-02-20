#ifndef INCLUDED_VISHV_MATH_SHAPES_SPHERE_H
#define INCLUDED_VISHV_MATH_SHAPES_SPHERE_H

#include "Shape3D.h"
#include "Constants.h"

namespace Vishv::Math::Shapes
{
	struct Sphere : public Base::Shape3D
	{
		Sphere() = default;
		float mRadius;
		float GetVolume() override
		{
			return Constans::Pi * (4.0f / 3.0f) * mRadius * mRadius * mRadius;
		}
	};
}

#endif // !INCLUDED_VISHV_MATH_SHAPES_SPHERE_H


