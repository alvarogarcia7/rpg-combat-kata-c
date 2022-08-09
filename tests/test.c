#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../prod.h"

static void test_characters_have_health_starting_at_1000() {
    character character;
    character_init(&character);

    assert_int_equal(character.health, 1000);
}

static void test_characters_have_level_starting_at_1() {
    character character;
    character_init(&character);

    assert_int_equal(character.level, 1);
}

static void test_characters_can_be_dead() {
    character character;
    character_init(&character);

    character_receive_damage(&character, 1000);

    assert_true(character_is_dead(&character));
}

static void test_characters_can_be_alive() {
    character character;
    character_init(&character);

    assert_true(character_is_alive(&character));
}


static void test_characters_can_be_healed() {
    character character;
    character_init(&character);
    character_receive_damage(&character, 150);

    character_receive_healing(&character, 150);

    assert_int_equal(character.health, 1000);
    assert_true(character_is_alive(&character));
}


static void test_character_health_cannot_go_lower_than_0() {
    character character;
    character_init(&character);

    character_receive_damage(&character, 1001);

    assert_int_equal(character.health, 0);
    assert_true(character_is_dead(&character));
}

/* A test case that does nothing and succeeds. */
static void canary_test(void **state) {
    (void) state; /* unused */
    assert_int_equal(0, 0);
}
int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(canary_test)
            , cmocka_unit_test(test_characters_have_health_starting_at_1000)
            , cmocka_unit_test(test_characters_have_level_starting_at_1)
            , cmocka_unit_test(test_characters_can_be_dead)
            , cmocka_unit_test(test_characters_can_be_alive)
            , cmocka_unit_test(test_character_health_cannot_go_lower_than_0)
            , cmocka_unit_test(test_characters_can_be_healed)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
