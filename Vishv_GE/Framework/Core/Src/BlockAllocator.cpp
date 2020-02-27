#include "Precompiled.h"
#include "BlockAllocator.h"

#include "Debug.h"

using namespace Vishv;
using namespace Vishv::Core;

Vishv::Core::BlockAllocator::BlockAllocator(size_t blockSize, size_t capacity)
	:mBlockSize(blockSize)
	,mCapacity(capacity)
{
	mData = (uint8_t*)  malloc(blockSize * capacity);
	mFreeSlots.reserve(capacity);

	for (size_t i = 0; i < capacity; ++i)
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
	size_t diff = (uint8_t*)ptr - mData;

	VISHVASSERT(diff % mBlockSize == 0, "[Core::BlockAllocator] Wrong pointer is provided");

	size_t index = diff / mBlockSize;
	VISHVASSERT(index < mCapacity, "[Core::BlockAllocator] pointer is out of range. Wrong pointer !!!!!!");
	mFreeSlots.push_back(index);
}

Vishv::Core::BlockAllocator::~BlockAllocator()
{
	free(mData);
	mData = nullptr;
}

