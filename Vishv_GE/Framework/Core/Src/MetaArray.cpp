#include "Precompiled.h"
#include "MetaArray.h"

Vishv::Core::Meta::MetaArray::MetaArray(const MetaType * elementType, GetElementFunc elementFunc, GetCountFunc countFunc)
	:MetaType("Array", MetaType::Category::Array, sizeof(std::vector<int>), nullptr, nullptr)
	, mElementType(elementType)
	, mGetElementFunction(std::move(elementFunc))
	,mGetCountFunction(std::move(countFunc))
{
}

