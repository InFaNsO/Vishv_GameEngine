#ifndef INCLUDED_VISHV_CORE_META_ARRAY_H
#define INCLUDED_VISHV_CORE_META_ARRAY_H

#include "MetaType.h"

namespace Vishv::Core::Meta
{

	class MetaArray : public MetaType
	{
	public:
		using GetElementFunc = std::function<void*(void*, size_t)>;
		using GetCountFunc = std::function<size_t(void*)>;

		MetaArray(const MetaType* elementType, GetElementFunc elementFunc, GetCountFunc countFunc);

		size_t GetCount(void* instance) const { return mGetCountFunction(instance); }
		const MetaType* GetElementType() const { return mElementType; }
		void* GetElement(void* instance, size_t index) const { return mGetElementFunction(instance, index); }

	private:
		const MetaType* mElementType;
		GetElementFunc mGetElementFunction;
		GetCountFunc mGetCountFunction;
	};
}


#endif // !INCLUDED_VISHV_CORE_META_ARRAY_H
