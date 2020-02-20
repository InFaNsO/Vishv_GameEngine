#ifndef INCLUDED_VISHV_MATH_Matrix4_H
#define INCLUDED_VISHV_MATH_Matrix4_H

#include "Matrix3.h"

namespace Vishv::Math
{
	struct Vector3;
	struct Vector4;
	struct Quaternion;
	class Transform;


struct Matrix4
{
	union 
	{
		struct //row + column subscript
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		std::array<float, 16> v;
	};

	constexpr Matrix4(std::array<float, 16> m)
		:v(m)
	{
	}
	constexpr Matrix4(const Matrix4& m = Identity())
		: v(m.v)
	{
	}

	constexpr Matrix4(float r1c1, float r1c2, float r1c3, float r1c4,
		float r2c1, float r2c2, float r2c3, float r2c4,
		float r3c1, float r3c2, float r3c3, float r3c4,
		float r4c1, float r4c2, float r4c3, float r4c4)
		:_11(r1c1), _12(r1c2), _13(r1c3), _14(r1c4), _21(r2c1), _22(r2c2), _23(r2c3), _24(r2c4), _31(r3c1), _32(r3c2), _33(r3c3), _34(r3c4), _41(r4c1), _42(r4c2), _43(r4c3), _44(r4c4)
	{
	}

	Matrix4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4);
	Matrix4(const Quaternion& q);
	Matrix4(const Quaternion& q, const Vector4& pos);
	//Matrix4(const Transform& t);

	Vector3 GetTranslation();

	void Reset()
	{
		for (int i = 0; i < 16; ++i)
		{
			v[i] = i % 5 == 0 ? 1.0f : 0.0f;
		}
	}

	//Getter and Setters
	std::array<float, 4> GetRow(int row) const
	{
		VISHVASSERT(row < 4 && row >= 0, "[Vishv::Math::Matrix4::GetRow] Row number out of bounds.");

		std::array<float, 4> r;

		size_t index = GetIndex(row, 0);

		for (int i = 0; i < 4; ++i)
		{
			r[i] = v[index + i];
		}

		return r;
	}
	std::array<float, 4> GetCol(int col) const
	{
		VISHVASSERT(col < 4 && col >= 0, "[Vishv::Math::Matrix4::GetCol] Column number out of bounds.");

		std::array<float, 4> r;

		size_t index = GetIndex(col, 0);

		for (int i = 0; i < 4; ++i)
		{
			r[i] = v[index + i];
		}

		return r;
	}
	void Set(size_t row, size_t col, float val)
	{

		v[GetIndex(row, col)] = val;
	}
	float Get(size_t row, size_t col) const
	{
		return v[GetIndex(row, col)];
	}
	void SetRow(int index, std::array<float, 4> row)
	{
		VISHVASSERT(index >= 0 && index <= 3, "[Vishv::Math::Matrix4::SetRow] index out of bounds.");
		int i = index * 4;
		for (int j = 0; j < 4; ++j)
		{
			v[i] = row[j];
			++i;
		}
	}
	void SetRow(int index, const Vector4& row);
	void SetCol(int index, std::array<float, 4> col)
	{
		VISHVASSERT(index >= 0 && index <= 3, "[Vishv::Math::Matrix4::SetCol] index out of bounds.");
		int i = index;
		for (int j = 0; j < 4; ++j)
		{
			v[i] = col[j];
			i += 4;
		}
	}
	void SetCol(int index, const Vector4& col);

	//overloading operators
	float& operator[] (int i)			//would allow to edit values on the go
	{
		return v[i];
	}
	float operator[] (int i) const			//would allow to edit values on the go
	{
		return v[i];
	}

	// operator * + - /

	constexpr Matrix4 operator*(float scalar)
	{
		for (int i = 0; i < 16; ++i)
		{
			v[i] *= scalar;
		}

		return *this;
	}
	constexpr Matrix4 operator*(const Matrix4& rhs) const
	{
		return Matrix4(
			(_11 * rhs._11) + (_12 * rhs._21) + (_13 * rhs._31) + (_14 * rhs._41),
			(_11 * rhs._12) + (_12 * rhs._22) + (_13 * rhs._32) + (_14 * rhs._42),
			(_11 * rhs._13) + (_12 * rhs._23) + (_13 * rhs._33) + (_14 * rhs._43),
			(_11 * rhs._14) + (_12 * rhs._24) + (_13 * rhs._34) + (_14 * rhs._44),

			(_21 * rhs._11) + (_22 * rhs._21) + (_23 * rhs._31) + (_24 * rhs._41),
			(_21 * rhs._12) + (_22 * rhs._22) + (_23 * rhs._32) + (_24 * rhs._42),
			(_21 * rhs._13) + (_22 * rhs._23) + (_23 * rhs._33) + (_24 * rhs._43),
			(_21 * rhs._14) + (_22 * rhs._24) + (_23 * rhs._34) + (_24 * rhs._44),

			(_31 * rhs._11) + (_32 * rhs._21) + (_33 * rhs._31) + (_34 * rhs._41),
			(_31 * rhs._12) + (_32 * rhs._22) + (_33 * rhs._32) + (_34 * rhs._42),
			(_31 * rhs._13) + (_32 * rhs._23) + (_33 * rhs._33) + (_34 * rhs._43),
			(_31 * rhs._14) + (_32 * rhs._24) + (_33 * rhs._34) + (_34 * rhs._44),

			(_41 * rhs._11) + (_42 * rhs._21) + (_43 * rhs._31) + (_44 * rhs._41),
			(_41 * rhs._12) + (_42 * rhs._22) + (_43 * rhs._32) + (_44 * rhs._42),
			(_41 * rhs._13) + (_42 * rhs._23) + (_43 * rhs._33) + (_44 * rhs._43),
			(_41 * rhs._14) + (_42 * rhs._24) + (_43 * rhs._34) + (_44 * rhs._44));
	}
	Vector3	operator*(const Vector3& vector) const;
	Vector4	operator*(const Vector4& v) const;
	constexpr Matrix4 operator+(const Matrix4& other) 
	{
		for (int i = 0; i < 16; ++i)
		{
			v[i] += other.v[i];
		}

		return *this;
	}
	constexpr Matrix4 operator-(const Matrix4& other) 
	{
		for (int i = 0; i < 16; ++i)
		{
			v[i] -= other.v[i];
		}

		return *this;
	}

	 Matrix4 operator=(const Matrix4& other)
	{
		for (int i = 0; i < 16; ++i) 
		{
			v[i] = other.v[i];
		}
		return *this;
	}
	
	//comparision
	constexpr bool operator== (const Matrix4& other)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (v[i] != other.v[i])
			{
				return false;
			}
		}
		return true;
	}
	constexpr bool operator!=(const Matrix4& other)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (v[i] == other.v[i])
			{
				return false;
			}
		}
		return true;
	}


	inline float Determinent() const
	{
		//Advance Code (slow)
		//float val = 0.0f;
		//int i = 0;
		//for (int j = 0; j < size; ++j)
		//{
		//	val += j%2 == 0 ? v[j] * GetMatrix<i, j>().Determinent() : (v[j] * GetMatrix(i, j).Determinent()) * -1;
		//}
		//
		//return val;
		//Old Code Hard coded
		
		return (_11 * Matrix3(_22, _23, _24, _32, _33, _34, _42, _43, _44).Determinent())
			- (_12 * Matrix3(_21, _23, _24, _31, _33, _34, _41, _43, _44).Determinent()) 
			+ (_13 * Matrix3(_21, _22, _24, _31, _32, _34, _41, _42, _44).Determinent())
			- (_14 * Matrix3(_21, _22, _23, _31, _32, _33, _41, _42, _43).Determinent());
	}
	inline Matrix4 Transpose() const
	{
		return Matrix4(	_11, _21, _31, _41,
						_12, _22, _32, _42,
						_13, _23, _33, _43, 
						_14, _24, _34, _44);
	}

	static inline Matrix4 Transpose(const Matrix4 & other)
	{
		return Matrix4(
			other._11, other._21, other._31, other._41,
			other._12, other._22, other._32, other._42,
			other._13, other._23, other._33, other._43,
			other._14, other._24, other._34, other._44
		);
	}
	static inline Matrix4 Transpose(const Matrix4* other)
	{
		return Matrix4(
			other->_11, other->_21, other->_31, other->_41,
			other->_12, other->_22, other->_32, other->_42,
			other->_13, other->_23, other->_33, other->_43,
			other->_14, other->_24, other->_34, other->_44
		);
	}

	inline Matrix4 Cofactor() const
	{
		//ADvance Code (slow)
		//std::array<float, 16> val;
		//for (int i = 0; i < size; ++i)
		//{
		//	for (int j = 0; j < size; ++j)
		//	{
		//		val[GetIndex(i, j)] = GetMatrix<i, j>().Determinent();
		//
		//		//Need to debug this to be sure (might be flipped due to starting from 0)
		//		if (i % 2 == 0 && j % 2 == 1 || i % 2 == 1 && j % 2 == 0)
		//		{
		//			val[GetIndex(i, j)] *= -1;
		//		}
		//	}
		//}
		//
		//return Matrix4(val);

		//	Old Matrix Code
		
		return Matrix4(	  Matrix3(_22, _23, _24, _32, _33, _34, _42, _43, _44).Determinent(), - Matrix3(_21, _23, _24, _31, _33, _34, _41, _43, _44).Determinent(),   Matrix3(_21, _22, _24, _31, _32, _34, _41, _42, _44).Determinent(), - Matrix3(_21, _22, _23, _31, _32, _33, _41, _42, _43).Determinent(),
						- Matrix3(_12, _13, _14, _32, _33, _34, _42, _43, _44).Determinent(),   Matrix3(_11, _13, _14, _31, _33, _34, _41, _43, _44).Determinent(), - Matrix3(_11, _12, _14, _31, _32, _34, _41, _42, _44).Determinent(),   Matrix3(_11, _12, _13, _31, _32, _33, _41, _42, _43).Determinent(),
						  Matrix3(_12, _13, _14, _22, _23, _24, _42, _43, _44).Determinent(), - Matrix3(_11, _13, _14, _21, _23, _24, _41, _43, _44).Determinent(),   Matrix3(_11, _12, _14, _21, _22, _24, _41, _42, _44).Determinent(), - Matrix3(_11, _12, _13, _21, _22, _23, _41, _42, _43).Determinent(),
						- Matrix3(_12, _13, _14, _22, _23, _24, _32, _33, _34).Determinent(),   Matrix3(_11, _13, _14, _21, _23, _24, _31, _33, _34).Determinent(), - Matrix3(_11, _12, _14, _21, _22, _24, _31, _32, _34).Determinent(),   Matrix3(_11, _12, _13, _21, _22, _23, _31, _32, _33).Determinent());
	}
	inline Matrix4 Adjoint() const
	{
		return Cofactor().Transpose();
	}
	inline Matrix4 Inverse() const
	{
		float det = Determinent();
		
		VISHVASSERT(det != 0.0f, "[Vishv::Math::Matrix4::Inverse] Devision by zero Matrix not set.");

		float val = 1 / det;

		return Adjoint() * val;
	}

	static inline Matrix4 Inverse(const Matrix4& m)
	{
		float det = m.Determinent();
		VISHVASSERT(det != 0.0f, "[Vishv::Math::Matrix4::Inverse] Devision by zero Matrix not set.");
		det = 1 / det;

		return m.Adjoint() * det;
	}

	//Transformation
	void Scale(const Vector3& v);
	void SetScale(const Vector3& v);
	constexpr void Scale(float f)
	{
		_11 += f;
		_22 += f;
		_33 += f;
	}

	constexpr void ScaleX(float s)
	{
		_11 *= s;
	}
	constexpr void ScaleY(float s)
	{
		_22 *= s;
	}
	constexpr void ScaleZ(float s)
	{
		_33 *= s;
	}

	void Rotate(const Vector3& v);
	void Rotate(float f)
	{
		RotateX(f);
		RotateY(f);
		RotateZ(f);
	}
	void RotateX(float s)
	{
		_22 = cosf(s);		_32 += -1 * sinf(s);
		_23 += sinf(s);		_33 = cosf(s);
	}
	void RotateY(float s)
	{
		_11 = cosf(s);		_31 += -1 * sinf(s);
		_13 += sinf(s);		_33 = cosf(s);
	}
	void RotateZ(float s)
	{
		_11 = cosf(s);		_21 += -1 * sinf(s);
		_12 += sinf(s);		_22 = cosf(s);
	}

	void Translate(const Vector3& v);
	void SetTranslate(const Vector3& v);

	constexpr void Translate(float f)
	{
		_41 += f;
		_42 += f;
		_43 += f;
	}
	constexpr void TranslateX(float f)
	{
		_41 = f;
	}
	constexpr void TranslateY(float f)
	{
		_42 = f;
	}
	constexpr void TranslateZ(float f)
	{
		_43 = f;
	}
	
	//translate operator overload
	constexpr void operator++()
	{
		Translate(1.0f);
	}
	constexpr void operator--()
	{
		Translate(-1.0f);
	}

	static Matrix4 ScaleMatrix(const Vector3& v);
	static Matrix4 RotateMatrixX(float a)
	{
		Matrix4 m(Identity());
		m.RotateX(a);
		return m;
	}
	static Matrix4 RotateMatrixY(float a)
	{
		Matrix4 m(Identity());
		m.RotateY(a);
		return m;
	}
	static Matrix4 RotateMatrixZ(float a)
	{
		Matrix4 m(Identity());
		m.RotateZ(a);
		return m;
	}
	static Matrix4 RotateMatrix(const Quaternion& q);
	static Matrix4 TranslationMatrix(const Quaternion& q, const Vector4& v);
	static Matrix4 TranslationMatrix(const Quaternion& q, const Vector3& v);
	static Matrix4 TranslateMatrix(const Vector3& v);
	static Matrix4 TranslateMatrix(const Vector4& v);

	static inline  Matrix4 Identity() 
	{ 
		return Matrix4(
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		); 
	}

	std::string To_String()
	{
		std::string txt = "";

		for (int i = 0; i < 16; ++i)
		{
			txt += std::to_string(v[i]) + " ";
		}
		return std::move(txt);
	}

private:
		static inline size_t GetIndex(size_t row, size_t col)
		{
			VISHVASSERT(row < 4 && row >= 0, "[Vishv::Math::Matrix4::GetIndex] Row number out of bounds.");
			VISHVASSERT(col < 4 && col >= 0, "[Vishv::Math::Matrix4::GetIndex] Column number out of bounds.");

			return (row * 4) + col;
		}

		//Make the result hardcoded to make it fast for loop is slow
		//template <int row, int col>
		//inline Matrix3 GetMatrix()
		//{
		//	std::array<float, 9> arr;
		//	int count = 0;
		//
		//	for (int i = 0; i < size; ++i)
		//	{
		//		if (i != row)
		//		{
		//			for (int j = 0; j < size; ++j)
		//			{
		//				if (j != col)
		//				{
		//					arr[count] = v[GetIndex(i, j)];
		//					++count;
		//				}
		//			}
		//		}
		//}
		//}
		//template <> inline Matrix3 GetMatrix<0, 0>(){ return { _22, _23, _24, _32, _33, _34, _42, _43, _44 }; }
		//template <> inline Matrix3 GetMatrix<1, 0>(){ return { _12, _13, _14, _32, _33, _34, _42, _43, _44 }; }
		//template <> inline Matrix3 GetMatrix<2, 0>(){ return { _12, _13, _14, _22, _23, _24, _42, _43, _44 }; }
		//template <> inline Matrix3 GetMatrix<3, 0>(){ return { _12, _13, _14, _22, _23, _24, _32, _33, _34 }; }
		//template <> inline Matrix3 GetMatrix<0, 1>(){ return { _21, _23, _24, _31, _33, _34, _41, _43, _44 }; }
		//template <> inline Matrix3 GetMatrix<1, 1>(){ return { _11, _13, _14, _31, _33, _34, _41, _43, _44 }; }
		//template <> inline Matrix3 GetMatrix<2, 1>(){ return { _11, _13, _14, _21, _23, _24, _41, _43, _44 }; }
		//template <> inline Matrix3 GetMatrix<3, 1>(){ return { _11, _13, _14, _21, _23, _24, _31, _33, _34 }; }
		//template <> inline Matrix3 GetMatrix<0, 2>(){ return { _21, _22, _24, _31, _32, _34, _41, _42, _44 }; }
		//template <> inline Matrix3 GetMatrix<1, 2>(){ return { _11, _12, _14, _31, _32, _34, _41, _42, _44 }; }
		//template <> inline Matrix3 GetMatrix<2, 2>(){ return { _11, _12, _14, _21, _22, _24, _41, _42, _44 }; }
		//template <> inline Matrix3 GetMatrix<3, 2>(){ return { _11, _12, _14, _21, _22, _24, _31, _32, _34 }; }
		//template <> inline Matrix3 GetMatrix<0, 3>(){ return { _21, _22, _23, _31, _32, _33, _41, _42, _43 }; }
		//template <> inline Matrix3 GetMatrix<1, 3>(){ return { _11, _12, _13, _31, _32, _33, _41, _42, _43 }; }
		//template <> inline Matrix3 GetMatrix<2, 3>(){ return { _11, _12, _13, _21, _22, _23, _41, _42, _43 }; }
		//template <> inline Matrix3 GetMatrix<3, 3>(){ return { _11, _12, _13, _21, _22, _23, _31, _32, _33 }; }

};
}	//Vishv

#endif //defined INCLUDED_VISHV_MATH_Matrix4_H