#define _XOPEN_SOURCE 600
#include "testlib.h"
#include "workerpool.h"

#include <string.h>
#include <unistd.h>

#include <sanitizer/lsan_interface.h>

static void job(int arg) {
    (void) arg;
}

int main() {
    test_start("You free the memory you allocate");
    test_plan(2);

    test_equals_int(initializeWorkerPool(), 0, "initializeWorkerPool succeeds");

    submitWork(job, 0xdeadbeef);

    usleep(100);

    finalizeWorkerPool();

    test_assert(!__lsan_do_recoverable_leak_check(), "there are no memory leaks");

    return test_end();
}
