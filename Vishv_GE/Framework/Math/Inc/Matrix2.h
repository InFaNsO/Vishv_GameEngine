#ifndef INCLUDED_VISHV_MATH_Matrix2_H
#define INCLUDED_VISHV_MATH_Matrix2_H

namespace Vishv::Math
{
	struct Vector2;

struct Matrix2
{
	union
	{
		struct //row + column subscript
		{
			float _11, _12;
			float _21, _22;
		};
		std::array<float, 4> v;
	};

	Matrix2() = default;
	inline Matrix2(std::array<float, 4> m)
		: v(m)
	{

	}
	inline Matrix2(const Matrix2& m)
		:v(m.v)
	{

	}
	constexpr Matrix2(float r1c1, float r1c2,
		float r2c1, float r2c2)
		: _11(r1c1), _12(r1c2), _21(r2c1), _22(r2c2)
	{
	}

	void SetRow(const Vector2& row1, const Vector2& row2);
	void SetColumn(const Vector2& col1, const Vector2& col2);

	Vector2 GetRow(int row);
	Vector2 GetColumn(int col);

	void Set(size_t row, size_t col, float val)
	{
		VISHVASSERT(row < 2 && row >= 0, "[Vishv::Math::Matrix4::Set] Row number out of bounds.");
		VISHVASSERT(col < 2 && col >= 0, "[Vishv::Math::Matrix4::Set] Column number out of bounds.");

		size_t index = (row * 2) + col;
		v[index] = val;
	}

	// operator * + - /

	inline Matrix2 operator* (float scalar)
	{
		int size = 4;

		for (int i = 0; i < size; ++i)
		{
			v[i] *= scalar;
		}

		return *this;
	}
	Matrix2 operator* (Matrix2 &other);
	inline Matrix2 operator+ (Matrix2 &other)
	{
		int size = 4;

		for (int i = 0; i < size; ++i) 
		{
			v[i] += other.v[i];
		}

		return *this;
	}
	inline Matrix2 operator- (Matrix2 &other)
	{
		int size = 4;

		for (int i = 0; i < size; ++i) 
		{
			v[i] -= other.v[i];
		}

		return *this;
	}

	float Determinent()
	{
		return (_11 * _22) - (_12 * _21);
	}
	Matrix2 Transpose()
	{
		return Matrix2(_11, _21, _12, _22);
	}
	Matrix2 Cofactor()
	{
		return Matrix2(_22, -_21, -_12, _11);
	}

	inline Matrix2 Adjoint()
	{
		return Cofactor().Transpose();
	}
	inline Matrix2 Inverse()
	{
		float det = Determinent();

		VISHVASSERT(det != 0.0f, "[Vishv::Math::Matrix3::Inverse] Devision by zero Matrix not set.");

		float val = 1 / det;

		return Adjoint() * val;
	}

	inline Matrix2 Identity()
	{
		std::array<float, 4> id;

		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				id[GetIndex(i, j)] = i == j ? 1.0f : 0.0f;
			}
		}

		return id;
	}

private:
	inline int GetIndex(int row, int col)
	{
		VISHVASSERT(row < 2 && row >= 0, "[Vishv::Math::Matrix4::GetIndex] Row number out of bounds.");
		VISHVASSERT(col < 2 && col >= 0, "[Vishv::Math::Matrix4::GetIndex] Column number out of bounds.");

		return (row * 2) + col;
	}

};
}

#endif //defined INCLUDED_VISHV_MATH_Matrix2_H