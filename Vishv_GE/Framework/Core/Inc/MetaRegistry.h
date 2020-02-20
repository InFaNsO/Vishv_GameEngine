#ifndef INCLUDED_VISHV_CORE_META_REGISTRY_H
#define INCLUDED_VISHV_CORE_META_REGISTRY_H


namespace Vishv::Core::Meta
{
	class MetaClass;

	void Register(const MetaClass* metaClass);

	const MetaClass* FindMetaClass(const std::string& className);
}


#endif // !INCLUDED_VISHV_CORE_META_REGISTRY_H
