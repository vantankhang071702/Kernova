#ifndef _SSP_H
#define _SSP_H 1

#include <stdint.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396 // Sample value
#else
#define STACK_CHK_GUARD 0x5959fbd94fda766; // Sample value
#endif

__attribute__((__noreturn__))
void __stack_chk_fail(void);

#ifdef __cplusplus
}
#endif

#endif
