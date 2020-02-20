#ifndef INCLUDED_VISHV_CORE_COMMON_H
#define INCLUDED_VISHV_CORE_COMMON_H

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

//Win32 Headers
#include <objbase.h>
#include <Windows.h>

//Standard Header
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

//Utility function to release Direct3D interfaces
template <class T>
inline void SafeRelease(T*& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}


#endif // !INCLUDED_VISHV_COMMON_H
