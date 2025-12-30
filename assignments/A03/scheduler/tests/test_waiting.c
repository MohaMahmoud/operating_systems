#include "testlib.h"
#include "scheduler.h"

int main() {
    test_start("You handle waiting processes the right way.");

    initScheduler();
    startProcess(0, 5);
    onProcessReady(0);
    startProcess(1, 4);
    onProcessReady(1);

    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
    onProcessBlocked(0);

    test_equals_int(scheduleNextProcess(), 1, "Next Process: 1");
    onProcessBlocked(1);
    onProcessReady(0);
    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");
    onProcessBlocked(0);

    onProcessReady(1);
    onProcessReady(0);
    test_equals_int(scheduleNextProcess(), 0, "Next Process: 0");

    return test_end();
}

