#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "day10_impl.h"

char* testdata[146] = {
    "addx 15 \n",
    "addx -11\n",
    "addx 6  \n",
    "addx -3 \n",
    "addx 5  \n",
    "addx -1 \n",
    "addx -8 \n",
    "addx 13 \n",
    "addx 4  \n",
    "noop    \n",
    "addx -1 \n",
    "addx 5  \n",
    "addx -1 \n",
    "addx 5  \n",
    "addx -1 \n",
    "addx 5  \n",
    "addx -1 \n",
    "addx 5  \n",
    "addx -1 \n",
    "addx -35\n",
    "addx 1  \n",
    "addx 24 \n",
    "addx -19\n",
    "addx 1  \n",
    "addx 16 \n",
    "addx -11\n",
    "noop    \n",
    "noop    \n",
    "addx 21 \n",
    "addx -15\n",
    "noop    \n",
    "noop    \n",
    "addx -3 \n",
    "addx 9  \n",
    "addx 1  \n",
    "addx -3 \n",
    "addx 8  \n",
    "addx 1  \n",
    "addx 5  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx -36\n",
    "noop    \n",
    "addx 1  \n",
    "addx 7  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx 2  \n",
    "addx 6  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx 1  \n",
    "noop    \n",
    "noop    \n",
    "addx 7  \n",
    "addx 1  \n",
    "noop    \n",
    "addx -13\n",
    "addx 13 \n",
    "addx 7  \n",
    "noop    \n",
    "addx 1  \n",
    "addx -33\n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx 2  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx 8  \n",
    "noop    \n",
    "addx -1 \n",
    "addx 2  \n",
    "addx 1  \n",
    "noop    \n",
    "addx 17 \n",
    "addx -9 \n",
    "addx 1  \n",
    "addx 1  \n",
    "addx -3 \n",
    "addx 11 \n",
    "noop    \n",
    "noop    \n",
    "addx 1  \n",
    "noop    \n",
    "addx 1  \n",
    "noop    \n",
    "noop    \n",
    "addx -13\n",
    "addx -19\n",
    "addx 1  \n",
    "addx 3  \n",
    "addx 26 \n",
    "addx -30\n",
    "addx 12 \n",
    "addx -1 \n",
    "addx 3  \n",
    "addx 1  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx -9 \n",
    "addx 18 \n",
    "addx 1  \n",
    "addx 2  \n",
    "noop    \n",
    "noop    \n",
    "addx 9  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx -1 \n",
    "addx 2  \n",
    "addx -37\n",
    "addx 1  \n",
    "addx 3  \n",
    "noop    \n",
    "addx 15 \n",
    "addx -21\n",
    "addx 22 \n",
    "addx -6 \n",
    "addx 1  \n",
    "noop    \n",
    "addx 2  \n",
    "addx 1  \n",
    "noop    \n",
    "addx -10\n",
    "noop    \n",
    "noop    \n",
    "addx 20 \n",
    "addx 1  \n",
    "addx 2  \n",
    "addx 2  \n",
    "addx -6 \n",
    "addx -11\n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
};

char* realdata[142] = {
    "addx 1  \n",
    "addx 5  \n",
    "noop    \n",
    "addx -1 \n",
    "noop    \n",
    "noop    \n",
    "addx 6  \n",
    "addx 15 \n",
    "addx -9 \n",
    "noop    \n",
    "addx -1 \n",
    "addx 4  \n",
    "addx 2  \n",
    "addx -22\n",
    "addx 27 \n",
    "addx -1 \n",
    "addx 4  \n",
    "noop    \n",
    "addx 1  \n",
    "addx 2  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx 1  \n",
    "addx -33\n",
    "addx 2  \n",
    "addx 5  \n",
    "addx 2  \n",
    "addx 3  \n",
    "addx -2 \n",
    "addx 7  \n",
    "noop    \n",
    "addx -2 \n",
    "addx -8 \n",
    "addx 15 \n",
    "addx 5  \n",
    "noop    \n",
    "noop    \n",
    "addx -2 \n",
    "addx 2  \n",
    "noop    \n",
    "noop    \n",
    "addx 7  \n",
    "addx -14\n",
    "noop    \n",
    "addx -2 \n",
    "addx -17\n",
    "addx 5  \n",
    "addx -4 \n",
    "noop    \n",
    "addx 23 \n",
    "addx -18\n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx 28 \n",
    "addx -18\n",
    "addx 4  \n",
    "noop    \n",
    "noop    \n",
    "addx -5 \n",
    "addx 1  \n",
    "addx 10 \n",
    "addx 2  \n",
    "noop    \n",
    "noop    \n",
    "addx -30\n",
    "addx 33 \n",
    "addx -32\n",
    "noop    \n",
    "noop    \n",
    "addx -2 \n",
    "addx 6  \n",
    "addx -2 \n",
    "addx 4  \n",
    "addx 3  \n",
    "addx 19 \n",
    "addx 10 \n",
    "addx -5 \n",
    "addx -16\n",
    "addx 3  \n",
    "addx -2 \n",
    "addx 17 \n",
    "addx -19\n",
    "addx 11 \n",
    "addx 2  \n",
    "addx 9  \n",
    "noop    \n",
    "addx -4 \n",
    "addx -6 \n",
    "addx -7 \n",
    "addx -24\n",
    "noop    \n",
    "addx 7  \n",
    "addx -2 \n",
    "addx 5  \n",
    "addx 2  \n",
    "addx 3  \n",
    "addx -2 \n",
    "addx 2  \n",
    "addx 5  \n",
    "addx 2  \n",
    "addx 7  \n",
    "addx -2 \n",
    "noop    \n",
    "addx 3  \n",
    "addx -2 \n",
    "addx 2  \n",
    "addx 7  \n",
    "noop    \n",
    "addx -2 \n",
    "addx -34\n",
    "addx 1  \n",
    "addx 1  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx 5  \n",
    "noop    \n",
    "noop    \n",
    "addx 5  \n",
    "addx -1 \n",
    "noop    \n",
    "addx 6  \n",
    "addx -1 \n",
    "noop    \n",
    "addx 4  \n",
    "addx 3  \n",
    "addx 4  \n",
    "addx -1 \n",
    "addx 5  \n",
    "noop    \n",
    "addx 5  \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "noop    \n",
    "addx 1  \n",
    "noop    \n",
    "noop    \n",
};

void test_day_10_example (void ** state) {
    int64_t part1 = 0;
    char part2[WIDTH*HEIGHT] = {0};
    calculate(testdata, 146, &part1, part2);
    assert_int_equal(part1, 13140);
    assert_string_equal(part2, "????????");  // Example doesn't contain valid characters
}

void test_day_10_real (void ** state) {
    int64_t part1 = 0;
    char part2[WIDTH*HEIGHT] = {0};
    calculate(realdata, 142, &part1, part2);
    assert_int_equal(part1, 14040);
    assert_string_equal(part2, "ZGCJZJFL");
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_day_10_example),
        cmocka_unit_test (test_day_10_real),
    };
    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}