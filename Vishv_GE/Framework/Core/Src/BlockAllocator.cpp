#include "Precompiled.h"
#include "BlockAllocator.h"

#include "Debug.h"

using namespace Vishv;
using namespace Vishv::Core;

Vishv::Core::BlockAllocator::BlockAllocator(uint32_t blockSize, uint32_t capacity)
	:mBlockSize(blockSize)
	,mCapacity(capacity)
{
	mData = (uint8_t*)  malloc(blockSize * capacity);
	mFreeSlots.reserve(capacity);

	for (uint32_t i = 0; i < capacity; ++i)
	{
		mFreeSlots.push_back(i);
	}

}

void * Vishv::Core::BlockAllocator::Allocate()
{
	if (mFreeSlots.empty())
		return nullptr;

	void * allocated = mData + (mFreeSlots[0] * mBlockSize);
	mFreeSlots.erase(mFreeSlots.begin());

	return allocated;
}

void Vishv::Core::BlockAllocator::Free(void * ptr)
{
	uint32_t diff = (uint8_t*)ptr - mData;

	VISHVASSERT(diff % mBlockSize == 0, "[Core::BlockAllocator] Wrong pointer is provided");

	uint32_t index = diff / mBlockSize;
	VISHVASSERT(index < mCapacity, "[Core::BlockAllocator] pointer is out of range. Wrong pointer !!!!!!");
	mFreeSlots.push_back(index);
}

Vishv::Core::BlockAllocator::~BlockAllocator()
{
	free(mData);
	mData = nullptr;
}

