#ifndef INCLUDED_VISHV_MATH_Matrix3_H
#define INCLUDED_VISHV_MATH_Matrix3_H

#include "Matrix2.h"

namespace Vishv::Math
{
	struct Vector2;
	struct Vector3;

struct Matrix3
{
	static const uint32_t size = 3;

	union
	{
		struct //row + column subscript
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		std::array<float, 9> v;
	};

	constexpr Matrix3(float r1c1, float r1c2, float r1c3,
		float r2c1, float r2c2, float r2c3,
		float r3c1, float r3c2, float r3c3)
		:_11(r1c1), _12(r1c2), _13(r1c3), _21(r2c1), _22(r2c2), _23(r2c3), _31(r3c1), _32(r3c2), _33(r3c3)
	{
	}
	Matrix3() = default;
	constexpr Matrix3(std::array<float, 9> m)
		: v(m)
	{
	}

	void SetRow(const Vector3& row1, const Vector3& row2, const Vector3& row3);
	void SetColumn(const Vector3& col1, const Vector3& col2, const Vector3& col3);

	std::array<float, 3> GetRow(int row)
	{
		VISHVASSERT(row < size && row >= 0, "[Vishv::Math::Matrix4::GetRow] Row number out of bounds.");

		std::array<float, 3> r;

		int index = GetIndex(row, 0);

		for (int i = 0; i < size; ++i)
		{
			r[i] = v[static_cast<size_t>(index + i)];
		}

		return r;
	}
	std::array<float, 3> GetCol(int col)
	{
		VISHVASSERT(col < size && col >= 0, "[Vishv::Math::Matrix4::GetCol] Column number out of bounds.");

		std::array<float, 3> r;

		int index = GetIndex(col, 0);

		for (int i = 0; i < size; ++i)
		{
			r[i] = v[static_cast<size_t>(index) +  static_cast<size_t>(i)];
		}

		return r;
	}


	void Set(size_t row, size_t col, float val)
	{
		const int size = 3;
		VISHVASSERT(row < size && row >= 0, "[Vishv::Math::Matrix4::Set] Row number out of bounds.");
		VISHVASSERT(col < size && col >= 0, "[Vishv::Math::Matrix4::Set] Column number out of bounds.");

		size_t index = (row * size) + col;
		v[index] = val;
	}

	// operator * + - /

	constexpr Matrix3 operator* (const float scalar)
	{
		int size = 9;
		for (int i = 0; i < size; ++i)
		{
			v[i] *= scalar;
		}

		return *this;
	}
	constexpr Matrix3 operator* (Matrix3 &other);
	constexpr Matrix3 operator+ (const Matrix3 &other)
	{
		int size = 9;
		for (int i = 0; i < size; ++i)
		{
			v[i] += other.v[i];
		}

		return *this;
	}
	constexpr Matrix3 operator- (const Matrix3 &other)
	{
		int size = 9;
		for (int i = 0; i < size; ++i)
		{
			v[i] -= other.v[i];
		}

		return *this;
	}

	inline float Determinent()
	{
		//Advance Sode (slow)
		//float val = 0.0f;
		//int i = 0;
		//for (int j = 0; j < size; ++j)
		//{
		//	val += j % 2 == 0 ? v[j] * GetMatrix<i, j>.Determinent() : (v[j] * GetMatrix(i, j).Determinent()) * -1;
		//}
		//return val;

		//Old Code Hard coded

		return (_11 * Math::Matrix2(_22, _23, _32, _33).Determinent()) - (_12 * Math::Matrix2(_21, _23, _31, _33).Determinent()) + (_13 * Math::Matrix2(_21, _22, _31, _32).Determinent());
	}
	inline Matrix3 Transpose()
	{
		return Matrix3(_11, _21, _31,
			_12, _22, _32,
			_13, _23, _33);
	}
	inline Matrix3 Cofactor()
	{
		//Slow code
		//std::array<float, 9> val;
		//for (int i = 0; i < size; ++i)
		//{
		//	for (int j = 0; j < size; ++j)
		//	{
		//		val[GetIndex(i, j)] = GetMatrix(i, j).Determinent();
		//
		//		//Need to debug this to be sure (might be flipped due to starting from 0)
		//		if (i % 2 == 0 && j % 2 == 1 || i % 2 == 1 && j % 2 == 0)
		//		{
		//			val[GetIndex(i, j)] *= -1;
		//		}
		//	}
		//}
//
	//	return Matrix3(val);

		//old code

		return Matrix3(Matrix2(_22, _23, _32, _33).Determinent(), -Matrix2(_21, _23, _31, _33).Determinent(), Matrix2(_21, _22, _31, _32).Determinent(),
			-Matrix2(_12, _13, _32, _33).Determinent(), Matrix2(_11, _13, _31, _33).Determinent(), -Matrix2(_11, _12, _31, _32).Determinent(),
			Matrix2(_12, _13, _22, _23).Determinent(), -Matrix2(_11, _13, _21, _23).Determinent(), Matrix2(_11, _12, _21, _22).Determinent());
	}
	inline Matrix3 Adjoint()
	{
		return Cofactor().Transpose();
	}
	inline Matrix3 Inverse()
	{
		float det = Determinent();

		VISHVASSERT(det != 0.0f, "[Vishv::Math::Matrix3::Inverse] Devision by zero Matrix not set.");

		float val = 1 / det;

		return Adjoint() * val;
	}

	static inline Matrix3 Identity()
	{
		std::array<float, 9> id;

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				id[GetIndex(i, j)] = i == j ? 1.0f : 0.0f;
			}
		}

		return id;
	}

	//Transformation
	void Scale(const Vector2& v);
	inline void Scale(float f)
	{
		_11 *= f;
		_22 *= f;
	}
	inline void ScaleX(float s)
	{
		_11 *= s;
	}
	inline void ScaleY(float s)
	{
		_22 *= s;
	}

	inline void Rotate(float s)
	{
		_11 *= cosf(s);		_12 *= -1 * sinf(s);
		_21 *= sinf(s);		_22 *= cosf(s);
	}

	inline void Translate(const Vector2& v);
	inline void Translate(float f)
	{
		_13 += f;
		_23 += f;
	}
	inline void TranslateX(float f)
	{
		_13 = f;
	}
	inline void TranslateY(float f)
	{
		_23 = f;
	}


	//translate operator overload
	void operator++()
	{
		Translate(1.0f);
	}
	void operator--()
	{
		Translate(-1.0f);
	}

	static Matrix3 ScaleMatrix(const Vector2& v);
	static Matrix3 RotateMatrix(float f)
	{
		Matrix3 m(Identity());
		m.Rotate(f);
		return m;
	}
	static Matrix3 TranslateMatrix(const Vector2& v)
	{
		Matrix3 m(Identity());
		m.Translate(v);
		return m;
	}

private:
	static inline int GetIndex(int row, int col)
	{
		VISHVASSERT(row < 4 && row >= 0, "[Vishv::Math::Matrix4::GetIndex] Row number out of bounds.");
		VISHVASSERT(col < 4 && col >= 0, "[Vishv::Math::Matrix4::GetIndex] Column number out of bounds.");

		return (row * 4) + col;
	}
	template <int row, int col>
	inline Matrix2 GetMatrix()
	{
		std::array<float, 4> arr;
		int count = 0;

		for (int i = 0; i < size; ++i)
		{
			if (i != row)
			{
				for (int j = 0; j < size; ++j)
				{
					if (j != col)
					{
						arr[count] = v[GetIndex(i, j)];
						++count;
					}
				}
			}
		}

		return arr;
	}

	template <> inline Matrix2 GetMatrix<0, 0>() { return { _22, _23, _32, _33 }; }
	template <> inline Matrix2 GetMatrix<1, 0>() { return { _12, _13, _22, _23 }; }
	template <> inline Matrix2 GetMatrix<2, 0>() { return { _12, _13, _22, _23 }; }
	template <> inline Matrix2 GetMatrix<0, 1>() { return { _21, _23, _31, _33 }; }
	template <> inline Matrix2 GetMatrix<1, 1>() { return { _11, _13, _31, _33 }; }
	template <> inline Matrix2 GetMatrix<2, 1>() { return { _11, _13, _21, _33 }; }
	template <> inline Matrix2 GetMatrix<0, 2>() { return { _21, _22, _31, _32 }; }
	template <> inline Matrix2 GetMatrix<1, 2>() { return { _11, _12, _31, _32 }; }
	template <> inline Matrix2 GetMatrix<2, 2>() { return { _11, _12, _21, _22 }; }

};	//Matrix3
}

#endif //defined INCLUDED_VISHV_MATH_Matrix4_H