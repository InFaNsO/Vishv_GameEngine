#ifndef INCLUDED_VISHV_CORE_META_H
#define INCLUDED_VISHV_CORE_META_H

#include "MetaArray.h"
#include "MetaClass.h"
#include "MetaField.h"
#include "MetaPointer.h"
#include "MetaRegistry.h"
#include "MetaType.h"
#include "MetaUtil.h"


#define META_TYPE_DECLARE(Type)\
	template<> const Vishv::Core::Meta::MetaType* Vishv::Core::Meta::DeduceType<Type>();

#define META_TYPE_DEFINE(Type, Name)\
	template<> const Vishv::Core::Meta::MetaType* Vishv::Core::Meta::DeduceType<Type>()\
	{\
		static Vishv::Core::Meta::MetaType sMetaType(\
			#Name,\
			MetaType::Category::Primitive,\
			sizeof(Type),\
			[] {return new Type; },\
			[](void* ptr) {delete static_cast<Type*>(ptr); },\
			nullptr,\
			Vishv::Core::Meta::Deserialize<Type>);\
		return &sMetaType;\
	}

#define META_CLASS_DECLARE\
	static const Vishv::Core::Meta::MetaClass* StaticGetMetaClass();\
	virtual const Vishv::Core::Meta::MetaClass* GetMetaClass() const {return StaticGetMetaClass(); }

#define META_CLASS_BEGIN_INTERNAL(ClassType)\
	template <> const Vishv::Core::Meta::MetaType* Vishv::Core::Meta::DeduceType<ClassType>()\
	{\
		return ClassType::StaticGetMetaClass();\
	}\
	const Vishv::Core::Meta::MetaClass* ClassType::StaticGetMetaClass()\
	{\
		using Class = ClassType;\
		const char* className = #ClassType;

#define META_DERIVED_BEGIN_INTERNAL(ClassType)\
	template <> const Vishv::Core::Meta::MetaType* Vishv::Core::Meta::DeduceType<ClassType>()\
	{\
		return ClassType::StaticGetMetaClass();\
	}\
	const Vishv::Core::Meta::MetaClass* ClassType::StaticGetMetaClass()\
	{\
		using Class = ClassType;\
		const char* className = #ClassType;

#define META_DERIVED_BEGIN(ClassType, ParentType)\
	META_DERIVED_BEGIN_INTERNAL(ClassType)\
		const Vishv::Core::Meta::MetaClass* parentMetaClass = ParentType::StaticGetMetaClass();

#define META_CLASS_BEGIN(ClassType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const Vishv::Core::Meta::MetaClass* parentMetaClass = nullptr;



#define META_CLASS_TEMPLATE_BEGIN_INTERNAL(ClassType)\
	const Vishv::Core::Meta::MetaType* Vishv::Core::Meta::DeduceType<ClassType>()\
	{\
		return ClassType::StaticGetMetaClass();\
	}\
	const Vishv::Core::Meta::MetaClass* ClassType::StaticGetMetaClass()\
	{\
		using Class = ClassType;\
		const char* className = #ClassType;



#define META_FIELD_BEGIN\
		static const std::initializer_list<Vishv::Core::Meta::MetaField> fields {

#define META_FIELD(Var, Name)\
			{ Vishv::Core::Meta::DeduceMemberType(&Class::Var), Name, Vishv::Core::Meta::GetFieldOffset(&Class::Var) },

#define META_FIELD_END\
		};

#define META_NO_FIELD\
		static const std::initializer_list<Vishv::Core::Meta::MetaField> fields;

#define META_CLASS_END\
		static const Vishv::Core::Meta::MetaClass sMetaClass(\
			className, sizeof(Class),\
			[] { return new Class(); },\
			[](void* data) { delete static_cast<Class*>(data); },\
			parentMetaClass, fields);\
		return &sMetaClass;\
	}



#endif // !INCLUDED_VISHV_CORE_META_H
