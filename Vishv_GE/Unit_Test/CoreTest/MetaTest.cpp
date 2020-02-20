#include "stdafx.h"
#include "CppUnitTest.h"
#include "Core/Inc/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Vishv::Core;

class Car
{
public:
	META_CLASS_DECLARE
	void Move() { mPosition += 1.0f; }

protected:
	float mPosition;
	bool mAutomatic = false;
};

class Tesla : public Car
{
public:
	META_CLASS_DECLARE
	void Move() { mPosition += 10.0f; }
protected:
	bool mGPS = true;
};

META_CLASS_BEGIN(Car)
META_FIELD_BEGIN
	META_FIELD(mPosition, "Position")
	META_FIELD(mAutomatic, "Automatic")
	META_FIELD_END
META_CLASS_END

META_DERIVED_BEGIN(Tesla, Car)
	META_FIELD_BEGIN
		META_FIELD(mGPS, "GPS")
	META_FIELD_END
META_CLASS_END


namespace MetaTesting
{
	TEST_CLASS(MetaTest)
	{
	public:

		TEST_METHOD(TestMetaType)
		{
			auto type = Meta::DeduceType<int>();
			Assert::AreEqual(type->GetName(), "Integer");
			Assert::IsTrue(type->GetCategory() == Meta::MetaType::Category::Primitive);
			Assert::IsTrue(type->GetSize() == sizeof(int));
		}

		TEST_METHOD(TestMetaPointer)
		{
			int * ptr = nullptr; 
			auto type = Meta::DeduceType<int*>();
			Assert::AreEqual(type->GetName(), "Pointer");
			Assert::IsTrue(type->GetCategory() == Meta::MetaType::Category::Pointer);
			Assert::IsTrue(type->GetSize() == sizeof(int*));
			
			auto metaPointer = static_cast<const Meta::MetaPointer*>(type);
			auto metaPointerType = metaPointer->GetMetaType();
			Assert::AreEqual(metaPointerType->GetName(), "Integer");
			Assert::IsTrue(metaPointerType->GetCategory() == Meta::MetaType::Category::Primitive);
			Assert::IsTrue(metaPointerType->GetSize() == sizeof(int));
		}

		TEST_METHOD(TestMetaArray)
		{
			using intVec = std::vector<int>;
			auto metaType = Meta::DeduceType<intVec>();
			
			Assert::AreEqual(metaType->GetName(), "Array");
			Assert::IsTrue(metaType->GetCategory() == Meta::MetaType::Category::Array);
			Assert::IsTrue(metaType->GetSize() == sizeof(intVec));

			intVec vec{1,25,36,24,85,64,77};

			auto metaArr = static_cast<const Meta::MetaArray*>(metaType);
			Assert::IsTrue(metaArr->GetElementType() == Meta::DeduceType<int>());
			
			for(size_t i = 0; i < metaArr->GetCount(&vec); ++i)
				Assert::IsTrue(*(int*)metaArr->GetElement(&vec, i) == vec[i]);
		}

		TEST_METHOD(TestMetaClass)
		{
			auto metaType = Meta::DeduceType<Car>();
			Assert::AreEqual(metaType->GetName(), "Car");
			Assert::IsTrue(metaType->GetCategory() == Meta::MetaType::Category::Class);
			Assert::IsTrue(metaType->GetSize() == sizeof(Car));

			auto metaClass = Car::StaticGetMetaClass();
			Assert::IsNull(metaClass->GetParent());
			Assert::IsTrue(metaClass->GetFieldCount() == 2);

			auto metaField0 = metaClass->GetField(0);
			Assert::IsTrue(metaField0->GetMetaType() == Meta::DeduceType<float>());
			Assert::AreEqual(metaField0->GetName(), "Position");
			Assert::IsTrue(metaField0 == metaClass->FindField("Position"));

			auto metaField1 = metaClass->GetField(1);
			Assert::IsTrue(metaField1->GetMetaType() == Meta::DeduceType<bool>());
			Assert::AreEqual(metaField1->GetName(), "Automatic");
			Assert::IsTrue(metaField1 == metaClass->FindField("Automatic"));
		}

		TEST_METHOD(TestMetaDerived)
		{
			auto metaType = Meta::DeduceType<Tesla>();
			Assert::AreEqual(metaType->GetName(), "Tesla");
			Assert::IsTrue(metaType->GetCategory() == Meta::MetaType::Category::Class);
			Assert::IsTrue(metaType->GetSize() == sizeof(Tesla));

			auto metaClass = Tesla::StaticGetMetaClass();
			Assert::IsTrue(metaClass->GetParent() == Car::StaticGetMetaClass());
			Assert::IsTrue(metaClass->GetFieldCount() == 3);

			auto metaField0 = metaClass->GetField(0);
			Assert::IsTrue(metaField0->GetMetaType() == Meta::DeduceType<float>());
			Assert::AreEqual(metaField0->GetName(), "Position");
			Assert::IsTrue(metaField0 == metaClass->FindField("Position"));

			auto metaField1 = metaClass->GetField(1);
			Assert::IsTrue(metaField1->GetMetaType() == Meta::DeduceType<bool>());
			Assert::AreEqual(metaField1->GetName(), "Automatic");
			Assert::IsTrue(metaField1 == metaClass->FindField("Automatic"));

			auto metaField2 = metaClass->GetField(2);
			Assert::IsTrue(metaField2->GetMetaType() == Meta::DeduceType<bool>());
			Assert::AreEqual(metaField2->GetName(), "GPS");
			Assert::IsTrue(metaField2 == metaClass->FindField("GPS"));
		}
	};
}