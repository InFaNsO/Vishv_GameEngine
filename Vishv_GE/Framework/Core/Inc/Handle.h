#ifndef INCLUDED_VISHV_CORE_HANDLE_H
#define INCLUDED_VISHV_CORE_HANDLE_H

namespace Vishv::Core
{
	template <class DataType>
	class HandlePool;

	template <class DataType>
	class Handle
	{
	public:
		Handle();
		bool IsValid() const;
		void Invalidate();

		DataType* Get() const;
		DataType* operator->() const;

		bool operator==(const Handle rhs) const { return mIndex == rhs.mIndex && mGeneration == rhs.mGeneration; }
		bool operator!=(const Handle rhs) const { return mIndex != rhs.mIndex || mGeneration != rhs.mGeneration; }

	private:
		friend class HandlePool<DataType>;

		static HandlePool<DataType>* sPool;

		
		uint32_t mIndex : 16;	//bit packing
		uint32_t mGeneration : 16;	//says that it will be using just these number of bits in the allocated memory (to make it act like a pointer as it takes half of 4 bytes)
	};

	template<class DataType>
	HandlePool<DataType>* Handle<DataType>::sPool = nullptr;

	template<class DataType>
	Handle<DataType>::Handle()
		:mIndex(0)
		,mGeneration(0)
	{
	}

	template<class DataType>
	inline bool Vishv::Core::Handle<DataType>::IsValid() const
	{
		return sPool && sPool->IsValid(*this);
	}

	template<class DataType>
	inline void Vishv::Core::Handle<DataType>::Invalidate()
	{
		*this = Handle<DataType>();
	}

	template<class DataType>
	inline DataType * Vishv::Core::Handle<DataType>::Get() const
	{
		return sPool ? sPool->Get(*this) : nullptr;
	}

	template<class DataType>
	inline DataType * Vishv::Core::Handle<DataType>::operator->() const
	{
		return sPool ? sPool->Get(*this) : nullptr;
	}
}


#endif // !INCLUDED_VISHV_CORE_HANDLE_H


#pragma once
