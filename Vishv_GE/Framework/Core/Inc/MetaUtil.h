#ifndef INCLUDED_VISHV_CORE_META_UTIL_H
#define INCLUDED_VISHV_CORE_META_UTIL_H

#include "MetaArray.h"
#include "MetaPointer.h"

namespace Vishv::Core::Meta
{
	class MetaType;
	template <class DataType>
	const MetaType* DeduceType();

	template <class DataType>
	void Deserialize(void* instance, const rapidjson::Value& jsonValue);

	namespace Detail
	{
		template <class DataType>
		inline const MetaType* DeduceTypeImpl(DataType*)
		{
			static_assert(sizeof(DataType) == -1, "Cannot deduce type");
		}

		template <class DataType>
		inline const MetaType* DeduceTypeImpl(DataType**)
		{
			static MetaPointer sMetaPointer(DeduceType<DataType>());
			return &sMetaPointer;
		}

		template <class DataType>
		inline const MetaType* DeduceTypeImpl(std::vector<DataType>*)
		{
			static const auto getElement = [](void* instance, size_t index) -> void*
			{
				auto vec = reinterpret_cast<std::vector<DataType>*>(instance);
				vec->resize(index + 1);
				return &(*vec)[index];
			};

			static const auto getCount = [](void* instance) -> size_t
			{
				auto vec = reinterpret_cast<std::vector<DataType>*>(instance);
				return vec->size();
			};

			static MetaArray sMetaArray(DeduceType<DataType>(), getElement, getCount);
			return &sMetaArray;
		}
	}

	template<class DataType>
	inline const MetaType* DeduceType()
	{
		return Detail::DeduceTypeImpl(static_cast<DataType*>(nullptr));
	}

	template <class ClassType, class DataType>
	inline const MetaType* DeduceMemberType(DataType ClassType::*)		//says pointer to x type in class c
	{
		return DeduceType<DataType>();
	}

	template <class ClassType, class DataType>
	inline size_t GetFieldOffset(DataType ClassType::* field)
	{
		return (size_t)(void*)&(((ClassType*)nullptr)->*field);
	}

	template <class BaseType, class DerivedType>
	inline DerivedType* DynamicCast(BaseType* ptr)
	{
		if (ptr->GetMetaClass() != DerivedType::StaticGetMetaClass())
			return nullptr;
		return static_cast<DerivedType*>(ptr);
	}

	template <class BaseType, class DerivedType>
	inline bool IsBaseOf()
	{
		auto parent = DerivedType::StaticGetMetaClass()->GetParent();
		while (parent)
		{
			if (parent == BaseType::StaticGetMetaClass())
				return true;
			parent = parent->GetParent();
		}
		return false;
	}
}


#endif // !INCLUDED_VISHV_CORE_META_UTIL_H
