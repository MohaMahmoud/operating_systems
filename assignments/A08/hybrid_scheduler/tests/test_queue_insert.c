#include "testlib.h"
#include "hybrid_scheduler.h"
#include <stdlib.h>

int main() {
    test_start("Queue: You insert a new item correctly.");

    Queue q;
    initQueue(&q);
    test_equals_ptr(q.tail, q.head, "after initQueue(), tail points to head");

    enqueue(&q, (void *) 42);

    test_equals_ptr(q.tail, q.head->next, "after enqueue(), tail points to inserted item");
    test_equals_ptr(q.tail->next, NULL, "next is NULL");
    test_equals_int((intptr_t) q.tail->thread, 42, "data is saved correctly");

    return test_end();
}


