#include "testlib.h"
#include "scheduler.h"

int main() {
    test_start("You schedule one process with highest priority every time.");

    initScheduler();
    startProcess(0, 5);
    onProcessReady(0);
    for (int i = 0; i < 10; i++) {
        test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
        onProcessPreempted(0);
    }

    return test_end();
}
