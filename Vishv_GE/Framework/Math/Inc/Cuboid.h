#ifndef INCLUDED_VISHV_MATH_SHAPES_CUBOID_H
#define INCLUDED_VISHV_MATH_SHAPES_CUBOID_H

#include "Shape3D.h"
#include "Constants.h"
#include "Vector3.h"

namespace Vishv::Math::Shapes
{
	struct Cuboid : public Base::Shape3D
	{
		Cuboid() = default;
		Cuboid(Vector3& v, Vector3& pos)
			: mHalfX(v.x * 0.5f)
			, mHalfY(v.y * 0.5f)
			, mHalfZ(v.z * 0.5f)
		{
			mTransform.mPosition = pos;
		}
		Cuboid(float x, float y, float z)
			:mHalfX(x * 0.5f)
			, mHalfY(y * 0.5f)
			, mHalfZ(z * 0.5f)
		{
		}


		float GetVolume() override
		{
			return (mHalfX + mHalfX) * (mHalfY + mHalfY) * (mHalfZ + mHalfZ);
		}

		void SetLengthX(float length) { mHalfX = length * 0.5f; }
		float GetLengthX()const { return mHalfX * 2.0f; }

		void SetLengthY(float length) { mHalfY = length * 0.5f; }
		float GetLengthY()const { return mHalfY * 2.0f; }

		void SetLengthZ(float length) { mHalfZ = length * 0.5f; }
		float GetLengthZ()const { return mHalfZ * 2.0f; }

	private:
		float mHalfX = 1.0f;
		float mHalfY = 1.0f;
		float mHalfZ = 1.0f;
	};
}

#endif // !INCLUDED_VISHV_MATH_SHAPES_SPHERE_H


