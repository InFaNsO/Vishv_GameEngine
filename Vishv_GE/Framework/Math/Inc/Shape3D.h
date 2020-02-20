#ifndef INCLUDED_VISHV_MATH_SHAPE3D_H
#define INCLUDED_VISHV_MATH_SHAPE3D_H

#include "Transform.h"

namespace Vishv::Math::Shapes::Base {
	
struct Shape3D
{
	virtual float GetVolume() { return 0.0f; }
	Transform mTransform;
};
}

#endif // !INCLUDED_VISHV_MATH_SHAPES_H

