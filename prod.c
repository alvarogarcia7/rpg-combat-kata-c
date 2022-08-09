#include "prod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEALTH 1000
#define INITIAL_LEVEL 1
#define MIN_HEALTH 0

void character_init(character *character) {
    character->health = MAX_HEALTH;
    character->level = INITIAL_LEVEL;
}

void character_receive_damage(character *character, damage_t damage){
    uint16_t new_health = character->health - damage;
    if (damage > character->health){
        new_health = MIN_HEALTH;
    }
    character->health = new_health;
}

void character_level_up(character *character, level_up_t level_up) {
    character->level += level_up;
}

bool character_is_dead(const character *character){
    return character->health == MIN_HEALTH;
}

bool character_is_alive(const character *character){
    return !character_is_dead(character);
}

void character_receive_healing(character *character, heal_t heal) {
    if (character_is_dead(character)){
        return;
    }

    uint16_t remaining_health_to_maximum = MAX_HEALTH - character->health;
    uint16_t result = character->health + heal;
    if (heal > remaining_health_to_maximum){
        result = MAX_HEALTH;
    }
    character->health = result;
}

void character_attack(const character *attacker, character *attackee) {
    if (attackee == attacker) {
        return;
    }
    int difference_in_levels = attacker->level - attackee->level;
    character_receive_damage(attackee, 150);
     if (difference_in_levels != 0 && difference_in_levels >= 5) {
         character_receive_healing(attackee, 75);
     } else if (difference_in_levels != 0 && difference_in_levels >= -5) {
        character_receive_damage(attackee, 150 / 2);
    }
}
