#ifndef INCLUDED_VISHV_CORE_META_TYPE_H
#define INCLUDED_VISHV_CORE_META_TYPE_H

#include "Debug.h"

namespace Vishv::Core::Meta
{
	class MetaArray;
	class MetaClass;
	class MetaPointer;

	class MetaType
	{
	public:
		using CreateFunc = std::function<void*()>;
		using DestroyFunc = std::function<void(void*)>;

		enum class Category
		{
			Primitive,
			Class,
			Array,
			Pointer
		};

		MetaType(const char* name, Category category, size_t size, CreateFunc create, DestroyFunc destroy);
		
		const char* GetName() const { return mName.c_str(); }
		Category GetCategory() const { return mCategory; }
		size_t GetSize() const { return mSize; }

		void* Create() const
		{
			VISHVASSERT(mCreate, "[MetaType] no creation available for %s", mName.c_str());
			return mCreate();
		}
		void Destroy(void* data) const
		{
			VISHVASSERT(mDestroy, "[MetaType] no destruction available for %s", mName.c_str());
			mDestroy(data);
		}

		const MetaArray* GetMetaArray() const;
		const MetaClass* GetMetaClass() const;
		const MetaPointer* GetMetaPointer() const;

	private:
		const std::string mName;
		Category mCategory;
		size_t mSize;

		CreateFunc mCreate;
		DestroyFunc mDestroy;
	};
}

#endif // !INCLUDED_VISHV_CORE_META_TYPE_H


#pragma once
