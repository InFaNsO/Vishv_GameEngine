#ifndef INCLUDED_VISHV_CORE_META_REGISTRATION_H
#define INCLUDED_VISHV_CORE_META_REGISTRATION_H

#include "Meta.h"

//Primitive basic declaration
META_TYPE_DECLARE(int)
META_TYPE_DECLARE(float)
META_TYPE_DECLARE(bool)
META_TYPE_DECLARE(std::string)

META_TYPE_DECLARE(uint32_t)
META_TYPE_DECLARE(uint64_t)


namespace Vishv::Core
{
	void StaticMetaRegister();
}

#define META_REGISTER(Class)\
	Vishv::Core::Meta::Register(Class::StaticGetMetaClass());

#endif // !INCLUDED_VISHV_CORE_META_REGISTRATION_H

