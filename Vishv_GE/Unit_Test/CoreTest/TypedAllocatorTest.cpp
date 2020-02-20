#include "stdafx.h"
#include "CppUnitTest.h"
#include "Core/Inc/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Vishv::Core;

namespace CoreTest
{
	TEST_CLASS(TypedBlockAllocatorTest)
	{
	public:
		class Bar
		{
		public:
			static int counter;
			Bar() { counter = 0; }
			Bar(const Bar&) { counter = 1; }
			Bar(Bar&&) { counter = 2; }
		};

		class Foo
		{
		public:
			int a, b;
			Foo() :a(42), b(7) {}
			Foo(int i, int j) :a(i), b(j) {}
			Foo(Bar) : a(12), b(34) {}
			Foo(std::string str) : a(24), b(68) {}
			~Foo()
			{
				a = 0xfeefee;
				b = 0xdeedee;
			}
		};

		TEST_METHOD(TestNew)
		{
			Foo foo("Bhavil");

			TypedAllocator<Foo> typedAllocator(1);
			Foo* ptr = typedAllocator.New();

			Assert::IsNotNull(ptr);
			Assert::IsTrue(ptr->a == 42);
			Assert::IsTrue(ptr->b == 7);

			Foo* p = typedAllocator.New();

			Assert::IsNull(p);
		}
		TEST_METHOD(TestOverloadedNew)
		{
			Foo foo("Bhavil");

			TypedAllocator<Foo> typedAllocator(1);
			Foo* ptr = typedAllocator.New( 5 , 6);

			Assert::IsNotNull(ptr);
			Assert::IsTrue(ptr->a == 5);
			Assert::IsTrue(ptr->b == 6);

			Foo* p = typedAllocator.New();

			Assert::IsNull(p);
		}
		TEST_METHOD(TestPerfectForwarding)
		{
			Foo foo("Bhavil");

			TypedAllocator<Foo> typedAllocator(1);
			Foo* ptr = typedAllocator.New(std::move( Bar()));

			Assert::IsNotNull(ptr);
			Assert::AreEqual(Bar::counter, 2);
		}
		TEST_METHOD(TestDelete)
		{
			Foo foo("Bhavil");
			TypedAllocator<Foo> typedAllocator(1);
			Foo* ptr = typedAllocator.New(Bar());

			Assert::IsNotNull(ptr);

			typedAllocator.Delete(ptr);

			Assert::IsTrue(ptr->a = 0xfeefee);
			Assert::IsTrue(ptr->b = 0xdeedee);
		}
	};
	int TypedBlockAllocatorTest::Bar::counter = 0;
}