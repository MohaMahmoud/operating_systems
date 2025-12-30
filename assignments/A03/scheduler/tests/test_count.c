#include "testlib.h"
#include "scheduler.h"

int main() {
    test_start("You do not miss to count processes just because they switch to the waiting state.");

    initScheduler();
    startProcess(0, 5);
    onProcessReady(0);
    startProcess(1, 4);

    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
    onProcessPreempted(0);
    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
    onProcessPreempted(0);
    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
    onProcessPreempted(0);

    onProcessReady(1);

    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
    onProcessPreempted(0);
    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
    onProcessPreempted(0);

    test_equals_int(scheduleNextProcess(), 1, "Next Process: 1");
    onProcessPreempted(1);

    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");

    return test_end();
}

