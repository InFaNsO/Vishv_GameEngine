#include "Precompiled.h"
#include "MetaType.h"

#include "MetaClass.h"
#include "MetaArray.h"
#include "MetaPointer.h"

Vishv::Core::Meta::MetaType::MetaType(const char * name, Category category, size_t size, CreateFunc create, DestroyFunc destroy, SerializeFunc serialize, DeserializeFunc deserialize)
	:mName(name)
	, mCategory(category)
	, mSize(size)
	, mCreate(std::move(create))
	, mDestroy(std::move(destroy))
	, mSerialize(std::move(serialize))
	, mDeserialize(std::move(deserialize))
{
}

using namespace Vishv::Core::Meta;


void* MetaType::Create() const
{
	VISHVASSERT(mCreate, "[MetaType] no creation available for %s", mName.c_str());
	return mCreate();
}

void MetaType::Destroy(void* data) const
{
	VISHVASSERT(mDestroy, "[MetaType] no destruction available for %s", mName.c_str());
	mDestroy(data);
}

void Vishv::Core::Meta::MetaType::Serialize(const void * instance, rapidjson::Value & jsonValue, rapidjson::Document& doc) const
{
	VISHVASSERT(mSerialize, "[MetaType] no serialize available for %s", mName.c_str());
	mSerialize(instance, jsonValue, doc );
}

void Vishv::Core::Meta::MetaType::Deserialize(void * instance, const rapidjson::Value & jsonValue) const 
{
	VISHVASSERT(mDeserialize, "[MetaType] no deserialize available for %s", mName.c_str());
	mDeserialize(instance, jsonValue);
}

