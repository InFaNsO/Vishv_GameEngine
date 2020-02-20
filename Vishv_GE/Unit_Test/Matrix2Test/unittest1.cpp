#include "stdafx.h"
#include "CppUnitTest.h"
#include "Math/Inc/VishvMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Matrix2Test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ConstructorTest_Array)
		{
			std::array<float, 4> arr;
			for (int i = 0; i < 4; ++i)
			{
				arr[i] = static_cast<float>(i);
			}

			Vishv::Math::Matrix2 m2(arr);


			Assert::IsTrue(arr == m2.v);
		}
		TEST_METHOD(ConstructorTest_Value)
		{
			Vishv::Math::Matrix2 m2(0, 1,2,3);

			Assert::AreEqual(0.0f, m2._11);
			Assert::AreEqual(1.0f, m2._12);
			Assert::AreEqual(2.0f, m2._21);
			Assert::AreEqual(3.0f, m2._22);
		}
		TEST_METHOD(ConstructorTest_Matrix2)
		{
			Vishv::Math::Matrix2 m2(0, 1, 2, 3);
			Vishv::Math::Matrix2 m21(m2);

			Assert::AreEqual(m2, m21);
		}
		TEST_METHOD(SetTest_Row)
		{
			Vishv::Math::Vector2 r1(0, 1);
			Vishv::Math::Vector2 r2(2, 3);

			Vishv::Math::Matrix2 m2;
			m2.SetRow(r1, r2);

			Assert::AreEqual(r1, m2.GetRow(0));
			Assert::AreEqual(r2, m2.GetRow(1));
		}
		TEST_METHOD(SetTest_Col)
		{
			Vishv::Math::Vector2 r1(0, 1);
			Vishv::Math::Vector2 r2(2, 3);

			Vishv::Math::Matrix2 m2;
			m2.SetColumn(r1, r2);

			Assert::AreEqual(r1, m2.GetColumn(0));
			Assert::AreEqual(r2, m2.GetColumn(1));
		}
		TEST_METHOD(SetTest_Set)
		{
			Vishv::Math::Matrix2 m2;
			m2.Set(0, 0, 1);

			Assert::AreEqual(1.0f, m2._11);
		}
		TEST_METHOD(OperatorTest_Multiply_Scalar)
		{
			Vishv::Math::Matrix2 m2(0, 1, 2, 3);
			m2 = m2 * 4;

			Assert::AreEqual(0.0f, m2._11);
			Assert::AreEqual(4.0f, m2._12);
		}
		TEST_METHOD(OperatorTest_Multiply_Matrix)
		{
			Vishv::Math::Matrix2 m2(0, 1, 2, 3);
			Vishv::Math::Matrix2 m22(4, 3, 2, 1);

			Vishv::Math::Matrix2 m(m2 * m22);
			Vishv::Math::Matrix2 res(2, 1, 14, 9);

			Assert::AreEqual(res, m);
		}
		TEST_METHOD(OperatorTest_Addition)
		{
			Vishv::Math::Matrix2 m2(0, 1, 2, 3);
			Vishv::Math::Matrix2 m22(4, 3, 2, 1);

			Vishv::Math::Matrix2 m(m2 * m22);
			Vishv::Math::Matrix2 res(2, 1, 14, 9);

			Assert::AreEqual(res, m);
		}
	};
}