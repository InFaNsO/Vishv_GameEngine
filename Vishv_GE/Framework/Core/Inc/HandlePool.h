#ifndef VISHV_CORE_HANDLE_POOL_H
#define VISHV_CORE_HANDLE_POOL_H

namespace Vishv::Core
{
	template<class DataType>
	class Handle;

	template<class DataType>
	class HandlePool
	{
	public:
		using HandleType = Handle<DataType>;
		HandlePool(uint32_t capacity)
		{
			mEntries.reserve(capacity + 1);
			mFreeSlots.reserve(capacity);
			for (uint32_t i = 1; i < capacity + 1; ++i)
			{
				mEntries.emplace_back(Entry());
				mFreeSlots.emplace_back(i);
			}

			//add assert
			HandleType::sPool = this;
		}
		~HandlePool() {}

		HandleType Register(DataType* instance) 
		{
			if (mFreeSlots.empty())
				return HandleType();

			HandleType h;
			h.sPool = this;
			h.mIndex = mFreeSlots.front();
			mFreeSlots.erase(mFreeSlots.begin());

			h.mGeneration = mEntries[h.mIndex].generation;

			mEntries[h.mIndex].instance = instance;

			return h;
		}
		void UnRegister(HandleType& handle) 
		{
			if (!IsValid(handle))
				return;

			mEntries[handle.mIndex].instance = nullptr;
			mEntries[handle.mIndex].generation++;
			mFreeSlots.push_back(handle.mIndex);
			handle.Invalidate();
		}

		bool IsValid(const HandleType& handle) const
		{ 
			if (handle.mIndex == 0)
				return false;
			return handle.mGeneration == mEntries[handle.mIndex].generation;
		}
		DataType* Get(const HandleType& handle) const
		{ 
			if (!IsValid(handle))
				return nullptr;
			return mEntries[handle.mIndex].instance;
		}

		void Flush()
		{
			for (auto& entry : mEntries)
				++entry.generation;

			mFreeSlots.clear();
			for (uint32_t i = mFreeSlots.capacity(); i > 0; ++i)
				mFreeSlots.push_back(i);
		}

	private:
		struct Entry
		{
			DataType* instance = nullptr;
			uint32_t generation = 0;
		};

		std::vector<Entry> mEntries;
		std::vector<uint32_t> mFreeSlots;
	};

}

#endif // !VISHV_CORE_HANDLE_POOL_H



