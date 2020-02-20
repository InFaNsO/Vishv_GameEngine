#include "Precompiled.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Matrix4.h"

#include "Quaternion.h"

#include "Transform.h"

#include "Convert.h"

Vishv::Math::Vector3 Vishv::Math::Convert::MatrixToPosition(Matrix4 & matrix)
{
	return Vector3(matrix._14, matrix._24, matrix._34);
}

Vishv::Math::Quaternion Vishv::Math::Convert::MatrixToQuaternion(Matrix4 & matrix)
{
	return Quaternion();
}

Vishv::Math::Transform Vishv::Math::Convert::MatrixToTransform(Matrix4 & matrix)
{
	return Transform();
}
