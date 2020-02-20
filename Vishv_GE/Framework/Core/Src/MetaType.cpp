#include "Precompiled.h"
#include "MetaType.h"

Vishv::Core::Meta::MetaType::MetaType(const char * name, Category category, size_t size, CreateFunc create, DestroyFunc destroy)
	:mName(name)
	, mCategory(category)
	, mSize(size)
	, mCreate(std::move(create))
	, mDestroy(std::move(destroy))
{
}

