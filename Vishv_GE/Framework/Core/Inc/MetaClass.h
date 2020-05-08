#ifndef INCLUDED_VISHV_CORE_META_CLASS_H
#define INCLUDED_VISHV_CORE_META_CLASS_H

#include "MetaType.h"

namespace Vishv::Core::Meta
{
	class MetaField;

	class MetaClass : public MetaType
	{
	public:
		MetaClass(const char * name, 
			size_t size, 
			MetaType::CreateFunc create, 
			MetaType::DestroyFunc destroy, 
			const MetaClass* parent, 
			std::vector<MetaField> fields);

		const MetaClass* GetParent() const						{ return mParent; }
		const MetaField* FindField(const char* name) const;
		const MetaField* GetField(size_t index) const;
		size_t GetFieldCount() const;

		void Serialize(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc) const override;
		void Deserialize(void* instance, const rapidjson::Value& jsonValue) const override;



	private:
		size_t GetParentFieldCount() const;
		const MetaClass* mParent;
		const std::vector<MetaField> mFields;

	};
}


#endif // !INCLUDED_VISHV_CORE_META_CLASS_H


