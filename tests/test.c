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

static void test_alive_characters_can_be_healed() {
    character character;
    character_init(&character);
    character_receive_damage(&character, 150);

    character_receive_healing(&character, 150);

    assert_int_equal(character.health, 1000);
    assert_true(character_is_alive(&character));
}

static void test_dead_characters_can_be_healed() {
    character character;
    character_init(&character);
    character_receive_damage(&character, 1000);
    assert_true(character_is_dead(&character));

    character_receive_healing(&character, 150);

    assert_int_equal(character.health, 0);
    assert_true(character_is_dead(&character));
}

static void test_character_health_cannot_go_lower_than_0() {
    character character;
    character_init(&character);

    character_receive_damage(&character, 1001);

    assert_int_equal(character.health, 0);
    assert_true(character_is_dead(&character));
}

static void test_character_health_cannot_go_higher_than_1000() {
    character character;
    character_init(&character);

    character_receive_healing(&character, 150);

    assert_int_equal(character.health, 1000);
}

static void test_character_can_damage_others() {
    character attacker; character_init(&attacker);
    character attackee; character_init(&attackee);

    character_attack(&attacker, &attackee);

    assert_int_equal(attackee.health, 850);
}

static void test_character_cannot_damage_itself() {
    character attacker; character_init(&attacker);

    character_attack(&attacker, &attacker);

    assert_int_equal(attacker.health, 1000);
}

static void test_character_attack_another_character_5_or_more_levels_above() {
    character attacker; character_init(&attacker);
    character attackee; character_init(&attackee);
    character_level_up(&attackee, 5);

    character_attack(&attacker, &attackee);

    assert_int_equal(attacker.health, 1000);
    assert_int_equal(attackee.health, 1000 - (225));
}

static void test_character_attack_another_character_5_or_more_levels_below() {
    character attacker; character_init(&attacker);
    character_level_up(&attacker, 5);
    character attackee; character_init(&attackee);

    character_attack(&attacker, &attackee);

    assert_int_equal(attacker.health, 1000);
    assert_int_equal(attackee.health, 1000 - (75));
}

static void test_character_attack_another_character_5_or_more_levels_below_corner_case() {
    character attacker; character_init(&attacker);
    character_level_up(&attacker, 5);
    character attackee; character_init(&attackee);
    character_receive_damage(&attackee, 850);

    character_attack(&attacker, &attackee);

    assert_int_equal(attacker.health, 1000);
    assert_int_equal(attackee.health, 1000 - 850 - (75));
}

/* A test case that does nothing and succeeds. */
static void canary_test(void **state) {
    (void) state; /* unused */
    assert_int_equal(0, 0);
}
int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(canary_test)
//            Initializer
            , cmocka_unit_test(test_characters_have_health_starting_at_1000)
            , cmocka_unit_test(test_characters_have_level_starting_at_1)
//            Query about character
            , cmocka_unit_test(test_characters_can_be_dead)
            , cmocka_unit_test(test_characters_can_be_alive)
//            Healing
            , cmocka_unit_test(test_alive_characters_can_be_healed)
            , cmocka_unit_test(test_dead_characters_can_be_healed)
//            Health
            , cmocka_unit_test(test_character_health_cannot_go_higher_than_1000)
            , cmocka_unit_test(test_character_health_cannot_go_lower_than_0)

//            Damage
            , cmocka_unit_test(test_character_can_damage_others)
            , cmocka_unit_test(test_character_cannot_damage_itself)
            , cmocka_unit_test(test_character_attack_another_character_5_or_more_levels_above)
            , cmocka_unit_test(test_character_attack_another_character_5_or_more_levels_below)
            , cmocka_unit_test(test_character_attack_another_character_5_or_more_levels_below_corner_case)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
