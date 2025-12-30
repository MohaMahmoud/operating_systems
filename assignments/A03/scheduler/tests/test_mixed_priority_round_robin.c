#include "testlib.h"
#include "scheduler.h"

int main() {
    test_start("You schedule two times two processes with the same priority the right way.");

    initScheduler();
    startProcess(0, 5);
    onProcessReady(0);
    startProcess(1, 5);
    onProcessReady(1);

    startProcess(2, 4);
    onProcessReady(2);
    startProcess(3, 4);
    onProcessReady(3);

    for (int i = 0; i < 10; i++) {
        // high prio
        for (int i = 0; i < 2; i++) {
            test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
            onProcessPreempted(0);
            test_equals_int(scheduleNextProcess(), 1, "Next Process: 1");
            onProcessPreempted(1);
        }
        test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
        onProcessPreempted(0);

        // low prio
        test_equals_int(scheduleNextProcess(), 2, "Next Process: 2");
        onProcessPreempted(2);

        // high prio
        for (int i = 0; i < 2; i++) {
            test_equals_int(scheduleNextProcess(), 1, "Next Process: 1");
            onProcessPreempted(1);
            test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
            onProcessPreempted(0);
        }
        test_equals_int(scheduleNextProcess(), 1, "Next Process: 1");
        onProcessPreempted(1);

        // low prio
        test_equals_int(scheduleNextProcess(), 3, "Next Process: 3");
        onProcessPreempted(3);
    }

    return test_end();
}

