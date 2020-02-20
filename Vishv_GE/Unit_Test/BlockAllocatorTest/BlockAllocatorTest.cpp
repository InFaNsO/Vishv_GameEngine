#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vishv/Inc/Vishv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlockAllocatorTest
{		
	TEST_CLASS(BlockAllocatorTest)
	{
	public:
		
		TEST_METHOD(OneBlockTest)
		{
			Vishv::Core::BlockAllocator blockAllocator(16, 1);
			void* ptr = blockAllocator.Allocate();
			Assert::IsNotNull(ptr);
		}
		TEST_METHOD(TwoBlockTest)
		{
			Vishv::Core::BlockAllocator blockAllocator(16, 2);
			void* ptr1 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr1);
			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr2);
			Assert::IsFalse(ptr1 == ptr2);
			void* ptr3 = blockAllocator.Allocate();
			Assert::IsNull(ptr3);
		}
		TEST_METHOD(FreeTest)
		{
			Vishv::Core::BlockAllocator blockAllocator(16, 1);
			void* ptr1 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr1);
			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNull(ptr2);
			blockAllocator.Free(ptr1);
			ptr2 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr2);
			Assert::IsTrue(ptr1 == ptr2);
		}
	};
}