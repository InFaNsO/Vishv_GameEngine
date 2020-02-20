#ifndef INCLUDED_VISHV_CORE_META_FIELD_H
#define INCLUDED_VISHV_CORE_META_FIELD_H


namespace Vishv::Core::Meta
{
	class MetaType;

	class MetaField
	{
	public:
		MetaField(const MetaType * type, const char* name, size_t offset);

		const MetaType* GetMetaType() const		{ return mType; }
		const char* GetName() const				{ return mName.c_str(); }
		size_t GetOffset() const				{ return mOffset; }

	private:
		std::string mName;
		const MetaType* mType;
		const size_t mOffset;
	};
}


#endif // !INCLUDED_VISHV_CORE_META_CLASS_H