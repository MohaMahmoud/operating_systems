#include "testlib.h"
#include "rendering.h"

int main() {
    test_start("you decode the byte array correctly.");
    test_plan(512);

    for (int i = 0; i < 256; ++i) {
        uint8_t packed = i;
        test_equals_int(color_at(&packed, 0), i / 16, "your upper decode works");
        test_equals_int(color_at(&packed, 1), i % 16, "your lower decode works");
    }

    return test_end();
}

