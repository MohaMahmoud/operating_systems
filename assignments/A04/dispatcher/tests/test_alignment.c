#include "testlib.h"
#include "dispatcher.h"
#include <stdlib.h>

void t1() {
	_assert_alignment();
	test_assert(1, "alignment in t1 is correct");
}

int main() {
	test_start("You aligned the stack properly.");
	test_plan(2);
	
	initThreads();
	startThread(t1);

	yield();
	yield();

	// This assertion depends on a call to _assert_alignment in _parkThread,
	// which may be removed by the student.
	test_assert(1, "alignment in _parkThread is correct");

	return test_end();
}
