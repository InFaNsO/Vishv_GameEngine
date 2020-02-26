#include "Precompiled.h"
#include "MetaType.h"

#include "MetaClass.h"
#include "MetaArray.h"
#include "MetaPointer.h"

Vishv::Core::Meta::MetaType::MetaType(const char * name, Category category, size_t size, CreateFunc create, DestroyFunc destroy)
	:mName(name)
	, mCategory(category)
	, mSize(size)
	, mCreate(std::move(create))
	, mDestroy(std::move(destroy))
{
}

using namespace Vishv::Core::Meta;

const MetaArray* MetaType::GetMetaArray() const
{
	VISHVASSERT(mCategory == Category::Array, "Invalid type cast");
	return static_cast<const MetaArray*>(this);
}

const MetaClass* MetaType::GetMetaClass() const
{
	VISHVASSERT(mCategory == Category::Class, "Invalid type cast");
	return static_cast<const MetaClass*>(this);
}

const MetaPointer* MetaType::GetMetaPointer() const
{
	VISHVASSERT(mCategory == Category::Pointer, "Invalid type cast");
	return static_cast<const MetaPointer*>(this);
}
