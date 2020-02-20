#include "Precompiled.h"
#include "Matrix3.h"
#include "Vector2.h"
#include "Vector3.h"

void Vishv::Math::Matrix3::SetRow(const Vector3& row1, const Vector3& row2, const Vector3& row3)
{
	_11 = row1.x; _12 = row1.y; _13 = row1.z;
	_21 = row2.x; _22 = row2.y; _23 = row2.z;
	_31 = row3.x; _32 = row3.y; _33 = row3.z;
}
void Vishv::Math::Matrix3::SetColumn(const Vector3& col1, const Vector3& col2, const Vector3& col3)
{
	_11 = col1.x; _12 = col2.y; _13 = col3.z;
	_21 = col1.x; _22 = col2.y; _23 = col3.z;
	_31 = col1.x; _32 = col2.y; _33 = col3.z;
}

constexpr Vishv::Math::Matrix3 Vishv::Math::Matrix3::operator* (Matrix3 &other)
{
	Matrix3 mat;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			Vector3 row(GetRow(i));
			Vector3 col(other.GetCol(j));

			float val = 0.0f;
			for (int i = 0; i < size; ++i)
			{
				val += row.v[i] * col.v[i];
			}

			mat.Set(i, j, val);
		}
	}

	return mat;
}
void Vishv::Math::Matrix3::Scale(const Vector2& v)
{
	_11 *= v.x;
	_22 *= v.y;
}
void Vishv::Math::Matrix3::Translate(const Vector2& v)
{
	_13 += v.x;
	_23 += v.y;
}
Vishv::Math::Matrix3 Vishv::Math::Matrix3::ScaleMatrix(const Vector2& v)
{
	Matrix3 m(Identity());
	m.Scale(v);
	return m;
}

