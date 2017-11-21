//great_module.c
#include <nmmintrin.h>

#ifdef _MSC_VER
#define DLL_EXPORT __declspec( dllexport ) 
#else
#define DLL_EXPORT
#endif
extern "C" {
	DLL_EXPORT int great_function(unsigned int n) {
		return _mm_popcnt_u32(n);
	}

	DLL_EXPORT int add(int n, int m) {
		return m+n;
	}
}