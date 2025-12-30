#include "testlib.h"
#include "scheduler.h"
#include <stdio.h>

int scheduled;

#define test_scheduleNextProcess(should) ({ \
    scheduled = scheduleNextProcess(); \
    char msg[100]; \
    snprintf(msg, sizeof(msg), "%s line %d: Next Process: %d", __FILE__, __LINE__, should); \
    test_equals_int(scheduled, should, msg); \
})

int main() {
    test_start("You schedule the extended test scenario the right way.");

    initScheduler();

    startProcess(0, 5);
    startProcess(1, 4);
    startProcess(2, 2);
    startProcess(3, 4);
    startProcess(4, 3);
    startProcess(5, 4);
    startProcess(6, 2);
    startProcess(7, 0);

    test_scheduleNextProcess(-1);
    // Let's assume we idle some time.
    onProcessReady(1);
    test_scheduleNextProcess(1);
    // Let's assume Process 1 is running here.
    onProcessPreempted(1);
    test_scheduleNextProcess(1);
    // Let's assume Process 1 is still running here.
    // Process 1 decides to do some Disk IO.
    onProcessBlocked(1);
    test_scheduleNextProcess(-1);
    // Assume we idle some time.
    // Suddenly, process 1 gets the data from the disk.
    onProcessReady(1);
    test_scheduleNextProcess(1);
    // Now process 1 is running.
    // Process 0 and 7 get ready.
    onProcessReady(0);
    onProcessReady(7);
    // Process 1 is still running and gets preempted.
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < 5; i++) {
            onProcessPreempted(scheduled);
            test_scheduleNextProcess(0);
        }
        onProcessPreempted(scheduled);
        test_scheduleNextProcess(j % 6 == 4 ? 7 : 1);
    }

    return test_end();
}

