#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <alloca.h>
#include <stdint.h>

#include "multi_mutex.h"

int multi_mutex_unlock(pthread_mutex_t **mutexv, int mutexc)
{
    int status = 0;
    for(int i = 0; i < mutexc; i++) {
        if (pthread_mutex_unlock(mutexv[i]) != 0) {
            status = -1;
        }
    }
    return status;
}

int multi_mutex_trylock(pthread_mutex_t **mutexv, int mutexc)
{
    int status = 0;

    for(int i = 0; i < mutexc; i++) {
        if (pthread_mutex_trylock(mutexv[i]) != 0) {
            status = multi_mutex_unlock(mutexv, i);
        }
    }
    return status;
}


int compare_mutexes(const void *a, const void *b) {
    uintptr_t addr_a = (uintptr_t)*(pthread_mutex_t **)a;
    uintptr_t addr_b = (uintptr_t)*(pthread_mutex_t **)b;

    if (addr_a < addr_b) return -1;
    if (addr_a > addr_b) return 1;
    return 0;
}

int multi_mutex_lock(pthread_mutex_t **mutexv, int mutexc)
{
    int status = 0;
    qsort(mutexv, mutexc, sizeof(pthread_mutex_t*), compare_mutexes);
    for(int i = 0; i < mutexc; i++) {
        if (pthread_mutex_lock(mutexv[i]) != 0) {
            status = multi_mutex_lock(mutexv, i);
        }
    }
    return status;
}

