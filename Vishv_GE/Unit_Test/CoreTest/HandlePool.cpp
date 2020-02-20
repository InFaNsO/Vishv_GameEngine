#include "stdafx.h"
#include "CppUnitTest.h"
#include "Core/Inc/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Vishv::Core;

namespace MemoryTest
{		
	TEST_CLASS(PoolTest)
	{
	public:
		
		TEST_METHOD(ValidCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);

			Assert::IsTrue(pool.IsValid(handle));

		}
		TEST_METHOD(RegisterCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);

			Assert::IsNotNull(pool.Get(handle));
		}
		TEST_METHOD(UnRegisterCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);
			pool.UnRegister(handle);

			Assert::IsNull(pool.Get(handle));
		}
		TEST_METHOD(InvalidateCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);
			pool.UnRegister(handle);

			Assert::IsFalse(pool.IsValid(handle));
		}
		TEST_METHOD(UnRegisterCopyCheck)
		{
			HandlePool<std::string> pool(10);
			std::string text = "RegisterCheck";
			auto handle = pool.Register(&text);
			auto handleCopy = handle;
			pool.UnRegister(handle);

			Assert::IsNull(pool.Get(handleCopy));
		}
	};
}