#include "Precompiled.h"
#include "Matrix4.h"

#include "Quaternion.h"
#include "Vector4.h"

#include "Transform.h"

Vishv::Math::Matrix4::Matrix4(const Quaternion & q)
	: _11(1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z))		, _12((2.0f * q.x * q.y) + (2.0f * q.z * q.w))				, _13((2.0f * q.x * q.z) - (2.0f * q.y * q.w))			, _14(0.0f)
	, _21((2.0f * q.x * q.y) - (2.0f * q.z * q.w))				, _22(1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z))		, _23((2.0f * q.y * q.z) + (2.0f * q.x * q.w))			, _24(0.0f)
	, _31((2.0f * q.x * q.z) + (2.0f * q.y * q.w))				, _32((2.0f * q.y * q.z) - (2.0f * q.x * q.w))				, _33(1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y))	, _34(0.0f)
	, _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
{
}

Vishv::Math::Matrix4::Matrix4(const Quaternion & q, const Vector4 & pos)
	: _11(1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z)), _12((2.0f * q.x * q.y) + (2.0f * q.z * q.w)), _13((2.0f * q.x * q.z) - (2.0f * q.y * q.w)), _14(0.0f)
	, _21((2.0f * q.x * q.y) - (2.0f * q.z * q.w)), _22(1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z)), _23((2.0f * q.y * q.z) + (2.0f * q.x * q.w)), _24(0.0f)
	, _31((2.0f * q.x * q.z) + (2.0f * q.y * q.w)), _32((2.0f * q.y * q.z) - (2.0f * q.x * q.w)), _33(1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y)), _34(0.0f)
	, _41(pos.x), _42(pos.y), _43(pos.z), _44(1.0f)
{
}


Vishv::Math::Matrix4::Matrix4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4)
	: _11(row1.x), _12(row1.y), _13(row1.z), _14(row1.w)
	, _21(row2.x), _22(row2.y), _23(row2.z), _24(row2.w)
	, _31(row3.x), _32(row3.y), _33(row3.z), _34(row3.w)
	, _41(row4.x), _42(row4.y), _43(row4.z), _44(row4.w)
{
}

Vishv::Math::Vector3 Vishv::Math::Matrix4::GetTranslation()
{
	return { _41, _42, _43 };
}

void Vishv::Math::Matrix4::SetRow(int index, const Vector4& row)
{
	VISHVASSERT(index >= 0 && index <= 3, "[Vishv::Math::Matrix4::SetRow] index out of bounds.");
	int i = index * 4;
	for (int j = 0; j < 4; ++j)
	{
		v[i] = row[j];
		++i;
	}
}

void Vishv::Math::Matrix4::SetCol(int index, const Vector4& col)
{
	VISHVASSERT(index >= 0 && index <= 3, "[Vishv::Math::Matrix4::SetCol] index out of bounds.");
	int i = index;
	for (int j = 0; j < 4; ++j)
	{
		v[i] = col[j];
		i += 4;
	}
}

Vishv::Math::Vector3 Vishv::Math::Matrix4::operator* (const Vector3& vector)	const
{
	Vector4 a(*this * Vector4(vector.x, vector.y, vector.z, 0));
	return Vector3(a.x, a.y, a.z);
}

Vishv::Math::Vector4	Vishv::Math::Matrix4::operator* (const Vector4& v)	const
{
	return Vector4(
		(_11 * v.x) + (_12 * v.y) + (_13 * v.z) + (_14 * v.w),
		(_21 * v.x) + (_22 * v.y) + (_23 * v.z) + (_24 * v.w),
		(_31 * v.x) + (_32 * v.y) + (_33 * v.z) + (_34 * v.w),
		(_41 * v.x) + (_42 * v.y) + (_43 * v.z) + (_44 * v.w)
	);
}

void Vishv::Math::Matrix4::Scale(const Vector3& v)
{
	_11 *= v.x;
	_22 *= v.y;
	_33 *= v.z;
}

void Vishv::Math::Matrix4::SetScale(const Vector3& v)
{
	_11 = v.x;
	_22 = v.y;
	_33 = v.z;
}

void Vishv::Math::Matrix4::Rotate(const Vector3& v)
{
	RotateX(v.x);
	RotateY(v.y);
	RotateZ(v.z);
}

void Vishv::Math::Matrix4::Translate(const Vector3& v)
{
	_41 += v.x;
	_42 += v.y;
	_43 += v.z;
}

void Vishv::Math::Matrix4::SetTranslate(const Vector3& v)
{
	_41 = v.x;
	_42 = v.y;
	_43 = v.z;
}

Vishv::Math::Matrix4 Vishv::Math::Matrix4::ScaleMatrix(const Vector3& v)
{
	Matrix4 m(Identity());
	m.SetScale(v);
	return m;
}

Vishv::Math::Matrix4 Vishv::Math::Matrix4::RotateMatrix(const Quaternion& q)
{
	return q;
}
Vishv::Math::Matrix4 Vishv::Math::Matrix4::TranslationMatrix(const Quaternion& q, const Vector4& v)
{
	return Matrix4(q, v);

}
Vishv::Math::Matrix4 Vishv::Math::Matrix4::TranslationMatrix(const Quaternion& q, const Vector3& v)
{
	return Matrix4(q, v);
}
Vishv::Math::Matrix4 Vishv::Math::Matrix4::TranslateMatrix(const Vector3& v)
{
	Matrix4 m(Identity());
	m.Translate(v);
	return m;
}
Vishv::Math::Matrix4 Vishv::Math::Matrix4::TranslateMatrix(const Vector4& v)
{
	Matrix4 m(Identity());
	m.Translate({ v.x, v.y, v.z });
	return m;
}



