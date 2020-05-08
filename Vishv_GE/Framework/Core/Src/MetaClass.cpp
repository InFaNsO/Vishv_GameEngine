#include "Precompiled.h"
#include "MetaClass.h"
#include "MetaField.h"
#include "MetaRegistry.h"

namespace
{
	
}

using namespace Vishv::Core::Meta;

Vishv::Core::Meta::MetaClass::MetaClass(const char * name, size_t size, MetaType::CreateFunc create,
	MetaType::DestroyFunc destroy,
	const MetaClass* parent,
	std::vector<MetaField> fields)
	:MetaType(name, MetaType::Category::Class, size, std::move(create), std::move(destroy))
	, mParent(parent)
	, mFields(std::move(fields))
{
}

const MetaField * Vishv::Core::Meta::MetaClass::FindField(const char * name) const
{
	for (auto& field : mFields)
	{
		if (strcmp(field.GetName(), name) == 0)
			return &field;
	}

	if (mParent != nullptr)
		return mParent->FindField(name);

	return nullptr;
}

size_t Vishv::Core::Meta::MetaClass::GetParentFieldCount() const
{
	return mParent ? mParent->GetFieldCount() : 0u;
}

const MetaField * Vishv::Core::Meta::MetaClass::GetField(size_t index) const
{
	VISHVASSERT(index < GetFieldCount(), "[MetaClass] index out of range");

	if (mParent && index < GetParentFieldCount())
		return mParent->GetField(index);
	return mFields.data() + (index - GetParentFieldCount());
}

size_t Vishv::Core::Meta::MetaClass::GetFieldCount() const
{
	return mParent ? GetParentFieldCount() + mFields.size() : mFields.size();
}


void Vishv::Core::Meta::MetaClass::Serialize(const void * instance, rapidjson::Value & jsonValue, rapidjson::Document& doc) const
{
	for (auto& field : mFields)
	{
		auto metaType =field.GetMetaType();
		auto instanceField = static_cast<const uint8_t*>(instance) + field.GetOffset();

		metaType->Serialize(instanceField, jsonValue, doc);
	}
}

void Vishv::Core::Meta::MetaClass::Deserialize(void * instance, const rapidjson::Value & jsonValue) const
{
	for (auto& prop : jsonValue.GetObjectW())
	{
		auto metaField = FindField(prop.name.GetString());
		auto metaType = metaField->GetMetaType();
		auto instanceField = static_cast<uint8_t*>(instance) + metaField->GetOffset();
		
		metaType->Deserialize(instanceField, prop.value);
	}
}



