#ifndef INCLUDED_VISHV_CORE_BLOCK_ALLOCATOR_H
#define INCLUDED_VISHV_CORE_BLOCK_ALLOCATOR_H

namespace Vishv::Core {

	class BlockAllocator
	{
	public:
		BlockAllocator(uint32_t blockSize, uint32_t capacity);
		~BlockAllocator();

		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;

		BlockAllocator(const BlockAllocator&&) = delete;
		BlockAllocator& operator=(const BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);
		uint32_t GetCapacity() const { return mCapacity; }

	private:
		uint8_t* mData;
		uint32_t mBlockSize;
		uint32_t mCapacity;
		std::vector<uint32_t> mFreeSlots;
		intptr_t nextfree;//
	};

}

#endif