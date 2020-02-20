#ifndef INCLUDED_VISHV_MATH_META_REGISTRATION_H
#define INCLUDED_VISHV_MATH_META_REGISTRATION_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"

#include "Quaternion.h"

#include "Cube.h"
#include "Cuboid.h"
#include "Sphere.h"
#include "Transform.h"

//Primitive basic declaration
META_TYPE_DECLARE(Vishv::Math::Vector2)
META_TYPE_DECLARE(Vishv::Math::Vector3)
META_TYPE_DECLARE(Vishv::Math::Vector4)

META_TYPE_DECLARE(Vishv::Math::Matrix2)
META_TYPE_DECLARE(Vishv::Math::Matrix3)
META_TYPE_DECLARE(Vishv::Math::Matrix4)

META_TYPE_DECLARE(Vishv::Math::Quaternion)

namespace Vishv::Math
{
	void StaticMetaRegister();
}

#endif


