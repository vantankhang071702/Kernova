#include <string.h>

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) 
{
	const unsigned char* src = (const unsigned char*) srcptr;
	unsigned char* dst = (unsigned char*) dstptr;

	for (size_t i = 0; i < size; i++) 
	{
		dst[i] = src[i];
	}

	return dstptr;
}