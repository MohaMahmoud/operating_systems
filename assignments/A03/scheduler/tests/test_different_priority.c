#include "testlib.h"
#include "scheduler.h"

int main() {
    test_start("You schedule two processes with different priorities the right way.");

    initScheduler();
    startProcess(0, 5);
    onProcessReady(0);
    startProcess(1, 4);
    onProcessReady(1);
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < 5; i++) {
            test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
            onProcessPreempted(0);
        }
        test_equals_int(scheduleNextProcess(), 1, "Next Process: 1");
        onProcessPreempted(1);
    }

    return test_end();
}
