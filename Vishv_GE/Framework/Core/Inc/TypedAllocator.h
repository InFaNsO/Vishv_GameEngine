#ifndef INCLUDED_VISHV_CORE_TYPED_ALLOCATOR_H
#define INCLUDED_VISHV_CORE_TYPED_ALLOCATOR_H

#include "BlockAllocator.h"
//Type safe memory fragmentation prevention system
namespace Vishv::Core {

	template <class T>
	class TypedAllocator : private BlockAllocator
	{
	public:
		TypedAllocator(size_t capacity)
			:BlockAllocator(sizeof(T), capacity)
		{

		}

		TypedAllocator(const TypedAllocator&) = delete;
		TypedAllocator& operator=(const TypedAllocator&) = delete;

		TypedAllocator(const TypedAllocator&&) = delete;
		TypedAllocator& operator=(const TypedAllocator&&) = delete;

		template<class... Args>
		T* New(Args&& ... args)
		{
			void* memory = Allocate();
			if (memory)
			{
				return new (memory) T(std::forward<Args>( args )...);
			}
			return nullptr;
		}
		void Delete(T* ptr)
		{
			if (!ptr)
				return;

			ptr->~T();
			Free(ptr);
		}

	};

}

#endif