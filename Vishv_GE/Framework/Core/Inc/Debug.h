#ifndef INCLUDED_VISHV_CORE_DEBUG_H
#define INCLUDED_VISHV_CORE_DEBUG_H

#if defined(_DEBUG)
	#define LOG(format, ...)\
		do{\
			char buffer[4096];\
			int ret = _snprintf_s(buffer, std::size(buffer), _TRUNCATE, "%s(%d) "##format, __FILE__ ,__LINE__  ,__VA_ARGS__);\
			OutputDebugStringA(buffer);\
			if(ret == -1)\
				OutputDebugStringA("** message truncated ** \n"); \
			OutputDebugStringA("\n");\
		}while(false)

	#define VISHVASSERT(condition, format, ...)\
		do{\
			if(!(condition))\
			{\
				LOG(format,__VA_ARGS__);\
				DebugBreak();\
			}\
		}while(false)
#else
	#define LOG(format, ...)
	#define VISHVASSERT(condition, format, ...)
#endif


#endif // !INCLUDED_VISHV_CORE_DEBUG_H
