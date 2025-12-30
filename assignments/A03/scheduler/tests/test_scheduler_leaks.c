#include "testlib.h"
#include "scheduler.h"

// Note: This test relies on LeakSanitizer to detect memory leaks. See
// Makefile.
int main() {
    test_start("You have no memory leaks in your scheduler.");

    initScheduler();
    startProcess(0, 5);
    onProcessReady(0);
    startProcess(1, 5);
    onProcessReady(1);
    startProcess(2, 5);
    onProcessReady(2);

    for (int i = 0; i < 500; i++) {
        scheduleNextProcess();
    }

    return test_end();
}
