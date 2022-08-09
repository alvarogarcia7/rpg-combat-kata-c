#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../prod.h"

static void Test_number_multiple_of_3_is_translated_to_Fizz(void **state)
{
	assert_string_equal("Fizz", fizzBuzz(6));
	assert_string_equal("Fizz", fizzBuzz(3));
	assert_string_equal("Fizz", fizzBuzz(9));
	assert_string_equal("Fizz", fizzBuzz(12));
}

static void Test_number_5_is_translated_to_Buzz(void **state)
{
	assert_string_equal("Buzz", fizzBuzz(5));
}

static void Test_number_15_is_translated_to_FizzBuzz(void **state)
{
    assert_string_equal("FizzBuzz", fizzBuzz(15));
}

/* A test case that does nothing and succeeds. */
static void canary_test(void **state) {
    (void) state; /* unused */
    assert_int_equal(0, 0);
}
int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(canary_test)
            , cmocka_unit_test(Test_number_15_is_translated_to_FizzBuzz)
            , cmocka_unit_test(Test_number_5_is_translated_to_Buzz)
            , cmocka_unit_test(Test_number_multiple_of_3_is_translated_to_Fizz)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
