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
		using SerializeFunc = std::function<void(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc)>;
		using DeserializeFunc = std::function<void(void* instance, const rapidjson::Value& jsonValue)>;

		enum class Category
		{
			Primitive,
			Class,
			Array,
			Pointer
		};

		MetaType(const char* name, 
			Category category, 
			size_t size, 
			CreateFunc create, 
			DestroyFunc destroy, 
			SerializeFunc serialize = nullptr, 
			DeserializeFunc deserialize = nullptr);
		
		const char* GetName() const { return mName.c_str(); }
		Category GetCategory() const { return mCategory; }
		size_t GetSize() const { return mSize; }

		void * Create() const;
		void Destroy(void* data) const;

		virtual void Serialize(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc) const;
		virtual void Deserialize(void* instance, const rapidjson::Value& jsonValue) const;


	private:
		const std::string mName;
		Category mCategory;
		size_t mSize;

		const CreateFunc mCreate;
		const DestroyFunc mDestroy;

		const SerializeFunc mSerialize;
		const DeserializeFunc mDeserialize;
	};
}

#endif // !INCLUDED_VISHV_CORE_META_TYPE_H


#pragma once
