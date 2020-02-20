#include "Precompiled.h"
#include "MetaClass.h"
#include "MetaField.h"
#include "MetaRegistry.h"

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

