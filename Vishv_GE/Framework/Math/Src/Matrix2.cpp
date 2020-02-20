#include "Precompiled.h"
#include "Matrix2.h"
#include "Vector2.h"

void Vishv::Math::Matrix2::SetRow(const Vector2& row1, const Vector2& row2)
{
	_11 = row1.x; _12 = row1.y;
	_21 = row2.x; _22 = row2.y;
}
void Vishv::Math::Matrix2::SetColumn(const Vector2& col1, const Vector2& col2)
{
	_11 = col1.x; _12 = col2.y;
	_21 = col1.x; _22 = col2.y;
}

Vishv::Math::Vector2 Vishv::Math::Matrix2::GetRow(int row)
{
	VISHVASSERT(row < 2 && row >= 0, "[Vishv::Math::Matrix4::GetRow] Row number out of bounds.");

	std::array<float, 2> r;

	int index = GetIndex(row, 0);

	for (int i = 0; i < 2; ++i)
	{
		r[i] = v[index + i];
	}

	return r;
}
Vishv::Math::Vector2 Vishv::Math::Matrix2::GetColumn(int col)
{
	VISHVASSERT(col < 2 && col >= 0, "[Vishv::Math::Matrix4::GetCol] Column number out of bounds.");

	std::array<float, 2> r;

	int index = GetIndex(col, 0);

	for (int i = 0; i < 2; ++i)
	{
		r[i] = v[index + i];
	}

	return r;
}
Vishv::Math::Matrix2 Vishv::Math::Matrix2::operator* (Matrix2 &other)
{
	int size = 4;

	Matrix2 mat;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			Math::Vector2 row = GetRow(i);
			Math::Vector2 col = other.GetColumn(j);

			float val = 0.0f;
			for (int i = 0; i < size; ++i)
			{
				val += row[i] * col[j];
			}

			mat.Set(i, j, val);
		}
	}

	return mat;
}
