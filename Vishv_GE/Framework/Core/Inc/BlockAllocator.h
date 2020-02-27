#ifndef INCLUDED_VISHV_CORE_BLOCK_ALLOCATOR_H
#define INCLUDED_VISHV_CORE_BLOCK_ALLOCATOR_H

namespace Vishv::Core {

	class BlockAllocator
	{
	public:
		BlockAllocator(size_t blockSize, size_t capacity);
		~BlockAllocator();

		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;

		BlockAllocator(const BlockAllocator&&) = delete;
		BlockAllocator& operator=(const BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);
		size_t GetCapacity() const { return mCapacity; }

	private:
		uint8_t* mData;
		size_t mBlockSize;
		size_t mCapacity;
		std::vector<size_t> mFreeSlots;
		intptr_t nextfree;//
	};

}

#endif