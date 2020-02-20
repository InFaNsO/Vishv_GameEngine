#include "Precompiled.h"
#include "MetaRegistration.h"

//Primitive basic defeination
META_TYPE_DEFINE(Vishv::Math::Vector2, Vector2)
META_TYPE_DEFINE(Vishv::Math::Vector3, Vector3)
META_TYPE_DEFINE(Vishv::Math::Vector4, Vector4)

META_TYPE_DEFINE(Vishv::Math::Matrix2, Matrix2)
META_TYPE_DEFINE(Vishv::Math::Matrix3, Matrix3)
META_TYPE_DEFINE(Vishv::Math::Matrix4, Matrix4)

META_TYPE_DEFINE(Vishv::Math::Quaternion, Quaternion)

void Vishv::Math::StaticMetaRegister()
{
//	META_REGISTER(Vector3);
	META_REGISTER(Transform);
}

