#define _DEFAULT_SOURCE

#include "testlib.h"
#include "pointers.h"

#include "stddef.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define PAGE_SIZE ((int)(1<<12))
#define LARGE_PAGE_SIZE ((int)(1<<21))

int main()
{
    test_start("You do not crash the indirect test.");
    test_plan(1);

    void * whole_area = mmap(0, LARGE_PAGE_SIZE, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (whole_area == MAP_FAILED) {
        printf("initial map failed, weird: %s\n", strerror(errno));
        exit(1);
    }


    void *pointer_area = (void*)((ptrdiff_t)(whole_area) + PAGE_SIZE);
    void *value_area = (void*)((ptrdiff_t)(whole_area) + 5 * PAGE_SIZE);
    //printf("%p %p %p\n", whole_area, pointer_area, value_area);
    if(pointer_area != mmap(pointer_area, 2 * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS, -1, 0)) {
        printf("mmap failed, for weird reasons. Probably not the fault of the students. Error @line%d: %s\n",
            __LINE__, strerror(errno));
        exit(-1);
    }
    if(value_area != mmap(value_area, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS, -1, 0)) {
        printf("mmap failed, for weird reasons. Probably not the fault of the students. Error @line%d: %s\n",
            __LINE__, strerror(errno));
        exit(-1);
    }
    int *values = value_area;
    int **pointers = pointer_area;
    for (int i = 0; i < (int)(PAGE_SIZE / sizeof(int)); ++i)
        values[i] = i;
    for (int i = (int)(PAGE_SIZE / sizeof(int) - 1), j = 0; i >= 0; --i, ++j)
        pointers[j] = values + i;

    test_equals_int(averageIndirect(pointer_area, PAGE_SIZE / sizeof(int)), PAGE_SIZE / sizeof(int) / 2 - 1,
        "you actually dereference the correct indirect pointers");


    return 0;
}
