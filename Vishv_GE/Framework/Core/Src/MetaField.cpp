#include "Precompiled.h"
#include "MetaField.h"
#include "MetaType.h"

Vishv::Core::Meta::MetaField::MetaField(const MetaType * type, const char * name, size_t offset)
	: mName(name)
	, mType(type)
	, mOffset(offset)
{
}

