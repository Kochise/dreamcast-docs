#include <stdlib.h>

extern "C"
	{
	// --- The builtin C++ new/delete functions.
	void *__builtin_new(int size)
		{
		return malloc(size);
		}

	void *__builtin_vec_new(int size)
		{
		return __builtin_new(size);
		}

	void __builtin_delete(void *ptr)
		{
		free(ptr);
		}

	void __builtin_vec_delete(void *ptr)
		{
		__builtin_delete(ptr);
		}
	}
