#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <inttypes.h>
#include <unistd.h>

void initThreads();

void yield();

int startThread(void (*func)(void));

#define STR(x) STR2(x)
#define STR2(x) #x

/*
 * Assert that the stack is aligned at 16 byte boundaries.
 *
 * Every function starts with the following prologue that sets up the frame
 * pointer:
 *
 * push   %rbp
 * mov    %rsp,%rbp
 *
 * The standard mandates that "the value (%rsp + 8) is always a multiple of 16
 * when control is transferred to the function entry point" (AMD64 ABI Draft
 * 0.99.6, Section 3.3.2). Thus, a properly aligned stack results in a frame
 * pointer %rbp that is a multiple of 16.
 */
#define _assert_alignment() do { \
        register uint64_t _rbp __asm__ ("rbp"); \
        if (_rbp & 0xF) { \
            static const char _assert_alignment_error[] = __FILE__ ":" STR(__LINE__) ": stack is not properly aligned!\n"; \
            write(1, _assert_alignment_error, sizeof(_assert_alignment_error)); \
            abort(); \
        } \
    } while (0)

#endif
