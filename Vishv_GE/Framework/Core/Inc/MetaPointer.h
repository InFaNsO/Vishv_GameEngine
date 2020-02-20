#ifndef INCLUDED_VISHV_CORE_META_POINTER_H
#define INCLUDED_VISHV_CORE_META_POINTER_H

#include "MetaType.h"

namespace Vishv::Core::Meta
{

	class MetaPointer : public MetaType
	{
	public:
		MetaPointer(const MetaType* pointerType);

		const MetaType* GetMetaType() const { return mPointerType; }

	private:
		const MetaType* mPointerType;
	};
}


#endif // !INCLUDED_VISHV_CORE_META_POINTER_H
