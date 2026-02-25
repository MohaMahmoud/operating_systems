#include "testlib.h"
#include "hybrid_scheduler.h"
#include <stdlib.h>

int main() {
    test_start("Queue: Your enqueue and dequeue works.");

    Queue q1;
    Queue q2;
    initQueue(&q1);
    initQueue(&q2);

    enqueue(&q1, (void *) 42);
    enqueue(&q1, (void *) 43);
    enqueue(&q1, (void *) 44);
    enqueue(&q1, (void *) 45);
    enqueue(&q1, (void *) 46);

    test_equals_int((intptr_t) dequeue(&q1), 42, "dequeue -> 42");
    test_equals_int((intptr_t) dequeue(&q1), 43, "dequeue -> 43");
    test_equals_int((intptr_t) dequeue(&q1), 44, "dequeue -> 44");
    test_equals_int((intptr_t) dequeue(&q1), 45, "dequeue -> 45");
    test_equals_int((intptr_t) dequeue(&q1), 46, "dequeue -> 46");
    test_equals_int((intptr_t) dequeue(&q1), 0,  "dequeue -> NULL (queue empty)");

    enqueue(&q2, (void *) 42);
    test_equals_int((intptr_t) dequeue(&q2), 42, "dequeue -> 42");
    enqueue(&q2, (void *) 43);
    test_equals_int((intptr_t) dequeue(&q2), 43, "dequeue -> 43");
    test_equals_int((intptr_t) dequeue(&q2), 0,  "dequeue -> NULL (queue empty)");
    enqueue(&q2, (void *) 44);
    enqueue(&q2, (void *) 45);
    test_equals_int((intptr_t) dequeue(&q2), 44, "dequeue -> 44");
    test_equals_int((intptr_t) dequeue(&q2), 45, "dequeue -> 45");

    return test_end();
}


