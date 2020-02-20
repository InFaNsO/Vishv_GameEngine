#include "stdafx.h"
#include "CppUnitTest.h"
#include "Core/Inc/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Vishv::Core;

namespace MemoryTest
{
	TEST_CLASS(HandleTest)
	{
	public:

		TEST_METHOD(RegisterCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);

			Assert::IsNotNull(handle.Get());
			Assert::IsTrue(handle->begin() == text.begin());
		}
		TEST_METHOD(InvalidateCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);

			handle.Invalidate();

			Assert::IsNull(handle.Get());
		}
		TEST_METHOD(CopyValidCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);
			auto handleCopy = handle;

			Assert::IsTrue(handle == handleCopy);
			Assert::IsNotNull(handleCopy.Get());
		}
		TEST_METHOD(CopyInvalidCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);
			auto handleCopy = handle;

			handleCopy.Invalidate();

			Assert::IsFalse(handleCopy.IsValid());
			Assert::IsTrue(handle.IsValid());
		}

	};
}